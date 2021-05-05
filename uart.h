#ifndef _INTERRUPTHANDLERFORUAR_H_

#define _INTERRUPTHANDLERFORUAR_H_

/************************************************** ***************************

 * Public function prototypes

 ************************************************** **************************/

void InitUart(unsigned int BaudRate, volatile int * hour, volatile int * min, volatile int * sec);

void IsrUart();

unsigned char EmptyUart();

unsigned char GetUart(void);

unsigned char PutUart(unsigned char in_char);

void parseReceived();

#endif //_INTERRUPTHANDLERFORUAR_H_
