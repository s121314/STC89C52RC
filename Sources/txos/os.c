#include <stdlib.h>
#include "os.h"

struct
{
    U8 state;
    U16 timer;
    U8 mail;
    U8 stackDeep;
    U8 xdata *stack;
}xdata OS_tcb[OS_taskMax+2] = {0};

U8 xdata OS_memPool[OS_memPoolSize] = {0};
U8 idata OS_stack[OS_stackDeep] = {0};
U8 OS_taskNow = 0;
U8 OS_taskNext = 0;

void OS_init()
{
    OS_stack[0] = *( (U8 *)(SP-1) );
    OS_stack[1] = *( (U8 *)(SP) );
    SP = OS_stack + 2 - 1;

    init_mempool(OS_memPool ,OS_memPoolSize);

    OS_load(0 ,OS_deamon);
}

void OS_load(U8 tid ,OS_TASK code *task)
{
    OS_tcb[tid].state = OS_taskReady;
    OS_tcb[tid].timer = 1;
    OS_tcb[tid].mail = 0;
    OS_tcb[tid].stackDeep = 17;
    OS_tcb[tid].stack = malloc(20);

    *(OS_tcb[tid].stack + 17 -1 -13 -1) = (U16)task % 256;
    *(OS_tcb[tid].stack + 17 -1 -13 ) = (U16)task / 256;
}

void OS_boot()
{
    OS_load( OS_taskMax + 1 , OS_idle );
	Timer2_init();

    OS_stack[0] = (U8)( (U16)OS_deamon % 256 );
    OS_stack[1] = (U8)( (U16)OS_deamon / 256 );

    OS_taskNow = OS_taskNext = 0;

    SP = OS_stack + 2 -1;
    return ;
}