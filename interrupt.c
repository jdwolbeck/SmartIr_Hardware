#include <xc.h>
#include "main.h"
#include "uart.h"

void __attribute__((interrupt, no_auto_psv)) _U2RXInterrupt(void)
{
    char RXread = U2RXREG;
    uart(RXread);
    IFS1bits.U2RXIF = 0;
}

void __attribute__((interrupt(auto_psv))) _INT0Interrupt (void)
{
    ctr++;
    IFS0bits.INT0IF = 0;
}
