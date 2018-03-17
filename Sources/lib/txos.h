#ifndef _TXOS
#define _TXOS

#include <ansi.h>
#include <STC89C5xRC.h>

#define DEBUG

#define MCU "STC89C52RC"
#define CPUHz (12000000UL/12)
#define OS_taskMax 2

#define OS_version "v0.2.13_20161001"
#define OS_tick_ms 10
#define OS_stackDeep 64
#define OS_memPoolSize 128

typedef void OS_TASK;
extern void OS_init();
extern void OS_boot();
extern void OS_load(U8 tid ,OS_TASK code *task);

extern void OS_waitMs(U16 ms);
extern void OS_waitCPUTick(U8 tick);

extern void OS_waitMail();
extern void OS_sendMail(U8 tid ,U8 mail);
extern U8 OS_readMail();

extern U8 OS_getCPUUsage();
//#define  OS_getCPUTick(us) (CPUHz*(us)/1000000UL)

#ifdef DEBUG
extern U8 OS_getStackMax();
#endif

#endif