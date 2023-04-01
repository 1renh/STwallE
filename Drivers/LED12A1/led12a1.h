/**
******************************************************************************
* @file    led12a1.h
* @author  SRA - NOIDA
* @version v1.0.0
* @date    30-Jun-21
* @brief   This is header file for led12a1.c.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef LED12A1_H
#define LED12A1_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "led1202.h"
#include "bsp_ip_conf.h"
 
/* Exported constants --------------------------------------------------------*/   
#define LED1202_DEV1_7BIT_ADDR  (0x58)
#define LED1202_DEV2_7BIT_ADDR  (0x59)
#define LED1202_DEV3_7BIT_ADDR  (0x5A)
#define LED1202_DEV4_7BIT_ADDR  (0x5B)
#define LED1202_GLOBAL_7BIT_ADDR  (0x5C)

#define LED1202_I2C_BUS                 0U   
#define LED1202_I2C_ADDR                LED1202_GLOBAL_7BIT_ADDR
#define TIMEOUT_DURATION 1000
     
/* Common Error codes */
#define BSP_ERROR_NONE                    0
#define BSP_ERROR_NO_INIT                -1
#define BSP_ERROR_WRONG_PARAM            -2
#define BSP_ERROR_BUSY                   -3
#define BSP_ERROR_PERIPH_FAILURE         -4
#define BSP_ERROR_COMPONENT_FAILURE      -5
#define BSP_ERROR_UNKNOWN_FAILURE        -6
#define BSP_ERROR_UNKNOWN_COMPONENT      -7
#define BSP_ERROR_BUS_FAILURE            -8
#define BSP_ERROR_CLOCK_FAILURE          -9
#define BSP_ERROR_MSP_FAILURE            -10

   
/* Exported types ------------------------------------------------------------*/   
typedef enum 
{
  LED_DEVICE1 = 0x00,
  LED_DEVICE2 = 0x01,
  LED_DEVICE3 = 0x02,
  LED_DEVICE4 = 0x03,
  LED_DEVICE_ALL
}TypedefEnumDevAddr;


typedef enum
{
  LED_CHANNEL_0    =   ((uint16_t)0x0001U),  /* Channel 0 selected    */
  LED_CHANNEL_1    =   ((uint16_t)0x0002U),  /* Channel 1 selected    */
  LED_CHANNEL_2    =   ((uint16_t)0x0004U),  /* Channel 2 selected    */
  LED_CHANNEL_3    =   ((uint16_t)0x0008U),  /* Channel 3 selected    */
  LED_CHANNEL_4    =   ((uint16_t)0x0010U),  /* Channel 4 selected    */
  LED_CHANNEL_5    =   ((uint16_t)0x0020U),  /* Channel 5 selected    */
  LED_CHANNEL_6    =   ((uint16_t)0x0040U),  /* Channel 6 selected    */
  LED_CHANNEL_7    =   ((uint16_t)0x0080U),  /* Channel 7 selected    */
  LED_CHANNEL_8    =   ((uint16_t)0x0100U),  /* Channel 8 selected    */
  LED_CHANNEL_9    =   ((uint16_t)0x0200U),  /* Channel 9 selected    */
  LED_CHANNEL_10   =   ((uint16_t)0x0400U),  /* Channel 10 selected   */
  LED_CHANNEL_11   =   ((uint16_t)0x0800U),  /* Channel 11 selected   */
  LED_CHANNEL_ALL  =   ((uint16_t)0x0FFFU)  /* All Channel  selected */    
} TypeDefChannel;

/* Exported constants --------------------------------------------------------*/  
extern I2C_HandleTypeDef hi2c1;
extern int32_t TmpStatus;
   
/* Exported functions ------------------------------------------------------- */ 
/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup LED12A1 LED12A1
  * @{
  */
    
/** @defgroup LED12A1 LED12A1
  * @{
  */ 
   
/** @defgroup LED12A1_Exported_Variables LED12A1 Exported Variables
  * @{
  */
extern LED1202_Object_TypeDef LED1202Obj;

/** @defgroup LED12A1_Exported_Variables LED12A1 Exported Functions
  * @{
  */
void LED12A1_GPIO_Init(void);
int32_t LED12A1_Init( void );
int32_t  BSP_I2C_Init(void);
int32_t BSP_I2C_DeInit(void);
int32_t BSP_I2C_Write(uint16_t DevAddr, uint16_t Reg, const uint8_t* pData, uint16_t Len);
int32_t BSP_I2C_Read(uint16_t DevAddr, uint16_t Reg, const uint8_t* pData, uint16_t Len);
int32_t WriteRegWrap(void *Handle, uint8_t Reg,const  uint8_t *pData, uint16_t Length);
int32_t ReadRegWrap(void *Handle, uint8_t Reg, const uint8_t *pData, uint16_t Length);
int32_t LED12A1_DeviceEnable( LED1202_Object_TypeDef* pObj , TypedefEnumDevAddr DevSelect);
int32_t LED12A1_DeviceDisable( LED1202_Object_TypeDef* pObj , TypedefEnumDevAddr DevSelect);
int32_t LED12A1_ScanAvailDevice( LED1202_Object_TypeDef* pObj ,uint8_t *pBuff);
int32_t LED12A1_SetDeviceAddr( LED1202_Object_TypeDef* pObj , TypedefEnumDevAddr DevSelect);
int32_t LED12A1_AnalogDimming( LED1202_Object_TypeDef* pObj , uint8_t Current, uint8_t Channel, TypedefEnumDevAddr DevSelect);
int32_t LED12A1_DigitalDimming( LED1202_Object_TypeDef* pObj ,uint16_t *pBuff,uint8_t Channel, uint8_t PatternNum, TypedefEnumDevAddr DevSelect);
int32_t LED12A1_ChannelEnable( LED1202_Object_TypeDef* pObj , TypeDefChannel Channel ,TypedefEnumDevAddr DevSelect);
int32_t LED12A1_ChannelDisable( LED1202_Object_TypeDef* pObj , TypeDefChannel Channel, TypedefEnumDevAddr DevSelect);

/**
 * @}
 */   

/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* LED12A1_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
