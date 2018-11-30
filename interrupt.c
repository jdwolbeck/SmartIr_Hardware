#include <xc.h>
#include "main.h"
#include "uart.h"
#include "app.h"

void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void)
{
    if(U1STAbits.URXDA)
    {
        char RXread = U1RXREG;
        if(RXread >= 0 && RXread <= 127)
            uart(RXread);
        IFS0bits.U1RXIF = 0;
    }
    else
        IFS0bits.U1RXIF = 1;
}

void __attribute__((interrupt(auto_psv))) _INT0Interrupt (void)
{
    IFS0bits.INT0IF = 0;
}
