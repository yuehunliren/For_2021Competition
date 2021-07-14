#ifndef __GY-53_H__
#define __GY-53_H__
#include "main.h"
#include "usart.h"
#include <string.h>
#include <stdlib.h>
int16_t filter(int16_t num);
extern uint8_t Buffer[8];
extern uint8_t aRxBuffer;
extern uint8_t Receive_ok;
#endif // __GY-53_H__