#include "..\os.h"

void OS_waitMail()
{
    if( OS_tcb[OS_taskNow].mail == 0 )
    {
        OS_tcb[OS_taskNow].state = OS_taskWaitMail;
        OS_taskSW();
    }
}

void OS_sendMail(U8 tid ,U8 mail)
{
    OS_tcb[tid].mail = mail;
    if( OS_tcb[tid].state == OS_taskWaitMail ) OS_tcb[tid].state = OS_taskReady;
}

U8 OS_readMail()
{
    U8 mail = OS_tcb[OS_taskNow].mail;
    OS_tcb[OS_taskNow].mail = 0;

    return mail;
}