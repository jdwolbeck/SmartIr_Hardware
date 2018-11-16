#include <xc.h>
#include "app.h"          /* variables/params used by system.c */
#include "main.h"

void delay(int delayVal)
{
    unsigned int i,j;

    for (i = 0; i < delayVal; i++)
    {
        for (j = 0; j < 120; j++);
    }
}

void printInt(long val)
{
    if(val > 9999)
    {
        U1TXREG = (val / 10000) + '0';
        delay(10);
        U1TXREG = ((val / 1000) % 10) + '0';
        delay(10);
        U1TXREG = ((val / 100) % 10) + '0';
        delay(10);
        U1TXREG = ((val / 10) % 10) + '0';
        delay(10);
        U1TXREG = (val % 10) + '0';
        delay(10);
    }
    else if(val > 999)
    {
        U1TXREG = (val / 1000) + '0';
        U1TXREG = ((val / 100) % 10) + '0';
        U1TXREG = ((val / 10) % 10) + '0';
        U1TXREG = (val % 10) + '0';
    }
    else if(val > 99)
    {
        U1TXREG = (val / 100) + '0';
        U1TXREG = ((val / 10) % 10) + '0';
        U1TXREG = (val % 10) + '0';
    }
    else if(val > 9)
    {
        U1TXREG = (val / 10) + '0';
        U1TXREG = (val % 10) + '0';
    }
    else
    {
        U1TXREG = val + '0';
    }
}