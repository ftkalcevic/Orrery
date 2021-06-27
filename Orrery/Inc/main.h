/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2020 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#define countof(x)	(sizeof(x)/sizeof((x)[0]))
	
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
#define GPIO_ENABLE_Pin GPIO_PIN_13
#define GPIO_ENABLE_GPIO_Port GPIOC
#define GPIO_DIR0_Pin GPIO_PIN_0
#define GPIO_DIR0_GPIO_Port GPIOA
#define GPIO_STEP0_Pin GPIO_PIN_1
#define GPIO_STEP0_GPIO_Port GPIOA
#define GPIO_DIR1_Pin GPIO_PIN_2
#define GPIO_DIR1_GPIO_Port GPIOA
#define GPIO_STEP1_Pin GPIO_PIN_3
#define GPIO_STEP1_GPIO_Port GPIOA
#define GPIO_DIR2_Pin GPIO_PIN_4
#define GPIO_DIR2_GPIO_Port GPIOA
#define GPIO_STEP2_Pin GPIO_PIN_5
#define GPIO_STEP2_GPIO_Port GPIOA
#define GPIO_DIR3_Pin GPIO_PIN_6
#define GPIO_DIR3_GPIO_Port GPIOA
#define GPIO_STEP3_Pin GPIO_PIN_7
#define GPIO_STEP3_GPIO_Port GPIOA
#define ADC_BUTTON_Pin GPIO_PIN_0
#define ADC_BUTTON_GPIO_Port GPIOB
#define ADC_JOY_Pin GPIO_PIN_1
#define ADC_JOY_GPIO_Port GPIOB
#define GPIO_BOOT1_Pin GPIO_PIN_2
#define GPIO_BOOT1_GPIO_Port GPIOB
#define GPIO_SPI_NSS_Pin GPIO_PIN_12
#define GPIO_SPI_NSS_GPIO_Port GPIOB
#define GPIO_STEP4_Pin GPIO_PIN_14
#define GPIO_STEP4_GPIO_Port GPIOB
#define GPIO_RGB_LED_Pin GPIO_PIN_8
#define GPIO_RGB_LED_GPIO_Port GPIOA
#define GPIO_DIR4_Pin GPIO_PIN_9
#define GPIO_DIR4_GPIO_Port GPIOA
#define GPIO_Display_RST_Pin GPIO_PIN_10
#define GPIO_Display_RST_GPIO_Port GPIOA
#define GPIO_STEP5_Pin GPIO_PIN_11
#define GPIO_STEP5_GPIO_Port GPIOA
#define GPIO_DIR5_Pin GPIO_PIN_12
#define GPIO_DIR5_GPIO_Port GPIOA
#define GPIO_DIR6_Pin GPIO_PIN_15
#define GPIO_DIR6_GPIO_Port GPIOA
#define GPIO_STEP6_Pin GPIO_PIN_3
#define GPIO_STEP6_GPIO_Port GPIOB
#define GPIO_DIR7_Pin GPIO_PIN_4
#define GPIO_DIR7_GPIO_Port GPIOB
#define GPIO_STEP7_Pin GPIO_PIN_5
#define GPIO_STEP7_GPIO_Port GPIOB
#define GPIO_DIR8_Pin GPIO_PIN_6
#define GPIO_DIR8_GPIO_Port GPIOB
#define GPIO_STEP8_Pin GPIO_PIN_7
#define GPIO_STEP8_GPIO_Port GPIOB
#define GPIO_STEP9_Pin GPIO_PIN_8
#define GPIO_STEP9_GPIO_Port GPIOB
#define GPIO_DIR9_Pin GPIO_PIN_9
#define GPIO_DIR9_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
extern CRC_HandleTypeDef hcrc;
extern I2C_HandleTypeDef hi2c2;
extern ADC_HandleTypeDef hadc1;
extern SPI_HandleTypeDef hspi2;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
