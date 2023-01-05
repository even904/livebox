#ifndef MY_LIB_H
#define MY_LIB_H

#include "math.h"
#include "main.h"

#include "ws2812b.h"

uint8_t Sin_Series(uint8_t (*img)[16],uint32_t t);
void Show_Number(uint8_t num,uint8_t x,uint8_t y,uint8_t (*rgb)[3]);

extern uint16_t number[16];
#endif