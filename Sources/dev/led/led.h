#ifndef _INC_LED_H
#define _INC_LED_H

#include "..\led.h"

#define LED_led1Off (~LED_led1On)
extern void LED_setLed1On();
extern void LED_setLed1Off();

#define LED_led2Off (~LED_led2On)
extern void LED_setLed2On();
extern void LED_setLed2Off();

#endif