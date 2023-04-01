/**
******************************************************************************
* @file    led1202.c 
* @author  SRA NOIDA
* @version v1.0.0
* @date    30-05-2021
* @brief   This file provides set of driver functions to manage communication 
*          between BSP and LED1202 chip.
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

/* Includes ------------------------------------------------------------------*/
#include "led1202.h"
#include "stdio.h"
#include "led12a1.h"    

/** @addtogroup BSP
  * @{
  */

/* External variables --------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Global variables ---------------------------------------------------------*/
int32_t TmpStatus;

/* Public functions ---------------------------------------------------------*/

/**
 * @brief  Register Component Bus IO operations
 * @param  pObj the device pObj
 * @param  pIO the IO pObj
 * @retval 0 in case of success, an error code otherwise
 */
int32_t LED1202_RegisterBusIO (LED1202_Object_TypeDef* pObj, LED1202_IO_TypeDef *pIO)
{
  int32_t ret = (int32_t)LED1202_OK;

  if (pObj == NULL)
  {
    ret = (int32_t)LED1202_ERROR;
  }
  else
  {
    pObj->IO.BusType     = pIO->BusType;
    pObj->IO.Address     = pIO->Address;
    pObj->IO.Init        = pIO->Init;
    pObj->IO.DeInit      = pIO->DeInit;
    pObj->IO.Write       = pIO->Write;
    pObj->IO.Read        = pIO->Read;
    pObj->IO.Delay     =   pIO->Delay;

    pObj->Ctx.ReadReg  = ReadRegWrap;
    pObj->Ctx.WriteReg = WriteRegWrap;
    pObj->Ctx.handle   = pObj;

    if (pObj->IO.Init == NULL)
    {
      ret = (int32_t)LED1202_ERROR;
    } else if (pObj->IO.Init() != 0) {
      ret = (int32_t)LED1202_ERROR;
    }
    else
    {
      /*DO nothing*/
    }
  }

  return ret;
}


/**
 * @brief  Reads the LED1202 ID
 * @param  pObj the device pObj
 * @param  pID pointer to the buffer
 * @param  DevAddr 7-Bit Device Address
 * @retval 0 in case of success, an error code otherwise
 */
int32_t LED1202_ReadID(LED1202_Object_TypeDef* pObj, uint8_t *pID, uint8_t DevAddr)
{
  int32_t ret;
  pObj->IO.Address = DevAddr<<1;
  TmpStatus = LED1202_ReadReg(&(pObj->Ctx), LED1202_DEVICE_ID, pID, 1);
  
  if((*pID) == I_AM_LED1202)
  {
    ret = (int32_t)LED1202_OK;
  }
  else
  {
    ret = (int32_t)LED1202_ERROR;
  }
  return (ret);
}


/**
  * @brief  Reads the IT status register from the LED1202.
  * @param  pObj the device pObj
  * @param  pITStatus Pointer on uint8_t, used to return the IT status, such as:
  *                       - RFUSERSTATE = 0x01
  *                       - RFBUSY = 0x02
  *                       - RFINTERRUPT = 0x04
  *                       - FIELDFALLING = 0x08
  *                       - FIELDRISING = 0x10
  *                       - RFPUTMSG = 0x20
  *                       - RFGETMSG = 0x40
  *                       - RFWRITE = 0x80
  * @param  DevAddr 7-Bit Device Address
  * @return int32_t enum status.
  */
int32_t LED1202_ReadITStatus( LED1202_Object_TypeDef* pObj, uint8_t * pITStatus , uint8_t DevAddr)
{

  int32_t ret;
  pObj->IO.Address = DevAddr<<1;
  ret = LED1202_ReadReg(&(pObj->Ctx), LED1202_FAULT_AND_STATUS_INTERRUPT, pITStatus, 1);
  return ret;
  
}


/**
 * @brief  Enable the channel of LED1202
 * @param  pObj the device pObj
 * @param  Channel LED_CHANNEL_0,LED_CHANNEL_1,LED_CHANNEL_2..LED_CHANNEL_11 can be passed
 * @param  DevAddr 7-Bit Device Address
 * @retval 0 in case of success, an error code otherwise
 */
int32_t LED1202_SetChannelState( LED1202_Object_TypeDef* pObj , uint16_t Channel ,StateEnum_TypeDef State, uint8_t DevAddr)
{
  volatile int32_t ret;
  uint16_t readReg;
  uint16_t chRegVal;
  pObj->IO.Address = DevAddr<<1;
  
  ret = LED1202_ReadReg(&(pObj->Ctx), LED1202_LED_CH_ENABLE, (uint8_t *)&readReg, 2);
    
  if(State == CH_STATE_ENABLE)
  {
    chRegVal = readReg | Channel;
    ret = LED1202_WriteReg(&(pObj->Ctx), LED1202_LED_CH_ENABLE, (uint8_t *)&chRegVal, 2);
  }
  else if(State == CH_STATE_DISABLE)
  {
    chRegVal = readReg & (~Channel);  
    ret = LED1202_WriteReg(&(pObj->Ctx), LED1202_LED_CH_ENABLE, (uint8_t *)&chRegVal, 2);
  }
  else
  {
    chRegVal = readReg & (~Channel);
    ret = LED1202_WriteReg(&(pObj->Ctx), LED1202_LED_CH_ENABLE, (uint8_t *)&chRegVal, 2);
  }
  return(ret);
}


/**
 * @brief  Write Configuration of LED1202
 * @param  pObj the device pObj
 * @param  Config value of config register
 * @param  DevAddr 7-Bit Device Address
 * @retval 0 in case of success, an error code otherwise
 */
int32_t LED1202_WriteConfig( LED1202_Object_TypeDef* pObj , uint8_t Config, uint8_t DevAddr)
{
  int32_t ret;
  pObj->IO.Address = DevAddr<<1;
  ret = LED1202_WriteReg(&(pObj->Ctx), LED1202_CONFIGURATION, &Config, 1);
  
  return(ret);
}

/**
 * @brief  Read Configuration register of LED1202
 * @param  pObj the device pObj
 * @param  pBuff Buffer to store the value 
 * @param  DevAddr 7-Bit Device Address
 * @retval 0 in case of success, an error code otherwise
 */
int32_t LED1202_ReadConfig( LED1202_Object_TypeDef* pObj , uint8_t *pBuff, uint8_t DevAddr)
{
  int32_t ret;
  pObj->IO.Address = DevAddr<<1;
  
  ret = LED1202_ReadReg(&(pObj->Ctx), LED1202_CONFIGURATION, pBuff, 1);
  
  return(ret);
}

/**
 * @brief  Read Fault mask register of LED1202
 * @param  pObj the device pObj
 * @param  pBuff Buffer to store the value 
 * @param  DevAddr 7-Bit Device Address
 * @retval 0 in case of success, an error code otherwise
 */
int32_t LED1202_ReadFaultMaskStatus( LED1202_Object_TypeDef* pObj , uint8_t *pData , uint8_t DevAddr)
{
  int32_t ret;
  pObj->IO.Address  = DevAddr<<1;
  
  ret = LED1202_ReadReg(&(pObj->Ctx), LED1202_FAULT_AND_STATUS_MASK, pData, 1); 
  
  return(ret);
}

/**
 * @brief  Write Fault mask register of LED1202
 * @param  pObj the device pObj
 * @param  pBuff pointer to the Buffer to be written 
 * @param  DevAddr 7-Bit Device Address
 * @retval 0 in case of success, an error code otherwise
 */
int32_t LED1202_WriteFaultMaskStatus( LED1202_Object_TypeDef* pObj , uint8_t *pData, uint8_t DevAddr)
{
  int32_t ret;
  pObj->IO.Address = DevAddr<<1;
  ret = LED1202_WriteReg(&(pObj->Ctx), LED1202_FAULT_AND_STATUS_MASK, pData, 1); 
  
  return(ret);
}

/**
 * @brief  Read Fault Interrupt status register of LED1202
 * @param  pObj the device pObj
 * @param  pBuff pointer to the Buffer to store the buffer
 * @param  DevAddr 7-Bit Device Address
 * @retval 0 in case of success, an error code otherwise
 */
int32_t LED1202_ReadFaultInterruptStatus( LED1202_Object_TypeDef* pObj , uint8_t *pData, uint8_t DevAddr)
{
  int32_t ret;
  pObj->IO.Address = DevAddr<<1;
  ret = LED1202_ReadReg(&(pObj->Ctx), LED1202_FAULT_AND_STATUS_INTERRUPT, pData, 1); 
  
  return(ret);
}

/**
 * @brief  Read Open channel status of LED1202
 * @param  pObj the device pObj
 * @param  pBuff pointer to the Buffer to store the buffer
 * @param  DevAddr 7-Bit Device Address
 * @retval 0 in case of success, an error code otherwise
 */
int32_t LED1202_ReadOpenChannel( LED1202_Object_TypeDef* pObj , uint16_t Channel, uint8_t DevAddr)
{
  uint16_t data;
  static uint8_t chStatus = 0;
  pObj->IO.Address = DevAddr<<1;
  TmpStatus = LED1202_ReadReg(&(pObj->Ctx), LED1202_OPEN_LED,(uint8_t *) &data, 2);
  
  
  if((data & Channel) == ((uint8_t)0x00))
  {
    chStatus = (uint8_t)1; /*Channel is Closed */
  }
  else
  {
    chStatus = (uint8_t)0; /* Channel is Open */
  }
  
  return((int32_t)chStatus);
}

/**
 * @brief  Read LED Current of a channel
 * @param  pObj the device pObj
 * @param  pBuff pointer to the Buffer to store the buffer
 * @param  Channel Channel number (0 to 11 )         
 * @param  DevAddr 7-Bit Device Address
 * @retval 0 in case of success, an error code otherwise
 */
int32_t LED1202_ReadLEDCurrentReg( LED1202_Object_TypeDef* pObj , uint8_t *pData , uint16_t Channel, uint8_t DevAddr)
{
  int32_t ret;
  pObj->IO.Address = DevAddr<<1;
  ret = LED1202_ReadReg(&(pObj->Ctx), (LED1202_CS0_LED_CURRENT + Channel), pData, 1); 
  
  return(ret);
}


/**
 * @brief  Write LED Current of a channel
 * @param  pObj the device pObj
 * @param  pBuff pointer to the buffer to be written
 * @param  Channel Channel number (0 to 11)
 * @param  DevAddr 7-Bit Device Address
 * @retval 0 in case of success, an error code otherwise
 */
int32_t LED1202_WriteLEDCurrentReg( LED1202_Object_TypeDef* pObj , uint8_t Current, uint16_t Channel, uint8_t DevAddr)
{
  int32_t ret;
  uint8_t currentRegValue;
  
  pObj->IO.Address = DevAddr<<1;
  
  if(Current < MAX_CH_CURRENT)
  {
    currentRegValue = (uint8_t ) (((uint16_t)Current *(uint16_t) MAX_VARIABLE)/(uint16_t)MAX_CH_CURRENT);
  }
  else
  {
    currentRegValue = MAX_VARIABLE;
  }
  
  ret = LED1202_WriteReg(&(pObj->Ctx), (LED1202_CS0_LED_CURRENT + Channel), &currentRegValue, 1); 
  
  return(ret);
}


/**
 * @brief  Write pattern Sequence of a channel
 * @param  pObj the device pObj
 * @param  pBuff pointer to the buffer to be written
 * @param  DevAddr 7-Bit Device Address
 * @retval 0 in case of success, an error code otherwise
 */
int32_t LED1202_WritePatternSequenceRepeatCounter( LED1202_Object_TypeDef* pObj , uint8_t *pData, uint8_t DevAddr)
{
  int32_t ret;
  pObj->IO.Address = DevAddr<<1;
  ret = LED1202_WriteReg(&(pObj->Ctx), LED1202_PATTERN_SEQUENCE_REPETITION, pData, 1); 
  
  return (ret);
}

/**
 * @brief  Read pattern Sequence of a channel
 * @param  pObj the device pObj
 * @param  pBuff pointer to the buffer to store the value
 * @param  DevAddr 7-Bit Device Address
 * @retval 0 in case of success, an error code otherwise
 */
int32_t LED1202_ReadPatternSequenceRepeatCounter( LED1202_Object_TypeDef* pObj , uint8_t *pData, uint8_t DevAddr)
{
  int32_t ret;
  pObj->IO.Address = DevAddr<<1;
  ret = LED1202_ReadReg(&(pObj->Ctx), LED1202_PATTERN_SEQUENCE_REPETITION, pData, 1); 
  
  return(ret);
}

/**
 * @brief  Write pattern Duration of a channel
 * @param  pObj the device pObj
 * @param  pData pointer to the buffer to be written
 * @param  PatternNum pattern Number
 * @param  DevAddr 7-Bit Device Address
 * @retval 0 in case of success, an error code otherwise
 */
int32_t LED1202_WritePatternDurationReg( LED1202_Object_TypeDef* pObj , uint8_t *pData , uint8_t PatternNum , uint8_t DevAddr)
{
  int32_t ret;
  pObj->IO.Address = DevAddr<<1;
  ret  = LED1202_WriteReg(&(pObj->Ctx), (uint8_t)(LED1202_PATTERN0_DURATION + PatternNum), pData, 1); 
  
  return (ret);
}

/**
 * @brief  Read pattern Duration of a channel
 * @param  pObj the device pObj
 * @param  pData pointer to the buffer to store
 * @param  PatternNum pattern Number
 * @param  DevAddr 7-Bit Device Address
 * @retval 0 in case of success, an error code otherwise
 */
int32_t LED1202_ReadPatternDurationReg( LED1202_Object_TypeDef* pObj , uint8_t *pData, uint8_t PatternNum , uint8_t DevAddr)
{
  int32_t ret;
  pObj->IO.Address = DevAddr<<1;
  ret  = LED1202_ReadReg(&(pObj->Ctx), (uint8_t)(LED1202_PATTERN0_DURATION + PatternNum), pData, 1); 
  
  return(ret);
}


/**
 * @brief  Write pattern PWM Duration of a channel
 * @param  pObj the device pObj
 * @param  pData pointer to the buffer to write
 * @param  Channel Channel Number (0 to 11)
 * @param  PatternNum Pattern Number
 * @param  DevAddr 7-Bit Device Address
 * @retval 0 in case of success, an error code otherwise
 */
int32_t LED1202_WritePatternPWMConfig( LED1202_Object_TypeDef* pObj , uint8_t *pData ,uint8_t Channel, uint8_t PatternNum, uint8_t DevAddr)
{
  uint16_t digData;
  uint8_t chOffset;
  int32_t ret = 0;
  pObj->IO.Address = DevAddr<<1;
  digData = (*((uint16_t *)pData));
  
  chOffset = (((uint8_t)2)*Channel) + (((uint8_t)24)*PatternNum);
  
  if(digData<=((uint16_t)4095))
  {
   ret =  LED1202_WriteReg(&(pObj->Ctx),(uint8_t)( LED1202_PATTERN0_CS0_PWM + chOffset), pData, 2); 
  }
  return (ret);
}

/**
 * @brief  Read pattern PWM Duration of a channel
 * @param  pObj the device pObj
 * @param  pData pointer to the buffer to store
 * @param  Channel Channel Number (0 to 11)
 * @param  PatternNum Pattern Number
 * @param  DevAddr 7-Bit Device Address
 * @retval 0 in case of success, an error code otherwise
 */
int32_t LED1202_ReadPatternPWMConfig( LED1202_Object_TypeDef* pObj ,  uint8_t *pData ,uint8_t Channel, uint8_t PatternNum, uint8_t DevAddr)
{
  int32_t ret;
  uint8_t chOffset;
  pObj->IO.Address = DevAddr<<1;
  chOffset = (((uint8_t)2)*Channel) + (((uint8_t)24)*PatternNum);
  ret = LED1202_ReadReg(&(pObj->Ctx), (uint8_t)(LED1202_PATTERN0_CS0_PWM + chOffset), pData, 2); 
  return (ret);
}

/**
 * @brief  Set Clock State
 * @param  pObj the device pObj
 * @param  ClockType internal clokc or external clock
 * @param  State State enable or Disable
 * @param  DevAddr 7-Bit Device Address
 * @retval 0 in case of success, an error code otherwise
 */
int32_t LED1202_SetClockState( LED1202_Object_TypeDef* pObj , ClockEnum_TypeDef ClockType ,StateEnum_TypeDef State, uint8_t DevAddr)
{
  int32_t ret;
  uint8_t tmp;
  pObj->IO.Address = DevAddr<<1;
  if(ClockType == INTERNAL)
  {
    if(State == CH_STATE_ENABLE)
    {
      tmp = 0x01;
    }
    else
    {
      tmp=0x00;
    }
    ret = LED1202_WriteReg(&(pObj->Ctx),LED1202_CLK_SYNC , &tmp, 1);
  }
  else if (ClockType == EXTERNAL)
  {
    if(State == CH_STATE_ENABLE)
    {
      tmp = 0x02;
    }
    else
    {
      tmp=0x00;
    }
    ret = LED1202_WriteReg(&(pObj->Ctx),LED1202_CLK_SYNC , &tmp, 1);
  }
  else
  {
    if(State == CH_STATE_ENABLE)
    {
      tmp = 0x01;
    }
    else
    {
      tmp=0x00;
    }
    ret = LED1202_WriteReg(&(pObj->Ctx),LED1202_CLK_SYNC , &tmp, 1);
  }
  
  return(ret);
}


/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
