#include <xc.h>
#include "app.h"
#include "adc.h"

int adcGrab(int select)
{
    int ADCValue0 = 0;
    int ADCValue1 = 0;
    IFS0bits.AD1IF = 0;
    AD1CON1bits.ASAM = 1;
    
    while(!IFS0bits.AD1IF){};
    AD1CON1bits.ASAM = 0;
    ADCValue0 = ADC1BUF0;
    ADCValue1 = ADC1BUF1;
    
    if(select)
        return ADCValue1;
    else
        return ADCValue0;
}