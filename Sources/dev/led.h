#ifndef _DEV_LED
#define _DEV_LED

#include <txos.h>

#define LED_led1 P10
#define LED_led1On 0

#define LED_led2 P11
#define LED_led2On 0

extern void LED_setLedOn(U8 id);
extern void LED_setLedOff(U8 id);

#endif