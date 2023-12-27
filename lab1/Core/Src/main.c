/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "adc.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "P10.h"
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
uint16_t buttonState;
uint16_t a = 16;
uint16_t b = 8;
uint16_t a1 = 0;
uint16_t b1 = 0;
uint16_t m = 2;
uint16_t n = 14;
uint16_t m1 = 3;
uint16_t n1 = 13;

uint16_t p = 0;
uint16_t o = 15;
uint16_t p1 = 31;
uint16_t o1 = 0;

uint16_t flag = 0;
uint16_t flag1 = 0;
uint16_t z;
uint16_t red;
uint16_t green;
uint16_t buttonstate;
uint16_t button = 0;
uint16_t c, count, delay, state2, delay1, delay2;

uint16_t Tim1IRQCount = 0;
uint16_t  AdcX = 0;
uint16_t  AdcY = 0;
Pixel pix[1];
Pixel pixleftUp;
Pixel pixrightBottom;
Pixel objleftUp;
Pixel objrightBottom;
Pixel objleftUp1;
Pixel objrightBottom1;
Pixel cubeleftUp;
Pixel cuberightBottom;
uint8_t data[16];

float Hz;
volatile uint32_t timer1=0;
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
   //uint8_t pData = 0b11111110;
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
  MX_ADC1_Init();
  MX_TIM1_Init();
  MX_ADC2_Init();
  MX_SPI1_Init();
  MX_SPI2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {{
	  buttonstate = HAL_GPIO_ReadPin(button1_GPIO_Port, button1_Pin);

	  HAL_ADC_Start_IT(&hadc1);
	  HAL_ADC_Start_IT(&hadc2);
	  HAL_ADC_PollForConversion(&hadc1, 10);
	  HAL_ADC_PollForConversion(&hadc2, 10);
	  AdcX = HAL_ADC_GetValue(&hadc1);
	  AdcY = HAL_ADC_GetValue(&hadc2);

	  pix[0].x = a;
	  pix[0].y = b;

	  objleftUp.x = m;
	  objleftUp.y = n;

	  objrightBottom.x = m1;
	  objrightBottom.y = n1;

	  cubeleftUp.x = p;
	  cubeleftUp.y = o;

	  cuberightBottom.x = p1;
	  cuberightBottom.y = o1;

	  if(flag == 1)
	  {
        m = a;
        n = b;
        m1 = a+1;
        n1 = b-1;
	  }

      if(b < b1 && a > a1)
      {
    	  pixleftUp.x = a1;
    	  pixleftUp.y = b1;

    	  pixrightBottom.x = a;
    	  pixrightBottom.y = b;

    	  if(a1 < m && b1 > n && a > m1 && b < n1 && buttonstate == 0)
    	  {
    		  flag = 1;
    	  }
      }

      if(b > b1 && a > a1)
      {
    	  pixleftUp.x = a1;
    	  pixleftUp.y = b;

    	  pixrightBottom.x = a;
    	  pixrightBottom.y = b1;

    	  if(a1 < m && b > n && a > m1 && b1 < n1 && buttonstate == 0)
    	  {
    		  flag = 1;
    	  }
      }

      if(b > b1 && a < a1)
      {
    	  pixleftUp.x = a;
    	  pixleftUp.y = b;

    	  pixrightBottom.x = a1;
    	  pixrightBottom.y = b1;

    	  if(a < m && b > n && a1 > m1 && b1 < n1 && buttonstate == 0)
    	  {
    		  flag = 1;
    	  }
      }

      if(b < b1 && a < a1)
      {
    	  pixleftUp.x = a;
    	  pixleftUp.y = b1;

    	  pixrightBottom.x = a1;
    	  pixrightBottom.y = b;

    	  if(a < m && b1 > n && a1 > m1 && b < n1 && buttonstate == 0)
    	  {
    		  flag = 1;
    	  }
      }


	  delay1++;

	   if(buttonstate == 0 && button == 0 && z == 0)
	      {
		    if(delay1 > 2000)
		    {
		      button=1;
	    	  a1 = a;
	    	  b1 = b;
		      delay1 = 0;
		    }

	      }

	   if(buttonstate == 1 && button == 0)
	      {
	    	  a1 = a;
	    	  b1 = b;
	      }

	   if(buttonstate == 1 && button == 1 && z == 0)
	  	      {
      		    if(delay1 > 2000)
      		    {
                  z = 1;
      		      delay1 = 0;
      		    }
	  	      }

	   if(buttonstate == 0 && button == 1 && z == 1)
	      {
 		    if(delay1 > 2000)
 		    {
 		      button=0;
 		      a1 = a;
 		      b1 = b;
 		      z = 0;
 		      delay1 = 0;
 		    }
	      }

	   if(buttonstate == 0 && ((a == m && b == n) || (a == m1 && b == n1) || (a == m1 && b == (n1 + 1)) || (a == (m1 - 1) && b == n1)) && flag == 0)
	   {
		   button = 0;
	       a1 = a;
	       b1 = b;
		   flag = 1;
		   HAL_Delay(500);
	   }

	   if(buttonstate == 1 && ((a == m && b == n) || (a == m1 && b == n1) || (a == m1 && b == (n1 + 1)) || (a == (m1 - 1) && b == n1)) && flag == 1 && flag1 ==0)
	  	   {
		   flag1 = 1;
		   button = 0;
	       a1 = a;
	       b1 = b;
	  	   HAL_Delay(200);
	  	   }
	   if(buttonstate == 0 && ((a == m && b == n) || (a == m1 && b == n1) || (a == m1 && b == (n1 + 1)) || (a == (m1 - 1) && b == n1)) && flag1 == 1)
	   	  	   {
	   		   flag = 0;
	   		   flag1 = 0;
			   button = 0;
		       a1 = a;
		       b1 = b;
	   	  	   HAL_Delay(200);
	   	  	   }

	           delay2++;


	          clearScreen((uint8_t*)data);
	  	      if(button == 1)
	  	      {
	  	    	  drawRect(pixleftUp, pixrightBottom, (uint8_t*)data, P10AB_11);
	  	      }
	  	      if(flag == 1)
	  	      {
		  	      drawRect(objleftUp, objrightBottom, (uint8_t*)data, P10AB_11);
		  	      drawRect(cubeleftUp, cuberightBottom, (uint8_t*)data, P10AB_11);
	  	      }
	  	      if(flag == 0)
	  	      {
		  	      drawRect(objleftUp, objrightBottom, (uint8_t*)data, P10AB_11);
	  	      }
	  		  drawPixels((Pixel*)pix, 1, (uint8_t*)data, P10AB_11);
	  		  HAL_GPIO_WritePin(GPIOD, nOE_Pin, GPIO_PIN_RESET);
	  		  HAL_GPIO_WritePin(GPIOD, SCLK_Pin, GPIO_PIN_RESET);
	  		  HAL_GPIO_WritePin(GPIOD, A_Channel_Pin, GPIO_PIN_SET);
	  		  HAL_GPIO_WritePin(GPIOD, B_Channel_Pin, GPIO_PIN_SET);
	  		  HAL_SPI_Transmit(&hspi2, (uint8_t*)data, 16, 10);
	  		  HAL_GPIO_WritePin(GPIOD, SCLK_Pin, GPIO_PIN_SET);
	  		  HAL_GPIO_WritePin(GPIOD, nOE_Pin, GPIO_PIN_SET);

	  		  clearScreen((uint8_t*)data);
	  	      if(button == 1)
	  	      {
	  	    	  drawRect(pixleftUp, pixrightBottom, (uint8_t*)data, P10AB_10);
	  	      }
	  	      if(flag == 1)
	  	      {
		  	      drawRect(objleftUp, objrightBottom, (uint8_t*)data, P10AB_10);
		  	      drawRect(cubeleftUp, cuberightBottom, (uint8_t*)data, P10AB_10);
	  	      }
	  	      if(flag == 0)
	  	      {
		  	      drawRect(objleftUp, objrightBottom, (uint8_t*)data, P10AB_10);
	  	      }
	  		  drawPixels((Pixel*)pix, 1, (uint8_t*)data, P10AB_10);
	  		  HAL_GPIO_WritePin(GPIOD, nOE_Pin, GPIO_PIN_RESET);
	  		  HAL_GPIO_WritePin(GPIOD, SCLK_Pin, GPIO_PIN_RESET);
	  		  HAL_GPIO_WritePin(GPIOD, A_Channel_Pin, GPIO_PIN_RESET);
	  		  HAL_GPIO_WritePin(GPIOD, B_Channel_Pin, GPIO_PIN_SET);
	  		  HAL_SPI_Transmit(&hspi2, (uint8_t*)data, 16, 10);
	  		  HAL_GPIO_WritePin(GPIOD, SCLK_Pin, GPIO_PIN_SET);
	  		  HAL_GPIO_WritePin(GPIOD, nOE_Pin, GPIO_PIN_SET);

	  		  clearScreen((uint8_t*)data);
	  	      if(button == 1)
	  	      {
	  	    	  drawRect(pixleftUp, pixrightBottom, (uint8_t*)data, P10AB_01);
	  	      }
	  	      if(flag == 1)
	  	      {
		  	      drawRect(objleftUp, objrightBottom, (uint8_t*)data, P10AB_01);
		  	      drawRect(cubeleftUp, cuberightBottom, (uint8_t*)data, P10AB_01);
	  	      }
	  	      if(flag == 0)
	  	      {
		  	      drawRect(objleftUp, objrightBottom, (uint8_t*)data, P10AB_01);
	  	      }
	  		  drawPixels((Pixel*)pix, 1, (uint8_t*)data, P10AB_01);
	  		  HAL_GPIO_WritePin(GPIOD, nOE_Pin, GPIO_PIN_RESET);
	  		  HAL_GPIO_WritePin(GPIOD, SCLK_Pin, GPIO_PIN_RESET);
	  		  HAL_GPIO_WritePin(GPIOD, A_Channel_Pin, GPIO_PIN_SET);
	  		  HAL_GPIO_WritePin(GPIOD, B_Channel_Pin, GPIO_PIN_RESET);
	  		  HAL_SPI_Transmit(&hspi2, (uint8_t*)data, 16, 10);
	  		  HAL_GPIO_WritePin(GPIOD, SCLK_Pin, GPIO_PIN_SET);
	  		  HAL_GPIO_WritePin(GPIOD, nOE_Pin, GPIO_PIN_SET);

	  		  clearScreen((uint8_t*)data);
	  	      if(button == 1)
	  	      {
	  	    	  drawRect(pixleftUp, pixrightBottom, (uint8_t*)data, P10AB_00);
	  	      }
	  	      if(flag == 1)
	  	      {
		  	      drawRect(objleftUp, objrightBottom, (uint8_t*)data, P10AB_00);
		  	      drawRect(cubeleftUp, cuberightBottom, (uint8_t*)data, P10AB_00);
	  	      }
	  	      if(flag == 0)
	  	      {
		  	      drawRect(objleftUp, objrightBottom, (uint8_t*)data, P10AB_00);
	  	      }
	  		  drawPixels((Pixel*)pix, 1, (uint8_t*)data, P10AB_00);
	  		  HAL_GPIO_WritePin(GPIOD, nOE_Pin, GPIO_PIN_RESET);
	  		  HAL_GPIO_WritePin(GPIOD, SCLK_Pin, GPIO_PIN_RESET);
	  		  HAL_GPIO_WritePin(GPIOD, A_Channel_Pin, GPIO_PIN_RESET);
	  		  HAL_GPIO_WritePin(GPIOD, B_Channel_Pin, GPIO_PIN_RESET);
	  		  HAL_SPI_Transmit(&hspi2, (uint8_t*)data, 16, 10);
	  		  HAL_GPIO_WritePin(GPIOD, SCLK_Pin, GPIO_PIN_SET);
	  		  HAL_GPIO_WritePin(GPIOD, nOE_Pin, GPIO_PIN_SET);

      delay++;

      if (a == 32){
    	  a=31;
      }
      if (b == 16){
    	  b=15;
      }
      if (a > 100){
    	  a=0;
      }
      if (b > 100){
    	  b=0;
      }
      if((AdcX > 3180) && (AdcY < 3235 && AdcY > 2700)){ // вправо
      if(delay > 1000)
      {
    	  a = a+1;
    	  delay = 0;
      }
      }
      if((AdcX < 2700) && (AdcY < 3235 && AdcY > 2700)){ // влево
          if(delay > 1000)
          {
        	  a = a-1;
        	  delay = 0;
          }
      }
      if((AdcX < 3180 && AdcX > 2700) && (AdcY < 2700)){ // вверх
          if(delay > 1000)
          {
        	  b = b+1;
        	  delay = 0;
          }
      }
      if((AdcX < 3180 && AdcX > 2700) && (AdcY > 3235)){ // вниз
          if(delay > 1000)
          {
        	  b = b-1;
        	  delay = 0;
          }
      }
      if((AdcX > 3180) && (AdcY < 2700)){ // вправо-вверх
          if(delay > 1000)
          {
              a = a+1;
              b = b+1;
        	  delay = 0;
          }
      }
      if((AdcX < 2700) && (AdcY < 2700)){ // влево-вверх
          if(delay > 1000)
          {
              a = a-1;
              b = b+1;
        	  delay = 0;
          }
      }
      if((AdcX > 3180) && (AdcY > 3235)){ // вправо-вниз
          if(delay > 1000)
          {
              a = a+1;
              b = b-1;
        	  delay = 0;
          }
      }
      if((AdcX < 2700) && (AdcY > 3235)){ // влево-вниз
          if(delay > 1000)
          {
              a = a-1;
              b = b-1;
        	  delay = 0;
          }
      }
	  }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
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
