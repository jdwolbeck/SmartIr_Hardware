// FBS boot segment
#pragma config BWRP = OFF // write protection
#pragma config BSS = OFF  // No boot program flash segment

// FGS  general segment code protection
#pragma config GWRP = OFF  // General segment may be written
#pragma config GCP = OFF   // No Protection

// FOSCSEL Oscillator selection configuration
#pragma config FNOSC = FRC // Fast RC Oscillator (FRC)
#pragma config IESO = ON   // internal switchover, two-speed start-up enabled

// FOSC Oscillator configuration
#pragma config POSCMOD = NONE   // Primary oscillator disabled 
#pragma config POSCFREQ = HS    // primary oscillator Hz range
#pragma config SOSCSEL = SOSCHP // secondary clock power selection
#pragma config FCKSM = CSDCMD   // clock switching disabled, clock monitor disabled

// FWDT Watchdog timer configuration
#pragma config WDTPS = PS32768  // Watchdog Timer Postscale Select bits:
#pragma config FWPSA = PR128    // WDT prescaler ratio of 1:128
#pragma config WINDIS = OFF     // Windowed Watchdog Timer Disable bit:
#pragma config FWDTEN = OFF     // WDT disabled in hardware; SWDTEN bit disabled

// FPOR
#pragma config BOREN = BOR3     // Brown-out Reset enabled in hardware, SBOREN bit disabled
#pragma config PWRTEN = ON      // Power-up Timer Enable bit on
#pragma config I2C1SEL = PRI    // Alternate I2C1 Pin Mapping bit: Use Default SCL1/SDA1 Pins For I2C1
#pragma config BORV = V18       // Brown-out Reset set to lowest voltage (1.8V)
#pragma config MCLRE = ON       // RA5 input pin disabled, MCLR pin enabled

// FICD 
#pragma config ICS = PGx1       // ICD Pin Placement Select bits

#include <xc.h>
#include "initialization.h"          /* variables/params used by system.c */
#include "app.h"

#define FCY 4000000
#define BAUD_RATE 9600

void InitApp(void)
{
    InitGPIO();
    InitUART();
    InitInt0();
    InitI2C();
}

void InitGPIO(void)
{
    LATB = 0;             //Set PORTB latches value to 0
    LATBbits.LATB8 = 1;
    LATBbits.LATB9 = 1;
    TRISB = 0x1FFE;       //Set pin direction
    ANSBbits.ANSB9 = 0;   //Enable digital input
    ANSBbits.ANSB8 = 0;   //Enable digital input
    ANSBbits.ANSB7 = 0;   //Enable digital input
    ANSBbits.ANSB1 = 0;   //Enable digital input
    ANSBbits.ANSB0 = 0;   //Enable digital input
}

void InitUART(void)
{
    U2MODE = 0;
    U2STA = 0;
        
    IFS1bits.U2RXIF = 0; //Clear RX interrupt Flag
    IPC7bits.U2RXIP = 3; //Priority of RX set to 3
    IEC1bits.U2RXIE = 1; //RX interrupt enabled    
    
    //Baud_Rate = 9600; Frequency = 4MHz; U2BRG = 25;
    U2BRG = (((FCY)/BAUD_RATE)/16)-1; //Calculate baud rate registers value
    
    U2MODEbits.UARTEN = 1;  //UART2 enable    
    U2STAbits.UTXEN = 1;      //Enable
    
    //CMD prompt cleaning
    delay(10);
    U2TXREG = 0xA;
    delay(10);
    U2TXREG = 0xA;
    delay(10);
    U2TXREG = 0xD;
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
    SSP1CON1bits.WCOL = 0;      //Write Collision detect.
    SSP1CON1bits.SSPOV = 0;     //Receive overflow indicator.
    SSP1CON1bits.CKP = 0;       //1 = SCK Release.
    SSP1CON1bits.SSPM = 8;      //Master Synchronous Serial Port Mode.
    
    SSP1CON2bits.GCEN = 0;
    SSP1CON2bits.ACKSTAT = 0;
    SSP1CON2bits.ACKDT = 0;
    SSP1CON2bits.ACKEN = 0;
    SSP1CON2bits.RCEN = 0;
    SSP1CON2bits.PEN = 0;  
    SSP1CON2bits.RSEN = 0;
    SSP1CON2bits.SEN = 0;
    
    SSP1CON3bits.ACKTIM = 0;    //Ack Time Status bit.
    SSP1CON3bits.PCIE = 0;      //Stop condition Interrupt Enable.
    SSP1CON3bits.SCIE = 0;      //Start condition Interrupt Enable.
    SSP1CON3bits.BOEN = 0;      //Buffer overwrite enable.
    SSP1CON3bits.SDAHT = 1;     //SDA Hold time (1 = 300nS, 0= 100nS)
    SSP1CON3bits.SBCDE = 0;     //Slave Buss Colision detect (Slave mode)
    SSP1CON3bits.AHEN = 0;      //Address hold (Slave mode)
    SSP1CON3bits.DHEN = 0;      //Data hold (Slave mode)
    
    SSP1MSK = 0;                //Slave Address Mask register.
    IFS1bits.SSP1IF = 0; 
    SSP1STAT = 0;
    SSP1STATbits.SMP = 1;
    SSP1ADD = 0x27;
    SSP1CON1bits.SSPEN = 1;     //Enables MSSP Port. 1 = Enable.
    
    //Read Buffer to clear it out;
    int clear = 0;
    clear = SSP1BUF;
}
