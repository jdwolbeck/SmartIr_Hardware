#include <xc.h>
#include "app.h"          /* User funct/params, such as InitApp              */
#include "main.h"
#include "i2c.h"
#include "lux.h"
#include "initialization.h"

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
int i2cAddr=0x0000, i2cCtr=3, i2cBool=0, i2cW=0, i2cR=0;

int16_t main(void)
{
    InitApp();
    int delayVal = 1048;
    luxOn();
    
    while(1)
    {
        LATBbits.LATB15 = 0;
        delay(delayVal);
        LATBbits.LATB15 = 1;
        delay(delayVal);
    }
    
    return 0;
}