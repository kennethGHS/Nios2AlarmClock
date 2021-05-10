#ifndef _INTERRUPTHANDLERFORUAR_H_

#define _INTERRUPTHANDLERFORUAR_H_

#include "clock.h"

/************************************************** ***************************

 * Public function prototypes

 ************************************************** **************************/

void InitUart(unsigned int BaudRate, _clock *clock, volatile int *leds);

void IsrUart();

unsigned char EmptyUart();

unsigned char GetUart(void);

unsigned char PutUart(unsigned char in_char);

void parseReceived();

#endif //_INTERRUPTHANDLERFORUAR_H_
