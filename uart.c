#include <xc.h>
#include "uart.h"
#include "main.h"
#include "i2c.h"

void uart(char RXread)
{
    if(eepromBool)
    {
        eepromCalc(RXread);
    }
    else if(eepromW)
    {
        eepromWrite(1, RXread);
    }
    else
    {
        switch (RXread)
        {
            case 'r':
                eepromRead(0);
                break;
            case 'w':
                eepromWrite(0, RXread);
                break;
            default:
                break;   
        }
    }
}
