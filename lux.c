#include <xc.h>
#include "lux.h"
#include "i2c.h"

void luxOn(void)
{
    i2cStart();             //Send Start condition
    i2cWrite(0b01110010);   //Send Slave address + R/W ((0x39 << 1) + 0)
    i2cAck();               //Check for Acknowledgment
    i2cWrite(0x80);         //Write to command register
    i2cAck();               //Check for Acknowledgment
    i2cWrite(0x03);         //Write 0x03 to command register to 'power-on'
    i2cAck();               //Check for Acknowledgment
    i2cStop();              //Assert Stop condition
}

void luxOff(void)
{
    i2cStart();
    i2cWrite(0b01110010);
    i2cAck();
    i2cWrite(0x80);
    i2cAck();
    i2cWrite(0x00);
    i2cAck();
    i2cStop();
}

long luxRead(void)
{
    long value, value1, value2;
    //Read the value of the low byte of ADC0 into value
    i2cStart();
    i2cWrite(0b01110010);
    i2cAck();
    i2cWrite(0x8E);
    i2cAck();
    i2cRestart();
    i2cWrite(0b01110011);
    i2cAck();
    value1 = i2cRead();
    i2cNAck(); 
    i2cStop();   
    
    //Read the value of the high byte of ADC0 into value
    i2cStart();
    i2cWrite(0b01110010);
    i2cAck();
    i2cWrite(0x8F);
    i2cAck();
    i2cRestart();
    i2cWrite(0b01110011);
    i2cAck();
    value2 = i2cRead();
    i2cNAck();
    i2cStop();
    
    value = value1 + (value2 << 8);
    return value;
}