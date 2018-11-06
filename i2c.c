#include <xc.h>
#include "i2c.h"
#include "app.h"
#include "main.h"

void i2cIdle(void)
{
  // Wait for Status Idle (i.e. ACKEN, RCEN, PEN, RSEN, SEN) and I2C Bus stop detection
  while (( SSP1CON2 & 0x1F ) || ( SSP1STAT & 0x04 ));
}

void i2cAck(void)
{
    while(SSP1CON2bits.ACKSTAT);
}

void i2cNAck(void)
{
    SSP1CON2bits.ACKDT = 1;
    SSP1CON2bits.ACKEN = 1;
    while(SSP1CON2bits.ACKEN);
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
