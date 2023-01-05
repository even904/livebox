#include "ws2812b.h"
#include "math.h"

uint8_t rgb[256][3] = {	{0,	  	0x0, 	0	}, //0
						{0x00,	0x00,	0x50}, //1
						{0x00,	0x50,	0x00}, //2
						{0x80,	0x80,	0x80}, //3
						{0x00,	0x00,	0x00}, //4
						{0x30,	0x30,	0x25}, //5
						};

uint16_t LED_BYTE_Buffer[PIXEL_MAX * 24 + 80 * 24]; 	/* 真正的数据 */

void WS2812_show(uint16_t n)
{
	uint32_t memaddr = PIXEL_MAX*24 + 80*24;
	uint32_t len = PIXEL_MAX*24;
	while (len <  memaddr)
	{
		LED_BYTE_Buffer[len] = 0;
		len++;
	}
	
	HAL_TIM_PWM_Start_DMA(&htim4, TIM_CHANNEL_1, (uint32_t *)&LED_BYTE_Buffer, memaddr );
}

void WS2812_send(uint8_t (*color)[3], uint16_t len)
{
	uint16_t i = 0;			                /* 循环标志 */
	uint32_t memaddr = 0;	                /* 数组位置标志 */
	uint16_t buffersize = 0;                /* 传输字节大小 */
	buffersize = (len*24)+80;	
	memaddr = 0;				

	while (len)
	{	
		for(i=0; i<8; i++) 
		{
			LED_BYTE_Buffer[memaddr] = ((color[0][1]<<i) & 0x0080) ? BIT_1:BIT_0;
			memaddr++;
		}
		for(i=0; i<8; i++) 
		{
			LED_BYTE_Buffer[memaddr] = ((color[0][0]<<i) & 0x0080) ? BIT_1:BIT_0;
			memaddr++;
		}
		for(i=0; i<8; i++) 
		{
			LED_BYTE_Buffer[memaddr] = ((color[0][2]<<i) & 0x0080) ? BIT_1:BIT_0;
			memaddr++;
		}
		len--;
	}
    
    while(memaddr < buffersize)
    {
        LED_BYTE_Buffer[memaddr] = 0;
        memaddr++;
    }

	HAL_TIM_PWM_Start_DMA(&htim4, TIM_CHANNEL_1, (uint32_t *)&LED_BYTE_Buffer, memaddr );
}

//画点
void set_pixel_color(uint8_t (*color)[3],uint16_t n)
{
	uint16_t i = 0;			                /* 循环标志 */
	uint32_t memaddr = n*24;	                /* 数组位置标志 */
	
		for(i=0; i<8; i++) 
		{
			LED_BYTE_Buffer[memaddr] = ((color[0][1]<<i) & 0x0080) ? BIT_1:BIT_0;
			memaddr++;
		}
		for(i=0; i<8; i++) 
		{
			LED_BYTE_Buffer[memaddr] = ((color[0][0]<<i) & 0x0080) ? BIT_1:BIT_0;
			memaddr++;
		}
		for(i=0; i<8; i++) 
		{
			LED_BYTE_Buffer[memaddr] = ((color[0][2]<<i) & 0x0080) ? BIT_1:BIT_0;
			memaddr++;
		}
		
//		WS2812_show(n);
}
//初始化
void Led_Matrix_Init(void)
{
	int i = 0;
	for (i = 0 ; i < 256 ; i++ )
	  {
		set_pixel_color(&rgb[0],i);
	  }
}

//全填充
void Led_Matrix_Fill(void)
{
	int i = 0;
	for (i = 0 ; i < 256 ; i++ )
	  {
		set_pixel_color(&rgb[3],i);
	  }
	 WS2812_show(256);
}

//缓存清屏
void Led_Matrix_Clear_All(void)
{
	int i = 0;
	for (i = 0 ; i < 256 ; i++ )
	  {
		set_pixel_color(&rgb[0],i);
	  }
}

//任意绘制一个点
//x： 0~15
//y： 0~15
void DrawPoint(uint8_t x,uint8_t y,uint8_t (*color)[3])
{
	x %= 16;
	y %= 16;
	uint8_t rowiseven = 0;//行号为偶数
	uint8_t n = 0;
	rowiseven = (y%2 == 0)?1 : 0;
	if (rowiseven)
	{
		n = y * 16 + x;
	}
	else
	{
		n = (y + 1) * 16 - x - 1;
	}
	set_pixel_color(color,n);
}

//圆心x0,y0，半径r
void DrawCircle(uint8_t x0,uint8_t y0,uint8_t r,uint8_t (*color)[3])
{
	uint8_t x = 0,y = 0;
	for (x = x0 - r ; x <= x0 + r ; x++)
	{
		y = sqrt(r*r - (x-x0)*(x-x0));
		DrawPoint(x ,(uint8_t) y0 + y, color);
		DrawPoint(x ,(uint8_t) y0 - y, color);
	}
}
//画线
void DrawLine(uint8_t x0,uint8_t y0,uint8_t x1,uint8_t y1,uint8_t (*color)[3])
{
	double x = 0.0 , y = 0.0 , k = 0.0;
	uint8_t i = 0;
	if (x0 == x1)
	{
		for  (i = y0;i < y1 ;i++)
		{
			DrawPoint(x0,i,color);
		}
	}
	else
	{
		k = (double)(y1-y0)/(double)(x1-x0);
		for(i = x0;i < x1;i++)
		{
			y = k*(double)(i - x0) + (double)y0;
			DrawPoint(i,(uint8_t)y,color);
		}
	}
	 WS2812_show(256);
}
//显示单色图片
void ShowImg(uint8_t (*img)[16],uint8_t (*color)[3])
{
	int m = 0 , n = 0;
	for (m = 0 ; m < 16 ; m++)
	{
		for (n = 0 ; n < 16;n++)
		{
			if (img[n][m] == 1)
			{
				DrawPoint(m,n,color);
			}else
			{
				DrawPoint(m,n,&rgb[0]);
			}
		}
	}
	WS2812_show(256);
}
//显示全彩图片
void Show_True_Color_Img(uint8_t (*img)[16][3])
{
	int m = 0 , n = 0 , color_channel = 0;
	uint8_t color[3];
	for (m = 0 ; m < 16 ; m++)
	{
		for (n = 0 ; n < 16; n++)
		{
			for (color_channel = 0;color_channel < 3;color_channel++)
			{
				color[color_channel] = img[n][m][color_channel];//颜色赋值
			}
			DrawPoint(m,n,&color);//彩图缓存
		}
	}
	WS2812_show(256);//显示图片
}


// Slightly different, this makes the rainbow equally distributed throughout
void WS281x_RainbowCycle(uint8_t wait, uint8_t (*rgb)[3]) {
  uint16_t i, j;
  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< PIXEL_MAX; i++) {
	  Color_Wheel(((i * 256 / PIXEL_MAX) + j) & 255 , rgb);
	  set_pixel_color(rgb,i);
    }
    WS2812_show(256);
    HAL_Delay(wait);
  }
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
void Color_Wheel(uint8_t wheelPos,uint8_t (* rgb)[3])
{
  wheelPos = 255 - wheelPos;
  if(wheelPos < 85) {
	  rgb[0][0] = 255 - wheelPos * 3;
	  rgb[0][1] = 0;
	  rgb[0][2] = wheelPos * 3;
  }
  if(wheelPos < 170) {
    wheelPos -= 85;
	  rgb[0][0] = 0;
	  rgb[0][1] = wheelPos * 3;
	  rgb[0][2] = 255 - wheelPos * 3;
  }
  wheelPos -= 170;
  	  rgb[0][0] = wheelPos * 3;
	  rgb[0][1] = 255 - wheelPos * 3;
	  rgb[0][2] = 0;
}

