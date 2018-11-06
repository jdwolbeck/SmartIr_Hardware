#include <xc.h>
#include "i2c.h"
#include "app.h"
#include "main.h"

void i2cIdle(void)
{
  // Wait for Status Idle (i.e. ACKEN, RCEN, PEN, RSEN, SEN) and I2C Bus stop detection
  while (( SSP1CON2 & 0x1F ) || ( SSP1STAT & 0x04 ));
}

void i2cStart(void)
{
    i2cIdle();                         //Check if the I2C bus is idle
    SSP1CON2bits.SEN=1;                 //Initiate start condition
    while(SSP1CON2bits.SEN);
}

int i2cWrite(unsigned char data)
{
        SSP1BUF=data;               //Input data to buffer
        while(SSP1STATbits.R_W);    //Wait for transmission to finish
        return SSP1CON2bits.ACKSTAT;//Return if acknowledgment
}

unsigned char i2cRead(void)
{
        SSP1CON2bits.RCEN = 1;
        while(SSP1CON2bits.RCEN);
        return SSP1BUF;
}

void i2cRestart(void)
{
    SSP1CON2bits.RSEN=1;                        //Initiate restart condition
    while(SSP1CON2bits.RSEN);
}

void i2cStop(void)
{
    SSP1CON2bits.PEN=1;             //Initiate Stop condition
    while(SSP1CON2bits.PEN);
}

int myWriteByte(unsigned short bAdd, unsigned char bData)
{
    unsigned short highAdd = (bAdd >> 8) & 0xFF;
    unsigned short lowAdd = (bAdd & 0x00FF);
    i2cStart();
    i2cWrite(0xA0);
    i2cWrite(highAdd);
    i2cWrite(lowAdd);        
    unsigned int temp = i2cWrite(bData);
    i2cStop();

    delay(256);
    return temp;
}
 
 
unsigned char myReadByte(unsigned short bAdd)
{
    unsigned char value;
    unsigned short highAdd = (bAdd >> 8) & 0xFF;
    unsigned short lowAdd = (bAdd & 0x00FF);
    i2cStart();
    i2cWrite(0b10100000);
    i2cWrite(highAdd);
    i2cWrite(lowAdd);
    i2cRestart();
    i2cWrite(0b10100001);
    value = i2cRead();
    i2cStop();

    delay(256);
    return value;
}

void eepromRead(int genBool)
{
    if(!genBool)
    {
        U2TXREG = 'R';
        eepromBool = 1;
        eepromR = 1;
    }
    else
    {
        eepromR = 0;
        U2TXREG = myReadByte(eepromAddr);
        eepromAddr = 0;
    }   
}

void eepromWrite(int genBool, char RXread)
{
    if(!genBool)
    {
        U2TXREG = 'W';
        eepromBool = 1;
        eepromW = 1;
    }
    else
    {
        int temp = myWriteByte(eepromAddr, RXread);
        eepromW = 0;
        eepromAddr = 0;
        if(!temp)
            U2TXREG = '+';
        else
            U2TXREG = '-';
    }
}

void eepromCalc(char RXread)
{
    if(eepromCtr == 0)
        eepromBool = 0;
    switch(RXread)
    {
        case '0':
            eepromAddr += (0 << (4*eepromCtr));
            break;
        case '1':
            eepromAddr += (1 << (4*eepromCtr));
            break;
        case '2':
            eepromAddr += (2 << (4*eepromCtr));
            break;
        case '3':
            eepromAddr += (3 << (4*eepromCtr));
            break;
        case '4':
            eepromAddr += (4 << (4*eepromCtr));
            break;
        case '5':
            eepromAddr += (5 << (4*eepromCtr));
            break;
        case '6':
            eepromAddr += (6 << (4*eepromCtr));
            break;
        case '7':
            eepromAddr += (7 << (4*eepromCtr));
            break;
        case '8':
            eepromAddr += (8 << (4*eepromCtr));
            break;
        case '9':
            eepromAddr += (9 << (4*eepromCtr));
            break;
        case 'A':
            eepromAddr += (10 << (4*eepromCtr));
            break;
        case 'B':
            eepromAddr += (11 << (4*eepromCtr));
            break;
        case 'C':
            eepromAddr += (12 << (4*eepromCtr));
            break;
        case 'D':
            eepromAddr += (13 << (4*eepromCtr));
            break;
        case 'E':
            eepromAddr += (14 << (4*eepromCtr));
            break;
        case 'F':
            eepromAddr += (15 << (4*eepromCtr));
            break;
        default:
            eepromR = 0;
            eepromW = 0;
            eepromAddr = 0;
            eepromCtr = 3;
            break;
    }
    U2TXREG = RXread;
    eepromCtr--;
    if(eepromR && eepromCtr < 0)
        eepromRead(1);
    if(eepromCtr < 0)
        eepromCtr = 3;
}