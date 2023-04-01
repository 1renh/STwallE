/**
******************************************************************************
* @file    led1202.h
* @author  SRA NOIDA
* @version v1.0.0
* @date    30-05-2021
* @brief   Header file for led1202.c.
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
#ifndef __LED1202_H
#define __LED1202_H

#ifdef __cplusplus
  extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "led1202_reg.h"

/** @addtogroup BSP
  * @{
  */ 
 

/** @addtogroup LED1202
  * @{
  */
    
/* Exported Constants --------------------------------------------------------*/
#define MAX_CH_CURRENT    ((uint8_t)20)
#define MAX_VARIABLE      ((uint8_t)255)

/* Exported types ------------------------------------------------------------*/

/**
 * @brief  LED1202 Enable Disable enumerator definition.
 */
typedef enum
{
  LED1202_DISABLE = 0,
  LED1202_ENABLE
} LED1202_EN_STATUS;

typedef int32_t (*LED1202_Init_Func) (void);
typedef int32_t (*LED1202_DeInit_Func) (void);
typedef int32_t (*LED1202_Write_Func)(uint16_t, uint16_t, const  uint8_t*, uint16_t);
typedef int32_t (*LED1202_Read_Func) (uint16_t, uint16_t,const  uint8_t*, uint16_t);
typedef int32_t (*LED1202_IsReady_Func) (uint16_t, const uint32_t);

typedef void (*LED1202_Delay_Func) (uint32_t );

typedef struct {
  uint32_t             BusType; /*0 means I2C, 1 means SPI 4-Wires, 2 means SPI-3-Wires */
  uint8_t              Address;
  LED1202_Init_Func    Init;
  LED1202_DeInit_Func  DeInit;
  LED1202_Write_Func   Write;
  LED1202_Read_Func    Read;
  LED1202_Delay_Func   Delay;
} LED1202_IO_TypeDef;


typedef struct {
  LED1202_IO_TypeDef IO ;
  LED1202_Ctx_TypeDef Ctx ;
  uint32_t IsInitialized;
} LED1202_Object_TypeDef;


/**
 * @brief  LED1202 standard driver API structure definition.
 */
typedef enum 
{
  INTERNAL = 0x00,
  EXTERNAL
}ClockEnum_TypeDef;

typedef enum 
{
  CH_STATE_ENABLE = 0x00,
  CH_STATE_DISABLE = 0x01
}StateEnum_TypeDef;

/* Exported Functions --------------------------------------------------------*/
int32_t LED1202_RegisterBusIO (LED1202_Object_TypeDef* pObj, LED1202_IO_TypeDef *pIO);
int32_t LED1202_ReadID(LED1202_Object_TypeDef* pObj, uint8_t *pID, uint8_t DevAddr);
int32_t LED1202_ReadITStatus( LED1202_Object_TypeDef* pObj, uint8_t * pITStatus , uint8_t DevAddr);
int32_t LED1202_SetChannelState( LED1202_Object_TypeDef* pObj , uint16_t Channel ,StateEnum_TypeDef State, uint8_t DevAddr);
int32_t LED1202_WriteConfig( LED1202_Object_TypeDef* pObj , uint8_t Config, uint8_t DevAddr);
int32_t LED1202_ReadConfig( LED1202_Object_TypeDef* pObj , uint8_t *pBuff, uint8_t DevAddr);
int32_t LED1202_ReadFaultMaskStatus( LED1202_Object_TypeDef* pObj , uint8_t *pData , uint8_t DevAddr);
int32_t LED1202_WriteFaultMaskStatus( LED1202_Object_TypeDef* pObj , uint8_t *pData, uint8_t DevAddr);
int32_t LED1202_ReadFaultInterruptStatus( LED1202_Object_TypeDef* pObj , uint8_t *pData, uint8_t DevAddr);
int32_t LED1202_ReadOpenChannel( LED1202_Object_TypeDef* pObj , uint16_t Channel, uint8_t DevAddr);
int32_t LED1202_ReadLEDCurrentReg( LED1202_Object_TypeDef* pObj , uint8_t *pData , uint16_t Channel, uint8_t DevAddr);
int32_t LED1202_WriteLEDCurrentReg( LED1202_Object_TypeDef* pObj , uint8_t Current, uint16_t Channel, uint8_t DevAddr);
int32_t LED1202_WritePatternSequenceRepeatCounter( LED1202_Object_TypeDef* pObj , uint8_t *pData, uint8_t DevAddr);
int32_t LED1202_ReadPatternSequenceRepeatCounter( LED1202_Object_TypeDef* pObj , uint8_t *pData, uint8_t DevAddr);
int32_t LED1202_WritePatternDurationReg( LED1202_Object_TypeDef* pObj , uint8_t *pData , uint8_t PatternNum , uint8_t DevAddr);
int32_t LED1202_ReadPatternDurationReg( LED1202_Object_TypeDef* pObj , uint8_t *pData, uint8_t PatternNum , uint8_t DevAddr);
int32_t LED1202_WritePatternPWMConfig( LED1202_Object_TypeDef* pObj , uint8_t *pData ,uint8_t Channel, uint8_t PatternNum, uint8_t DevAddr);
int32_t LED1202_ReadPatternPWMConfig( LED1202_Object_TypeDef* pObj ,  uint8_t *pData ,uint8_t Channel, uint8_t PatternNum, uint8_t DevAddr);
int32_t LED1202_SetClockState( LED1202_Object_TypeDef* pObj , ClockEnum_TypeDef ClockType ,StateEnum_TypeDef State, uint8_t DevAddr);


/**
  * @}
  */

/**
  * @}
  */ 
  

#ifdef __cplusplus
  }
#endif
#endif /* __LED1202_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
