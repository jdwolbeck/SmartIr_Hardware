/* Device header file */
#if defined (__XC16__)
    #include <xc.h>
#elif defined (__C30__)
    #if defined(__PIC24E__)
        #include <p24Fxxxx.h>
    #elif defined (__PIC24F__) || defined (__PIC24FK__)
        #include <p24Fxxxx.h>
    #elif defined(__PIC24H__)
        #include <p24Hxxxx.h>
    #endif
#endif

#include "app.h"          /* User funct/params, such as InitApp              */
#include "main.h"
#include "i2c.h"
#include "initialization.h"

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
int ctr=0, ctrSandwich=0, ctrPoptart=0, ctrSoda=0, ctrCoffee=0, ctrChips=0, ctrCookies=0;
int itemSandwich=0, itemPoptart=0, itemSoda=0, itemCoffee=0, itemChips=0, itemCookies=0, itemTotal=0;
float cashEntered = 0.0;
float total = 0.0;
char cashString[10];
int eepromAddr=0x0000, eepromCtr=3, eepromBool=0, eepromW=0, eepromR=0;

int16_t main(void)
{
    /* Initialize IO ports and peripherals */
    InitApp();
    int delayVal = 1048;
    
    while(1)
    {
        LATBbits.LATB15 = 0;
        delay(delayVal);
        LATBbits.LATB15 = 1;
        delay(delayVal);
        LATBbits.LATB15 = 0;
        delay(delayVal);
        LATBbits.LATB15 = 1;
        delay(delayVal);
    }
    
    return 0;
}