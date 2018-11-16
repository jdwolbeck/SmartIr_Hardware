#include <xc.h>
#include "main.h"
#include "uart.h"

void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void)
{
    char RXread = U1RXREG;
    uart(RXread);
    IFS0bits.U1RXIF = 0;
}

void __attribute__((interrupt(auto_psv))) _INT0Interrupt (void)
{
    IFS0bits.INT0IF = 0;
}
