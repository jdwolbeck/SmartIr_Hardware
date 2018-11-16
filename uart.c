#include <xc.h>
#include <stdio.h>
#include "uart.h"
#include "main.h"
#include "i2c.h"
#include "app.h"
#include "eeprom.h"
#include "lux.h"

void uart(char RXread)
{
    long value = 0;
    switch (RXread)
    {
        case 'r':
            eepromRead(0);
            break;
        case 'w':
            eepromWrite(0, RXread);
            break;
        case '1':
            value = luxRead();
            printInt(value);
            break;
        case '2':
            U1TXREG = 'A';
            U1TXREG = 0x0A;
            U1TXREG = 0x0D;
            break;
        default:
            break;   
    }
}
