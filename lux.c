#include <xc.h>
#include "lux.h"
#include "i2c.h"

void luxOn(void)
{
    i2cStart();
    i2cWrite(0b01110010);
    i2cAck();
    i2cWrite(0xC0);
    i2cAck();
    i2cWrite(0x03);
    i2cAck();
    i2cStop();
}

void luxOff(void)
{
    i2cStart();
    i2cWrite(0b01110010);
    i2cAck();
    i2cWrite(0xC0);
    i2cAck();
    i2cWrite(0x00);
    i2cAck();
    i2cStop();
}

int luxRead(void)
{
    
    int value, value1, value2;
    //Read the value of the low byte of ADC0 into value
    i2cStart();
    i2cWrite(0b01110010);
    i2cAck();
    i2cWrite(0xCC);
    i2cAck();
    i2cRestart();
    i2cWrite(0b01110011);
    value1 = i2cRead();
    i2cNAck(); 
    i2cStop();   
    
    //Read the value of the high byte of ADC0 into value
    i2cStart();
    i2cWrite(0b01110010);
    i2cAck();
    i2cWrite(0xCD);
    i2cAck();
    i2cRestart();
    i2cWrite(0b01110011);
    value2 = i2cRead();
    i2cNAck();
    i2cStop();
    
    value = value1 + (value2 << 8);
    return value;
}