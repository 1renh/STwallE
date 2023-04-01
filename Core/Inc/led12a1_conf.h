
/**
 ******************************************************************************
 * @file    led12a1_conf.h
 * @author  SRA Application Team
 * @version V1.0.0
 * @date    30-July-2021
 * @brief   This file contains definitions for the LED12A1 components bus interfaces
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under SLA0094 license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        https://www.st.com/SLA0094
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LED12A1_CONF_H__
#define __LED12A1_CONF_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32g0xx_hal.h"
#include "main.h"  


#include "stm32g0xx_hal_exti.h"

/* Global configuration ---------------------------------------------------*/

/* Defines ---------------------------------------------------------------*/

#define LED12A1_GPIO_PIN       GPIO_PIN_0
#define LED12A1_GPIO_PORT      GPIOC
#define LED12A1_GPIO_IRQn      EXTI0_1_IRQn
#define LED12A1_GPIO_IT_PRIO   1
#define LED12A1_GPIO_EXTI_LINE  ((uint32_t )EXTI_LINE_0)
#define LED12A1_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOC_CLK_ENABLE()
#ifdef __cplusplus
}
#endif

#endif /* __LED12A1_CONF_H__*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

