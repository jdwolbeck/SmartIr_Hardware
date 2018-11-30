#include <stdbool.h>

extern int i2cBool, i2cW, i2cR, i2cAddr, i2cCtr;

unsigned char myReadByte(unsigned short);
bool myWriteByte(unsigned short, unsigned char);
void i2cIdle(void);
int i2cAck(void);
void i2cMAck(void);
void i2cMNAck(void);
void i2cStart(void);
void i2cWrite(unsigned char);
int i2cRead(void);
void i2cRestart(void);
void i2cStop(void);
