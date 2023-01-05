#ifndef WS2812B_H
#define WS2812B_H

#include "tim.h"

#define PIXEL_MAX 256	

#define BIT_1                   50 /* 1比较值为50 */
#define BIT_0                   25 /* 0比较值为25 */

extern uint8_t rgb[256][3] ;

void WS2812_send(uint8_t (*color)[3], uint16_t len);

void set_pixel_color(uint8_t (*color)[3],uint16_t n);

void Led_Matrix_Init(void);
	
void DrawPoint(uint8_t x,uint8_t y,uint8_t (*color)[3]);

void DrawCircle(uint8_t x0,uint8_t y0,uint8_t r,uint8_t (*color)[3]);

void DrawLine(uint8_t x0,uint8_t y0,uint8_t x1,uint8_t y1,uint8_t (*color)[3]);

void ShowImg(uint8_t (*img)[16],uint8_t (*color)[3]);

void Show_True_Color_Img(uint8_t (*img)[16][3]);

void Color_Wheel(uint8_t wheelPos,uint8_t (* rgb)[3]);

void WS281x_RainbowCycle(uint8_t wait, uint8_t (*rgb)[3]);

void Led_Matrix_Fill(void);

void Led_Matrix_Clear_All(void);

void WS2812_show(uint16_t n);

#endif

