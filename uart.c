#include <xc.h>
#include <stdio.h>
#include "uart.h"
#include "main.h"
#include "i2c.h"
#include "app.h"
#include "lux.h"
#include "adc.h"

void uart(char RXread)
{
    long value = 0;
    int adcVal = 1;
    switch (RXread)
    {
        case 'a':
            adcVal = adc1Grab();
            printInt(adcVal);
            U1TXREG = 0x0A;
            U1TXREG = 0x0D;
            break;
        case 'b':
            adcVal = adc2Grab();
            printInt(adcVal);
            U1TXREG = 0x0A;
            U1TXREG = 0x0D;
            break;
        case 'i':
            luxOn();
            break;
        case 'o':
            value = luxRead();
            printInt(value);
            break;
        case 0xD:
            U1TXREG = 0x0A;
            U1TXREG = 0x0D;
            break;
        default:
            U1TXREG = 'E';
            break;   
    }
}
