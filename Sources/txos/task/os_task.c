#include <txos.h>
#include "..\os.h"

extern void OS_stackSW() reentrant;

OS_TASK OS_deamon() reentrant
{
    do
    {
        OS_waitMs(OS_tick_ms);
    }while(TRUE);
}

void OS_taskSW()
{
    for( OS_taskNext = 0 ;TRUE ;OS_taskNext++)
    {
        if( OS_taskNext > OS_taskMax + 1 ) OS_taskNext = 0;
        if( OS_tcb[OS_taskNext].state == OS_taskReady ) break;
    }
    for( OS_taskNext = 0 ;TRUE ;OS_taskNext++)
    {
        if( OS_taskNext > OS_taskMax + 1 ) OS_taskNext = 0;
        if( OS_tcb[OS_taskNext].state == OS_taskReady ) break;
    }

    if( OS_taskNext != OS_taskNow )
    {
        OS_stackSW();
    }
}