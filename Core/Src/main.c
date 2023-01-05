/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ws2812b.h"
#include "math.h"
#include "my_lib.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */

	int i = 0;
	Led_Matrix_Init();
	uint8_t ranbow[7][3] = {{200,0,0},{200,135,0},{200,200,0},{0,200,0},{0,200,200},{0,0,200},{109,0,200}};
	uint8_t ranbow_ll[7][3] = {{100,0,0},{100,75,0},{100,100,0},{0,100,0},{0,100,100},{0,0,100},{59,0,100}};
  /* USER CODE END 2 */
	uint8_t test2_img[16][16][3] = {
	{{34 ,34 ,34 ,},{34 ,34 ,34 ,},{34 ,34 ,34 ,},{34 ,34 ,34 ,},{33 ,33 ,33 ,},{32 ,31 ,31 ,},{32 ,27 ,28 ,},{32 ,24 ,26 ,},{32 ,23 ,25 ,},{32 ,23 ,25 ,},{32 ,25 ,27 ,},{32 ,29 ,30 ,},{33 ,33 ,33 ,},{33 ,34 ,34 ,},{34 ,34 ,34 ,},{34 ,34 ,34 ,},},
	{{34 ,34 ,34 ,},{32 ,33 ,33 ,},{31 ,33 ,33 ,},{32 ,32 ,32 ,},{31 ,28 ,28 ,},{32 ,23 ,25 ,},{33 ,21 ,24 ,},{33 ,22 ,24 ,},{33 ,22 ,25 ,},{33 ,22 ,25 ,},{33 ,21 ,24 ,},{32 ,22 ,24 ,},{32 ,25 ,27 ,},{32 ,31 ,31 ,},{33 ,34 ,34 ,},{34 ,34 ,34 ,},},
	{{33 ,34 ,34 ,},{25 ,30 ,32 ,},{9 ,23 ,31 ,},{20 ,22 ,27 ,},{32 ,21 ,23 ,},{33 ,21 ,23 ,},{33 ,21 ,24 ,},{33 ,22 ,25 ,},{33 ,22 ,25 ,},{33 ,22 ,25 ,},{33 ,22 ,24 ,},{33 ,20 ,24 ,},{32 ,20 ,23 ,},{32 ,26 ,27 ,},{32 ,34 ,33 ,},{33 ,34 ,34 ,},},
	{{33 ,32 ,33 ,},{22 ,24 ,26 ,},{6 ,18 ,22 ,},{20 ,19 ,23 ,},{33 ,21 ,24 ,},{33 ,23 ,25 ,},{32 ,24 ,26 ,},{33 ,23 ,26 ,},{33 ,22 ,25 ,},{32 ,23 ,25 ,},{32 ,24 ,26 ,},{32 ,23 ,25 ,},{33 ,22 ,25 ,},{32 ,26 ,27 ,},{32 ,30 ,30 ,},{33 ,33 ,33 ,},},
	{{32 ,28 ,31 ,},{27 ,24 ,19 ,},{22 ,19 ,5 ,},{26 ,19 ,14 ,},{31 ,19 ,24 ,},{32 ,23 ,26 ,},{33 ,25 ,27 ,},{33 ,24 ,26 ,},{32 ,22 ,25 ,},{32 ,23 ,25 ,},{32 ,25 ,26 ,},{32 ,23 ,25 ,},{32 ,22 ,24 ,},{33 ,23 ,25 ,},{32 ,24 ,25 ,},{32 ,32 ,32 ,},},
	{{32 ,30 ,33 ,},{32 ,31 ,26 ,},{27 ,21 ,10 ,},{26 ,16 ,13 ,},{29 ,17 ,22 ,},{33 ,22 ,26 ,},{32 ,22 ,25 ,},{30 ,20 ,23 ,},{29 ,20 ,22 ,},{30 ,20 ,23 ,},{32 ,22 ,25 ,},{30 ,20 ,22 ,},{29 ,18 ,21 ,},{32 ,20 ,23 ,},{32 ,22 ,24 ,},{32 ,29 ,30 ,},},
	{{34 ,34 ,34 ,},{33 ,34 ,34 ,},{31 ,24 ,26 ,},{27 ,15 ,19 ,},{27 ,15 ,19 ,},{32 ,21 ,24 ,},{31 ,20 ,23 ,},{27 ,17 ,19 ,},{25 ,18 ,18 ,},{27 ,17 ,20 ,},{29 ,17 ,21 ,},{25 ,17 ,18 ,},{25 ,17 ,18 ,},{31 ,20 ,23 ,},{33 ,22 ,24 ,},{31 ,25 ,26 ,},},
	{{33 ,34 ,34 ,},{33 ,33 ,33 ,},{34 ,26 ,30 ,},{29 ,17 ,21 ,},{25 ,14 ,17 ,},{31 ,19 ,23 ,},{26 ,15 ,18 ,},{16 ,10 ,13 ,},{19 ,16 ,16 ,},{26 ,18 ,20 ,},{26 ,15 ,18 ,},{17 ,14 ,14 ,},{15 ,14 ,15 ,},{28 ,20 ,22 ,},{32 ,20 ,23 ,},{28 ,21 ,23 ,},},
	{{33 ,34 ,34 ,},{33 ,32 ,32 ,},{33 ,25 ,27 ,},{28 ,17 ,20 ,},{24 ,11 ,16 ,},{29 ,16 ,20 ,},{19 ,12 ,15 ,},{6 ,9 ,13 ,},{15 ,18 ,20 ,},{28 ,22 ,21 ,},{26 ,19 ,18 ,},{15 ,16 ,17 ,},{13 ,16 ,19 ,},{27 ,21 ,22 ,},{30 ,17 ,20 ,},{27 ,20 ,22 ,},},
	{{34 ,34 ,34 ,},{33 ,32 ,32 ,},{33 ,24 ,26 ,},{27 ,15 ,19 ,},{23 ,10 ,15 ,},{25 ,12 ,16 ,},{23 ,18 ,19 ,},{18 ,22 ,23 ,},{23 ,25 ,25 ,},{30 ,27 ,24 ,},{30 ,27 ,25 ,},{25 ,26 ,25 ,},{25 ,26 ,26 ,},{28 ,22 ,22 ,},{26 ,13 ,17 ,},{28 ,22 ,24 ,},},
	{{34 ,34 ,34 ,},{33 ,32 ,32 ,},{32 ,23 ,25 ,},{26 ,12 ,17 ,},{23 ,10 ,15 ,},{26 ,14 ,18 ,},{30 ,23 ,24 ,},{33 ,32 ,30 ,},{32 ,31 ,29 ,},{32 ,30 ,28 ,},{33 ,31 ,29 ,},{34 ,33 ,31 ,},{33 ,32 ,30 ,},{27 ,17 ,19 ,},{24 ,12 ,17 ,},{29 ,27 ,28 ,},},
	{{34 ,34 ,34 ,},{33 ,32 ,32 ,},{31 ,21 ,24 ,},{24 ,10 ,15 ,},{24 ,11 ,16 ,},{29 ,18 ,22 ,},{28 ,20 ,21 ,},{30 ,28 ,27 ,},{34 ,34 ,32 ,},{33 ,30 ,28 ,},{33 ,30 ,28 ,},{33 ,33 ,32 ,},{30 ,26 ,27 ,},{24 ,13 ,16 ,},{26 ,19 ,21 ,},{32 ,32 ,32 ,},},
	{{34 ,34 ,34 ,},{33 ,32 ,32 ,},{29 ,19 ,22 ,},{24 ,9 ,14 ,},{22 ,8 ,14 ,},{28 ,16 ,20 ,},{24 ,15 ,17 ,},{26 ,19 ,18 ,},{32 ,28 ,25 ,},{31 ,28 ,26 ,},{30 ,26 ,25 ,},{28 ,21 ,22 ,},{24 ,12 ,16 ,},{27 ,15 ,19 ,},{31 ,28 ,29 ,},{34 ,34 ,34 ,},},
	{{34 ,34 ,34 ,},{32 ,30 ,31 ,},{28 ,17 ,20 ,},{24 ,8 ,14 ,},{21 ,8 ,13 ,},{24 ,13 ,17 ,},{25 ,14 ,17 ,},{25 ,12 ,14 ,},{28 ,19 ,19 ,},{27 ,23 ,22 ,},{22 ,16 ,17 ,},{21 ,9 ,12 ,},{23 ,9 ,14 ,},{30 ,18 ,21 ,},{33 ,29 ,30 ,},{34 ,34 ,34 ,},},
	{{33 ,33 ,33 ,},{30 ,27 ,28 ,},{27 ,14 ,18 ,},{26 ,15 ,18 ,},{25 ,16 ,18 ,},{24 ,14 ,17 ,},{25 ,13 ,17 ,},{25 ,13 ,16 ,},{26 ,18 ,19 ,},{27 ,21 ,22 ,},{26 ,17 ,18 ,},{27 ,17 ,19 ,},{28 ,17 ,20 ,},{27 ,15 ,19 ,},{31 ,26 ,27 ,},{33 ,33 ,33 ,},},
	{{33 ,33 ,33 ,},{28 ,23 ,25 ,},{27 ,17 ,20 ,},{32 ,27 ,27 ,},{32 ,27 ,26 ,},{27 ,18 ,20 ,},{26 ,15 ,18 ,},{29 ,19 ,20 ,},{29 ,21 ,22 ,},{28 ,21 ,22 ,},{32 ,24 ,25 ,},{33 ,26 ,26 ,},{28 ,18 ,21 ,},{25 ,15 ,18 ,},{31 ,26 ,28 ,},{34 ,33 ,33 ,},},
};
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
//	Led_Matrix_Fill();

	uint8_t x = 0 ,y = 0,num = 0;
	uint8_t nocolor[3] = {0,0,0};
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
//	  Sin_Series(sinwave,time_flag);
//	  ShowImg(sinwave,&rgb[5]);
//	  time_flag++;
////	  DrawLine(0,15,0,15,&rgb[5]);
//	//Led_Matrix_Clear_All();
//	for(int i = 0 ; i < 15 ; i++)
//	  {
//		DrawPoint(time_flag % 16,i,&ranbow_ll[time_flag % 7]);
//	  }
//	  WS2812_show(256);
	  //Show_True_Color_Img(test2_img);
	  
	  Show_Number(0,0,0,&ranbow_ll[6]);
	  Show_Number(1,8,0,&ranbow_ll[6]);
//	  
//	WS2812_show(256);
//	  
//	HAL_Delay(FLASH_PERIOD);
	
//	Show_True_Color_Img(test2_img);
	
	HAL_Delay(FLASH_PERIOD);
	  
	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
