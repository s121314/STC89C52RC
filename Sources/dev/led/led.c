#include "led.h"

void LED_setLedOn(U8 id)
{
    switch(id)
    {
        case 1 : LED_setLed1On();break;
        case 2 : LED_setLed2On();break;
        default : ;
    }
}

void LED_setLedOff(U8 id)
{
    switch(id)
    {
        case 1 : LED_setLed1Off();break;
        case 2 : LED_setLed2Off();break;
        default : ;
    }
}