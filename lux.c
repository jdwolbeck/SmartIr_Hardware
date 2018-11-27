#include <xc.h>
#include "lux.h"
#include "i2c.h"

void luxOn(void)
{
    i2cStart();                                     //Send Start condition
    i2cWrite(SLAVE_ADDR_FLOAT_WRITE);               //Send Slave address + R/W ((0x39 << 1) + 0)
    i2cAck();                                       //Check for Acknowledgment
    i2cWrite(COMMAND_BYTE + CONTROL_REG);           //Write to control register
    i2cAck();                                       //Check for Acknowledgment
    i2cWrite(POWER_ON);                             //Write 0x03 to control register to 'power-on'
    i2cAck();                                       //Check for Acknowledgment
    i2cStop();                                      //Assert Stop condition
}

void luxOff(void)
{
    i2cStart();                                     //Send Start condition
    i2cWrite(SLAVE_ADDR_FLOAT_WRITE);               //Send Slave address + R/W ((0x39 << 1) + 0)
    i2cAck();                                       //Check for Acknowledgment
    i2cWrite(COMMAND_BYTE + CONTROL_REG);           //Write to control register
    i2cAck();                                       //Check for Acknowledgment
    i2cWrite(POWER_OFF);                            //Write 0x00 to control register to 'power-off'
    i2cAck();                                       //Check for Acknowledgment
    i2cStop();                                      //Assert Stop condition
}

long luxRead(void)
{
    long value, value1, value2;
    i2cStart();                                     //Send Start condition
    i2cWrite(SLAVE_ADDR_FLOAT_WRITE);               //Send Slave address + R/W ((0x39 << 1) + 0)
    i2cAck();                                       //Check for Acknowledgment
    i2cWrite(COMMAND_BYTE + DATA0_LOW_REG);         //Send Address of desired register
    i2cAck();                                       //Check for Acknowledgment  
    i2cRestart();                                   //Send Restart condition
    i2cWrite(SLAVE_ADDR_FLOAT_READ);                //Send Slave address + R/W ((0x39 << 1) + 1)
    i2cAck();                                       //Check for Acknowledgment
    value1 = i2cRead();                             //Read low byte of ADC0 into value1
    i2cMNAck();                                      //Send Acknowledgment to Slave
    i2cStop();                                      //Assert Stop condition 
    
    i2cStart();                                     //Send Start condition
    i2cWrite(SLAVE_ADDR_FLOAT_WRITE);               //Send Slave address + R/W ((0x39 << 1) + 0)
    i2cAck();                                       //Check for Acknowledgment
    i2cWrite(COMMAND_BYTE + DATA0_HIGH_REG);        //Send Address of desired register
    i2cAck();                                       //Check for Acknowledgment
    i2cRestart();                                   //Send Restart condition
    i2cWrite(SLAVE_ADDR_FLOAT_READ);                //Send Slave address + R/W ((0x39 << 1) + 1)
    i2cAck();                                       //Check for Acknowledgment
    value2 = i2cRead();                             //Read high byte of ADC0 into value2
    i2cMNAck();                                      //Send Acknowledgment to Slave
    i2cStop();                                      //Assert Stop condition
    
    value = value1 + (value2 << 8);                 //Combine Low and High byte 0 <= value < 65536
    return value;
}