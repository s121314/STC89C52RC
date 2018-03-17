#include <txos.h>
#include "..\os.h"
#include <stdlib.h>
#include <string.h>

#ifdef DEBUG
static U8 OS_stackMax = 0;
#endif

void OS_stackSW() reentrant
{
#pragma asm
        PUSH    ACC
        PUSH    B
        PUSH    PSW
        PUSH    DPH ;大端模式，高位放在低地址
        PUSH    DPL

        MOV     A,R0
        PUSH    ACC
        MOV     A,R1
        PUSH    ACC
        MOV     A,R2
        PUSH    ACC
        MOV     A,R3
        PUSH    ACC
        MOV     A,R4
        PUSH    ACC
        MOV     A,R5
        PUSH    ACC
        MOV    A,R6
        PUSH    ACC
        MOV     A,R7
        PUSH    ACC
#pragma endasm
    OS_tcb[OS_taskNow].stackDeep = SP - (U8)OS_stack + 1;
#ifdef DEBUG
    if( OS_tcb[OS_taskNow].stackDeep > OS_stackMax ) OS_stackMax = OS_tcb[OS_taskNow].stackDeep;
#endif
    OS_tcb[OS_taskNow].stack = malloc( OS_tcb[OS_taskNow].stackDeep );
    memmove( OS_tcb[OS_taskNow].stack ,OS_stack ,OS_tcb[OS_taskNow].stackDeep );

    SP = OS_stack + OS_stackDeep - 8;

    OS_taskNow = OS_taskNext;
    memmove( OS_stack,OS_tcb[OS_taskNow].stack ,OS_tcb[OS_taskNow].stackDeep );
    free( OS_tcb[OS_taskNow].stack );
    OS_tcb[OS_taskNow].stack = NULL;

    SP = OS_stack + OS_tcb[OS_taskNow].stackDeep - 1;
    OS_tcb[OS_taskNow].state = OS_taskRunning;

#pragma asm
        POP     ACC
        MOV     R7,A
        POP     ACC
        MOV     R6,A
        POP     ACC
        MOV     R5,A
        POP     ACC
        MOV     R4,A
        POP     ACC
        MOV     R3,A
        POP     ACC
        MOV     R2,A
        POP     ACC
        MOV     R1,A
        POP     ACC
        MOV     R0,A

        POP     DPL ;大端模式，高位放在低地址
        POP     DPH
        POP     PSW
        POP     B
        POP     ACC
#pragma endasm
    
    return ;
}

#ifdef DEBUG
U8 OS_getStackMax()
{
    return OS_stackMax;
}
#endif