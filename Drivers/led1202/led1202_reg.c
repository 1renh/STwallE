/**
******************************************************************************
* @file    led1202_reg.c
* @author  SRA NOIDA
* @date    30-05-2021
* @brief   LED1202 Register Driver files
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

/* Includes   ----------------------------------------------------------------*/
#include "led1202_reg.h"
#include "led1202.h"


/**
* @brief  Read generic device register
*
* @param  ctx   read / write interface definitions(ptr)
* @param  reg   register to read
* @param  data  pointer to buffer that store the data read(ptr)
* @param  len   number of consecutive register to read
* @retval          interface status (MANDATORY: return 0 -> no Error)
*
*/
int32_t LED1202_ReadReg (const LED1202_Ctx_TypeDef *pLed, uint16_t Reg, const uint8_t *Data, uint16_t len)
{
  int32_t tmp;
  tmp =(int32_t)( pLed->ReadReg(pLed->handle, Reg,  Data, len));
  return (tmp);
}


/**
* @brief  Write generic device register
*
* @param  ctx   read / write interface definitions(ptr)
* @param  reg   register to read
* @param  data  pointer to buffer that store the data read(ptr)
* @param  len   number of consecutive register to read
* @retval          interface status (MANDATORY: return 0 -> no Error)
*
*/
int32_t LED1202_WriteReg (const LED1202_Ctx_TypeDef *pLed, uint16_t Reg, const uint8_t* Data, uint16_t len)
{
  int32_t tmp;
  tmp = (int32_t)(pLed->WriteReg(pLed->handle, Reg, Data, len));
  return (tmp);
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
