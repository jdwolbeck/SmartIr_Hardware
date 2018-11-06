extern int i2cBool, i2cW, i2cR, i2cAddr, i2cCtr;

unsigned char myReadByte(unsigned short);
int myWriteByte(unsigned short, unsigned char);
void i2cIdle(void);
void i2cAck(void);
void i2cNAck(void);
void i2cStart(void);
int i2cWrite(unsigned char);
unsigned char i2cRead(void);
void i2cRestart(void);
void i2cStop(void);
