#include <intrins.h>
#include <txos.h>
#include "..\os.h"

#define OS_tick_CPUTick ((U16)(CPUHz*OS_tick_ms/1000))
#define OS_tickPatch (0)

static U8 CPUCount[2] = {0};
static U8 CPUUsage = 0;

extern U8 OS_getCPUUsage()
{
    return CPUUsage;
}

OS_TASK OS_idle() reentrant
{
    do
    {
        #ifdef DEBUG
        OS_getCPUUsage();
        OS_getStackMax();
        #endif
        CPUCount[0]++;

        OS_sendMail(OS_taskMax+1 ,1);
        OS_waitMail();
        OS_readMail();

        OS_waitCPUTick(0);
        OS_waitMs(OS_tick_ms);
    }while(TRUE);
}

void Timer2_init()
{
    IPH |= 0x20 ;IP |= 0x20;
    T2MOD = 0x00 ; T2CON = 0x00 ;TF2 = 0;
    RCAP2H = ( 65536 - OS_tick_CPUTick - OS_tickPatch ) / 256;
    RCAP2L = ( 65536 - OS_tick_CPUTick - OS_tickPatch ) % 256;
    ET2 = 1 ;EA = 1 ;
    TR2 = 1;
}

void Timer2_ISR() interrupt 5
{
    static U8 tid = 0;

    TF2 = 0;
    for( tid = 0 ;tid <= (OS_taskMax+1) ;tid++ )
    {
        if( OS_tcb[tid].timer == 0 )
        {
            if(  OS_tcb[tid].state == OS_taskWaitTimer )
            {
                OS_tcb[tid].state = OS_taskReady;
            }
        }
        else
        {
            OS_tcb[tid].timer --;
        }
    }

    if( (++CPUCount[0]) >= 100 )
    {
        CPUUsage =( 1 - ((R32)CPUCount[1]) / CPUCount[0] ) * 100;
        CPUCount[0] = CPUCount[1] = 0;
    }
}

void OS_waitMs(U16 ms)
{
    U16 tick = ms / OS_tick_ms;
    if( tick==0 ) tick=1;
    
    OS_tcb[OS_taskNow].timer = tick;
    OS_tcb[OS_taskNext].state = OS_taskWaitTimer;
    OS_taskSW();
}

void OS_waitCPUTick(U8 tick)
{
    if( tick >= 21 )
    {
        tick = tick - 21 + 2 ;
        if( tick%2 != 0 ) _nop_();
        tick = tick / 2;
        do
        {
            --tick;
        }while( tick!=0 );
    }
    else
    {
        _nop_();_nop_();_nop_();_nop_();_nop_();
        _nop_();_nop_();_nop_();_nop_();_nop_();
    }
}