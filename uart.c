#include <xc.h>
#include <stdio.h>
#include "uart.h"
#include "main.h"
#include "i2c.h"
#include "lux.h"

void uart(char RXread)
{
    int value = 0;
    char valueStr[10] = "";
    switch (RXread)
    {
        case '1':
            value = luxRead();
            sprintf(valueStr, "%g", value);
            int i;
            while(valueStr[i] != '\0')
            {
                U2TXREG = valueStr[i++];
            }
            U2TXREG = 0x0A;
            U2TXREG = 0x0D;
            break;
        case '2':
            U2TXREG = 'A';
            U2TXREG = 0x0A;
            U2TXREG = 0x0D;
            break;
        default:
            break;   
    }
}
