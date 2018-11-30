#include <xc.h>
#include <stdbool.h>
#include "i2c.h"
#include "app.h"
#include "main.h"

void i2cIdle(void)
{
  // Wait for Status Idle (i.e. ACKEN, RCEN, PEN, RSEN, SEN) and I2C Bus stop detection
    while (( I2C1CONL & 0x1F ) || ( I2C1STAT & 0x4001 ));
}

int i2cAck(void)
{
    if(I2C1STATbits.ACKSTAT)
    {
        U1TXREG = 'N';
        return 0;
    }
    else
    {
        U1TXREG = 'A';
        I2C1STATbits.ACKSTAT = 1;
        return 1;
    }
}

/**********| Function for Master sending (No) Acknowledgment to Slave |**********/
void i2cMNAck(void)
{
    I2C1CONLbits.ACKDT = 1;
    I2C1CONLbits.ACKEN = 1;
    while(I2C1CONLbits.ACKEN);
}

void i2cMAck(void)
{
    I2C1CONLbits.ACKDT = 0;
    I2C1CONLbits.ACKEN = 1;
    while(I2C1CONLbits.ACKEN);
}

/**********| Function for Master sending Start Condition |**********/
void i2cStart(void)
{
    i2cIdle();                  //Check if the I2C bus is idle
    I2C1CONLbits.SEN=1;         //Initiate start condition   
    while(I2C1CONLbits.SEN);    //Cleared automatically by hardware
}

void i2cWrite(unsigned char data)
{
    i2cIdle();
    I2C1TRN = data;             //Input data to buffer
    while(I2C1STATbits.TRSTAT); //Wait while transmit in progress
}

int i2cRead(void)
{
    i2cIdle(); //Wait for an Idle bus
    I2C1CONLbits.RCEN = 1;
    while(I2C1CONLbits.RCEN || !I2C1STATbits.RBF);
    return I2C1RCV;
}

void i2cRestart(void)
{
    I2C1CONLbits.RSEN=1;                        //Initiate restart condition
    while(I2C1CONLbits.RSEN);
}

void i2cStop(void)
{
    I2C1CONLbits.PEN=1;             //Initiate Stop condition
    while(I2C1CONLbits.PEN);
}

bool myWriteByte(unsigned short bAdd, unsigned char bData)
{
    unsigned short highAdd = (bAdd >> 8) & 0xFF;
    unsigned short lowAdd = (bAdd & 0x00FF);
    i2cStart();
    i2cWrite(0xA0);
    i2cAck();
    i2cWrite(highAdd);
    i2cAck();
    i2cWrite(lowAdd);        
    i2cAck();
    i2cWrite(bData);
    i2cAck();
    i2cStop();

    delay(256);
    return true;
}
 
 
unsigned char myReadByte(unsigned short bAdd)
{
    unsigned char value;
    unsigned short highAdd = (bAdd >> 8) & 0xFF;
    unsigned short lowAdd = (bAdd & 0x00FF);
    i2cStart();
    i2cWrite(0b10100000);
    i2cAck();
    i2cWrite(highAdd);
    i2cAck();
    i2cWrite(lowAdd);
    i2cAck();
    i2cRestart();
    i2cWrite(0b10100001);
    i2cAck();
    value = i2cRead();
    i2cMAck();
    i2cStop();

    delay(256);
    return value;
}
