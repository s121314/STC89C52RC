#ifndef _INC_OS_H
#define _INC_OS_H

#include <txos.h>

#define OS_taskRunning 0
#define OS_taskReady 1
#define OS_taskWaitTimer 2
#define OS_taskWaitMail 3
#define OS_taskWaitUart 4

extern struct
{
    U8 state;
    U16 timer;
    U8 mail;
    U8 stackDeep;
    U8 xdata *stack;
}xdata OS_tcb[OS_taskMax+2];

extern U8 xdata OS_memPool[OS_memPoolSize];
extern U8 idata OS_stack[OS_stackDeep];

extern U8 OS_taskNow;
extern U8 OS_taskNext;

extern OS_TASK OS_deamon() reentrant;
extern OS_TASK OS_idle() reentrant;

extern void OS_taskSW();
extern void Timer2_init();

#endif