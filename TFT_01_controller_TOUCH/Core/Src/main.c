/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @project		: free_michelle
  * @author			: grados73 - https://github.com/grados73
  * @purpose		: kontroler dotykowego wyswietlacza TFT do interfejsu komunikacji z
  * 					uzytkownikiem dla projektu sterownika akwarium
  ******************************************************************************
  **/
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* STANDARD LIBRARIES */
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
/* PRRIVATE FILES */
#include "TFT_ILI9341.h"
#include "GFX_Color.h"
#include "GFX_EnhancedFonts.h"
#include "XPT2064.h"
#include "functions.h"
#include "uartdma.h"
#include "parser.h"
#include "menuTFT.h"
#include "ds3231_for_stm32_hal.h"
/* PRRIVATE FONTS*/
#include "EnhancedFonts/arialBlack_20ptFontInfo.h"
#include "EnhancedFonts/arialBlack_11ptFontInfo.h"
#include "EnhancedFonts/ArialBlack_28pts_bold.h" //Bez polskich znakow!

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
uint8_t Msg[32];
UARTDMA_HandleTypeDef huartdma2;
uint8_t BufferReceive[64];
uint16_t Xread, Yread;
I2C_HandleTypeDef hi2c1;
//To update current displayed clock
extern uint8_t Time[3];
extern MenuTFTState State;

uint8_t THour, TMinutes, TSeconds;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_NVIC_Init(void);
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
  MX_SPI1_Init();
  MX_DMA_Init();
  MX_USART2_UART_Init();
  MX_SPI3_Init();
  MX_I2C1_Init();
  MX_TIM11_Init();

  /* Initialize interrupts */
  MX_NVIC_Init();
  /* USER CODE BEGIN 2 */
  //
  //Timer START
  HAL_TIM_Base_Start_IT(&htim11);
  // TFT controller INIT
  ILI9341_Init(&hspi1);
  // UART in DMA mode with use RingBuffer INIT
  UARTDMA_Init(&huartdma2, &huart2);
  // TFT touch controller INIT
  XPT2046_Init(&hspi3, EXTI9_5_IRQn);
  // RTC Initialization
  DS3231_Init(&hi2c1);
//  __disable_irq();
  DS3231_SetInterruptMode(DS3231_ALARM_INTERRUPT);
  DS3231_EnableOscillator(DS3231_ENABLED);
  DS3231_EnableAlarm2(DS3231_ENABLED);
  DS3231_SetAlarm2Mode(DS3231_A2_EVERY_M);


//  __enable_irq();

  // TO DO! - Tutaj przeprowadzić inicjalizację peryferiów i połączenia z drugim STMem

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	  if(UARTDMA_IsDataReceivedReady(&huartdma2))
	  {
		  UART_ParseLine(&huartdma2); // Parsing function
	  }

	  //
	  // TRANSMIT
	  //
	  UARTDMA_TransmitEvent(&huartdma2);

	  //
	  // TOUCH
	  //
	  XPT2046_Task();


	  MenuTFT();

//	  THour = DS3231_GetHour();
//	  TMinutes = DS3231_GetMinute();
//	  TSeconds = DS3231_GetSecond();



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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 12;
  RCC_OscInitStruct.PLL.PLLN = 96;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief NVIC Configuration.
  * @retval None
  */
static void MX_NVIC_Init(void)
{
  /* EXTI4_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);
  /* EXTI9_5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
  /* I2C1_EV_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(I2C1_EV_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);
  /* USART2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(USART2_IRQn);
  /* SPI3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SPI3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(SPI3_IRQn);
}

/* USER CODE BEGIN 4 */
// Periodic interrupt from TIMERS Callback
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM11)
	{
		HAL_GPIO_TogglePin(BP_USER_LED_GPIO_Port, BP_USER_LED_Pin);
		ChangeHourOnScreen();
	}
}

// Output interrupt from GPIO etc. Callback
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == TOUCH_IRQ_Pin)
	{
		XPT2046_IRQ();
	}

	if(GPIO_Pin == RTC_IRQ_Pin) // Interrupt from RTC - alarm one per minute
	{
		DS3231_ClearAlarm2Flag();

	}
}

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

