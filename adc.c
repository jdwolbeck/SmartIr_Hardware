
#include <xc.h>
#include "app.h"
#include "adc.h"

int adc1Grab(void)
{
    LATBbits.LATB13 = 0;
    LATBbits.LATB14 = 0;
    AD1CON1bits.SAMP = 1;
    delay(10);
    AD1CON1bits.SAMP = 0;
    LATBbits.LATB14 = 1;
    while(!AD1CON1bits.DONE);
    LATBbits.LATB13 = 1;
    return ADC1BUF8;
}

int adc2Grab(void)
{
    AD1CON1bits.SAMP = 1;
    delay(10);
    AD1CON1bits.SAMP = 0;
    delay(10);
    return ADC1BUF0;
}