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
