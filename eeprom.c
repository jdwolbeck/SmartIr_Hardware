#include <xc.h>
#include "i2c.h"
#include "main.h"
#include "eeprom.h"

void eepromRead(int genBool)
{
    if(!genBool)
    {
        U1TXREG = 'R';
        eepromBool = 1;
        eepromR = 1;
    }
    else
    {
        eepromR = 0;
        U1TXREG = myReadByte(eepromAddr);
        eepromAddr = 0;
    }   
}

void eepromWrite(int genBool, char RXread)
{
    if(!genBool)
    {
        U1TXREG = 'W';
        eepromBool = 1;
        eepromW = 1;
    }
    else
    {
        int temp = myWriteByte(eepromAddr, RXread);
        eepromW = 0;
        eepromAddr = 0;
        if(!temp)
            U1TXREG = '+';
        else
            U1TXREG = '-';
    }
}

void eepromCalc(char RXread)
{
    if(eepromCtr == 0)
        eepromBool = 0;
    switch(RXread)
    {
        case '0':
            eepromAddr += (0 << (4*eepromCtr));
            break;
        case '1':
            eepromAddr += (1 << (4*eepromCtr));
            break;
        case '2':
            eepromAddr += (2 << (4*eepromCtr));
            break;
        case '3':
            eepromAddr += (3 << (4*eepromCtr));
            break;
        case '4':
            eepromAddr += (4 << (4*eepromCtr));
            break;
        case '5':
            eepromAddr += (5 << (4*eepromCtr));
            break;
        case '6':
            eepromAddr += (6 << (4*eepromCtr));
            break;
        case '7':
            eepromAddr += (7 << (4*eepromCtr));
            break;
        case '8':
            eepromAddr += (8 << (4*eepromCtr));
            break;
        case '9':
            eepromAddr += (9 << (4*eepromCtr));
            break;
        case 'A':
            eepromAddr += (10 << (4*eepromCtr));
            break;
        case 'B':
            eepromAddr += (11 << (4*eepromCtr));
            break;
        case 'C':
            eepromAddr += (12 << (4*eepromCtr));
            break;
        case 'D':
            eepromAddr += (13 << (4*eepromCtr));
            break;
        case 'E':
            eepromAddr += (14 << (4*eepromCtr));
            break;
        case 'F':
            eepromAddr += (15 << (4*eepromCtr));
            break;
        default:
            eepromR = 0;
            eepromW = 0;
            eepromAddr = 0;
            eepromCtr = 3;
            break;
    }
    U1TXREG = RXread;
    eepromCtr--;
    if(eepromR && eepromCtr < 0)
        eepromRead(1);
    if(eepromCtr < 0)
        eepromCtr = 3;
}