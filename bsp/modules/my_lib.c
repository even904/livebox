#include "my_lib.h"

uint8_t series[8] = {0};
uint8_t Sin_Series(uint8_t (*img)[16],uint32_t t)
{
	
	int i = 0;
	double time = (double) t * FLASH_PERIOD / 1000.0f;
	double temp;
	temp = 8 * sin( 0.3927 * time) + 8;
	for(i = 0;i < 16;i++)
	{
		series[i] = (uint8_t)temp;
	}
	
	int m = 0 , n = 0;
	for (m = 0 ; m < 16 ; m++)
	{
		for (n = 0 ; n < 16;n++)
		{
			img[m][n] = 0;
		}
	}
	for(n = 0 ; n < series[0] ; n++)
	{
		img[0][n] = 1;
	}
	
}

/**
 * @LastEditors: Even
 * @Date: 2022-12-26 12:04:57
 * @Description: number encoding
 */
uint16_t number[16] = {0x7E3F,0x43F1,0x5EBD,0x7EB5,0x7C87,0x76B7,0x76BF,0x7C21,//0~7
					   0xFEBF,0xFEB7,};//8~F

/**
 * @LastEditors: Even
 * @Date: 2022-12-26 12:01:03
 * @Description: show number 5*3
 * @param {uint8_t} num
 * @param {uint8_t} x
 * @param {uint8_t} y 
 */
void Show_Number(uint8_t num,uint8_t x,uint8_t y,uint8_t (*rgb)[3])
{
	uint8_t m = x,n = y;
	uint8_t nocolor[3] = {0,0,0};
	uint16_t k = 1;
	for (m = x; m < x+3; m++)
	{
		for(n = y; n < y+5 ; n++)
		{
			if((number[num] & k) != 0)
				DrawPoint(m,n,rgb);
			else
				DrawPoint(m,n,&nocolor);
			k = k << 1;
		}
	}
	WS2812_show(256);
}

/***/
	
uint8_t YueLu[16][16] = {
	{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0},//0
	{0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0},//1
	{0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},//2
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0},//3
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0},//4
	{0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0},//5
	{0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0},//6
	{0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0},//7
	{0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0},//8
	{0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0},//9
	{0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0},//10
	{0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0},//11
	{0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0},//12
	{0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0},//13
	{0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0},//14
	{0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},//15
};

uint8_t number1[16][16] = {
	{0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
	{1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
	{0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
};

uint8_t number2[16][16] = {
	{0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
	{0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
	{0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
	{0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0},
	{1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1},
	{0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
	{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
};


	
uint8_t Light_level[1][3] = {{0x00,0x00,0x00}};
uint8_t light_level = 0;

uint8_t R = 255,G = 0,B = 159,k = 0;

	
	
volatile uint32_t time_flag = 0;
uint8_t sample_series[16] = {0};

uint8_t sinwave[16][16] = {{0}};

uint8_t test_img[16][16][3] = {
	{{200,0,0},{200,135,0},{200,200,0},{0,200,0},{0,200,200},{0,0,200},{109,0,200}},
	{{200,0,0},{200,135,0},{200,200,0},{0,200,0},{0,200,200},{0,0,200},{109,0,200}},
	{{200,0,0},{200,135,0},{200,200,0},{0,200,0},{0,200,200},{0,0,200},{109,0,200}},
	{{200,0,0},{200,135,0},{200,200,0},{0,200,0},{0,200,200},{0,0,200},{109,0,200}},
	{{200,0,0},{200,135,0},{200,200,0},{0,200,0},{0,200,200},{0,0,200},{109,0,200}},
	{{200,0,0},{200,135,0},{200,200,0},{0,200,0},{0,200,200},{0,0,200},{109,0,200}},
	{{100,0,0},{100,75,0},{100,100,0},{0,100,0},{0,100,100},{0,0,100},{59,0,100}},
	{{100,0,0},{100,75,0},{100,100,0},{0,100,0},{0,100,100},{0,0,100},{59,0,100}},
	{{100,0,0},{100,75,0},{100,100,0},{0,100,0},{0,100,100},{0,0,100},{59,0,100}},
	{{100,0,0},{100,75,0},{100,100,0},{0,100,0},{0,100,100},{0,0,100},{59,0,100}},
};

