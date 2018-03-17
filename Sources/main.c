#include <txos.h>
#include "dev\led.h"

OS_TASK task1()
{
    do
    {
        LED_setLedOn(1);
        OS_waitMs(1000);

        LED_setLedOff(1);
        OS_waitMs(1000);
    }while(TRUE);
}

OS_TASK task2()
{
    do
    {
        LED_setLedOff(2);
        OS_waitMs(1000);

        LED_setLedOn(2);
        OS_waitMs(1000);
    }while(TRUE);
}

void main()
{
    OS_init();

    OS_load(1,task1);
    OS_load(2,task2);

    OS_boot();
}