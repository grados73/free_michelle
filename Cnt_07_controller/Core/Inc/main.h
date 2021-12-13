/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define USER_BRD_LED1_Pin GPIO_PIN_13
#define USER_BRD_LED1_GPIO_Port GPIOC
#define RELAY_4_Pin GPIO_PIN_12
#define RELAY_4_GPIO_Port GPIOB
#define RELAY_3_Pin GPIO_PIN_13
#define RELAY_3_GPIO_Port GPIOB
#define RELAY_2_Pin GPIO_PIN_14
#define RELAY_2_GPIO_Port GPIOB
#define RELAY_1_Pin GPIO_PIN_15
#define RELAY_1_GPIO_Port GPIOB
#define USART_1_WIRE_DS_Pin GPIO_PIN_9
#define USART_1_WIRE_DS_GPIO_Port GPIOA
#define USER_LED_Pin GPIO_PIN_11
#define USER_LED_GPIO_Port GPIOA
#define LIGHT_4_Pin GPIO_PIN_4
#define LIGHT_4_GPIO_Port GPIOB
#define LIGHT_3_Pin GPIO_PIN_5
#define LIGHT_3_GPIO_Port GPIOB
#define LIGHT_2_Pin GPIO_PIN_6
#define LIGHT_2_GPIO_Port GPIOB
#define LIGHT_1_Pin GPIO_PIN_7
#define LIGHT_1_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
