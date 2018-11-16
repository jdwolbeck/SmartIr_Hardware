// FSEC
#pragma config BWRP = OFF    // Boot Segment Write-Protect bit->Boot Segment may be written
#pragma config BSS = DISABLED    // Boot Segment Code-Protect Level bits->No Protection (other than BWRP)
#pragma config BSEN = OFF    // Boot Segment Control bit->No Boot Segment
#pragma config GWRP = OFF    // General Segment Write-Protect bit->General Segment may be written
#pragma config GSS = DISABLED    // General Segment Code-Protect Level bits->No Protection (other than GWRP)
#pragma config CWRP = OFF    // Configuration Segment Write-Protect bit->Configuration Segment may be written
#pragma config CSS = DISABLED    // Configuration Segment Code-Protect Level bits->No Protection (other than CWRP)
#pragma config AIVTDIS = OFF    // Alternate Interrupt Vector Table bit->Disabled AIVT

// FBSLIM
#pragma config BSLIM = 8191    // Boot Segment Flash Page Address Limit bits->

// FOSCSEL
#pragma config FNOSC = FRC    // Oscillator Source Selection->Internal Fast RC (FRC)
#pragma config PLLMODE = DISABLED    // PLL Mode Selection->No PLL used; PLLEN bit is not available
#pragma config IESO = ON    // Two-speed Oscillator Start-up Enable bit->Start up device with FRC, then switch to user-selected oscillator source

// FOSC
#pragma config POSCMD = NONE    // Primary Oscillator Mode Select bits->Primary Oscillator disabled
#pragma config OSCIOFCN = OFF    // OSC2 Pin Function bit->OSC2 is clock output
#pragma config SOSCSEL = OFF    // SOSC Power Selection Configuration bits->Digital (SCLKI) mode
#pragma config PLLSS = PLL_PRI    // PLL Secondary Selection Configuration bit->PLL is fed by the Primary oscillator
#pragma config IOL1WAY = ON    // Peripheral pin select configuration bit->Allow only one reconfiguration
#pragma config FCKSM = CSDCMD    // Clock Switching Mode bits->Both Clock switching and Fail-safe Clock Monitor are disabled

// FWDT
#pragma config WDTPS = PS32768    // Watchdog Timer Postscaler bits->1:32768
#pragma config FWPSA = PR128    // Watchdog Timer Prescaler bit->1:128
#pragma config FWDTEN = OFF    // Watchdog Timer Enable bits->WDT and SWDTEN disabled
#pragma config WINDIS = OFF    // Watchdog Timer Window Enable bit->Watchdog Timer in Non-Window mode
#pragma config WDTWIN = WIN25    // Watchdog Timer Window Select bits->WDT Window is 25% of WDT period
#pragma config WDTCMX = WDTCLK    // WDT MUX Source Select bits->WDT clock source is determined by the WDTCLK Configuration bits
#pragma config WDTCLK = LPRC    // WDT Clock Source Select bits->WDT uses LPRC

// FPOR
#pragma config BOREN = ON    // Brown Out Enable bit->Brown Out Enable Bit
#pragma config LPCFG = OFF    // Low power regulator control->No Retention Sleep
#pragma config DNVPEN = ENABLE    // Downside Voltage Protection Enable bit->Downside protection enabled using ZPBOR when BOR is inactive

// FICD
#pragma config ICS = PGD1    // ICD Communication Channel Select bits->Communicate on PGEC1 and PGED1
#pragma config JTAGEN = OFF    // JTAG Enable bit->JTAG is disabled

// FDEVOPT1
#pragma config ALTCMPI = DISABLE    // Alternate Comparator Input Enable bit->C1INC, C2INC, and C3INC are on their standard pin locations
#pragma config TMPRPIN = OFF    // Tamper Pin Enable bit->TMPRN pin function is disabled
#pragma config SOSCHP = ON    // SOSC High Power Enable bit (valid only when SOSCSEL = 1->Enable SOSC high power mode (default)
#pragma config ALTI2C1 = ALTI2CEN    // Alternate I2C pin Location->SDA1 and SCL1 on RB9 and RB8

#include <xc.h>
#include "initialization.h"          /* variables/params used by system.c */
#include "app.h"
#include "i2c.h"

#define FCY 4000000
#define BAUD_RATE 9600

void InitApp(void)
{
    InitClock();
    InitGPIO();
    i2cBusReset();
    InitUART();
    InitInt0();
    InitI2C(); 
}

void InitClock(void)
{
    // CPDIV 1:1; PLLEN disabled; DOZE 1:8; RCDIV FRC; DOZEN disabled; ROI disabled; 
    CLKDIV = 0x3000;
    // STOR disabled; STORPOL Interrupt when STOR is 1; STSIDL disabled; STLPOL Interrupt when STLOCK is 1; STLOCK disabled; STSRC SOSC; STEN disabled; TUN Center frequency; 
    OSCTUN = 0x0000;
    // ROEN disabled; ROSEL FOSC; ROSIDL disabled; ROSWEN disabled; ROOUT disabled; ROSLP disabled; 
    REFOCONL = 0x0000;
    // RODIV 0; 
    REFOCONH = 0x0000;
    // ROTRIM 0; 
    REFOTRIML = 0x0000;
    // DCOTUN 0; 
    DCOTUN = 0x0000;
    // DCOFSEL 8; DCOEN disabled; 
    DCOCON = 0x0700;
    // DIV 0; 
    OSCDIV = 0x0000;
    // TRIM 0; 
    OSCFDIV = 0x0000;
    // CF no clock failure; NOSC FRC; SOSCEN disabled; POSCEN disabled; CLKLOCK unlocked; OSWEN Switch is Complete; IOLOCK not-active; 
    __builtin_write_OSCCONH((uint8_t) ((0x0000 >> _OSCCON_NOSC_POSITION) & 0x00FF));
    __builtin_write_OSCCONL((uint8_t) (0x0000 & 0x00FF));
}

void InitGPIO(void)
{
    LATB = 0;
    //Set direction of RB pins (1 = input | 0 = output)
    TRISB = 0x1FEF;
    //Set pins as digital input pins
    ANSB = 0x0000;
}

void InitUART(void)
{
    U1MODE = 0x0000;//(0x8008 & ~(1<<15));//0x0000;
    U1STA = 0x0000;
        
    RPINR18bits.U1RXR = 3; //Set RB3 as U1RX
    RPOR2bits.RP4R = 3;  //Set RB4 as U1TX
    IFS0bits.U1RXIF = 0; //Clear RX interrupt Flag
    IPC2bits.U1RXIP = 3; //Priority of RX set to 3
    IEC0bits.U1RXIE = 1; //RX interrupt enabled    
    
    //Baud_Rate = 9600; Frequency = 4MHz; U2BRG = 25;
    U1BRG = (((FCY/BAUD_RATE)/16)-1); //Calculate baud rate registers value
    U1MODEbits.UARTEN = 1;  //UART1 enable    
    U1STAbits.UTXEN = 1;    //Enable
}

void InitInt0(void)
{
    IFS0bits.INT0IF = 0;        //Reset INT0 interrupt flag
    INTCON1bits.NSTDIS = 0;     //Disable interrupt nesting
    IPC0bits.INT0IP = 4;        //Set high priority.
    INTCON2bits.INT0EP = 0;     //Set Interrupt 0's polarity to rising
    IEC0bits.INT0IE = 1;        //Enable Interrupt 0
}

void InitI2C(void)
{
    I2C1CONL = 0x1000;
    I2C1STAT = 0;
    I2C1CONHbits.SDAHT = 1;     //SDA Hold time (1 = 300nS, 0= 100nS)
    I2C1BRG = 0x12;
    I2C1ADD = 0x39;
    //I2C1MSK = 0x00;
    IFS1bits.MI2C1IF = 0;
    I2C1CONLbits.I2CEN = 1;     //enables i2c 1 = Enable.
    
//    //Read Buffer to clear it out;
//    int clear = 0;
//    clear = I2C1RCV;
}
