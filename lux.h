#define SLAVE_ADDR_FLOAT_WRITE  0x72//Address of TSL2561 (ADDR pin floating)
#define SLAVE_ADDR_FLOAT_READ   0x73//Address of TSL2561 (ADDR pin floating)
#define WRITE_BIT           0b0 //R/nW bit low to write
#define READ_BIT            0b1 //R/nW bit high to read
#define COMMAND_BYTE        0x80//Bit 7: 1, Bit 6: Clear, Bit 5: WORD, Bit 4: Block
#define POWER_ON            0x03//Write to Control register to begin conversion
#define POWER_OFF           0x00//Write to Control register to end conversion

#define CONTROL_REG         0x0 //Control of basic functions
#define TIMING_REG          0x1 //Integration time/gain control
#define THRESHLOW_LOW_REG   0x2 //Low byte of low interrupt threshold
#define THRESHLOW_HIGH_REG  0x3 //High byte of low interrupt threshold
#define THRESHHIGH_LOW_REG  0x4 //Low byte of high interrupt threshold
#define THRESHHIGH_HIGH_REG 0x5 //High byte of high interrupt threshold
#define INTERRUPT_REG       0x6 //Interrupt control
#define DATA0_LOW_REG       0xC //Low byte of ADC channel 0
#define DATA0_HIGH_REG      0xD //High byte of ADC channel 0
#define DATA1_LOW_REG       0xE //Low byte of ADC channel 1
#define DATA1_HIGH_REG      0xF //High byte of ADC channel 1

extern unsigned int broadband, infrared;

long luxRead(void);
void luxOn(void);
void luxOff(void);