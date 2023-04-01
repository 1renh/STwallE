/**
 ******************************************************************************
 * @file    bsp_ip_conf.h
 * @author  MEMS Application Team
 * @brief   BSP IP configuration file
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
#ifndef __BSP_IP_CONF_H__
#define __BSP_IP_CONF_H__

#ifdef __cplusplus
extern "C" {
#endif

  
#include "stm32g0xx_hal.h"
  
/* Exported variables --------------------------------------------------------*/
/* Exported defines ----------------------------------------------------------*/

#define LED12A1_I2C_Init                                    BSP_I2C_Init
#define LED12A1_I2C_DeInit                                  BSP_I2C_DeInit
#define LED12A1_I2C_Write                                   BSP_I2C_Write
#define LED12A1_I2C_Read                                    BSP_I2C_Read
#define LED12A1_Delay                                       HAL_Delay

#define LED12A1_I2C_HANDLE                                  hi2c1  
  
#ifdef __cplusplus
}
#endif

#endif /* __BSP_IP_CONF_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
