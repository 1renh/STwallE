/**
******************************************************************************
* @file    led12a1.c
* @author  SRA NOIDA
* @version v1.0.0
* @date    30-05-2021
* @brief   This file provides the X-NUCLEO-LED12A1 Driver
*          board.
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
#include "led12a1.h"
#include "led12a1_conf.h"
#include "bsp_ip_conf.h"


/** @addtogroup BSP BSP
* @{
*/

/** @addtogroup LED12A1 LED12A1
* @{
*/ 


/** @defgroup LED12A1_Private_Macros LED12A1 Private Macros
* @{
*/
/*### RECORD ###*/


/**
* @}
*/ 

/** @defgroup LED12A1_Exported_Variables LED12A1  Exported Variables
* @{
*/

/**
* @}
*/

/** @defgroup LED12A1_Private_Variables LED12A1_ Private Variables
* @{
*/
LED1202_Object_TypeDef LED1202Obj;

/**
* @}
*/ 

/** @defgroup LED12A1_Private_Function_Prototypes LED12A1  Private Function Prototypes
* @{
*/


/**
* @}
*/ 

/** @defgroup LED12A1_Exported_Functions LED12A1  Exported Functions
* @{
*/ 



/**
* @brief  LED12A1 Board Initialization 
* @retval 0 in case of success, an error code otherwise
*/
int32_t LED12A1_Init( void )
{
  volatile int32_t ret =  (int32_t)LED1202_OK;
  LED1202_IO_TypeDef ledIO;
  
  /*register SPI bus function to the component */
  ledIO.BusType = LED1202_I2C_BUS;
  ledIO.Address = LED1202_I2C_ADDR;
  ledIO.Init = LED12A1_I2C_Init;
  ledIO.DeInit = LED12A1_I2C_DeInit;
  ledIO.Write = LED12A1_I2C_Write;
  ledIO.Read = LED12A1_I2C_Read;
  ledIO.Delay = LED12A1_Delay;
  
  ret = LED1202_RegisterBusIO (&LED1202Obj, &ledIO);
  
  return (ret);
}

/**
* @brief  LED12A1 I2C Initialization 
* @retval 0 in case of success, an error code otherwise
*/
int32_t  BSP_I2C_Init(void)
{
  MX_I2C1_Init();
  return (0);
}

/**
* @brief  LED12A1 I2C DeInitialization 
* @retval 0 in case of success, an error code otherwise
*/
int32_t BSP_I2C_DeInit(void)
{
  HAL_StatusTypeDef ret;
  ret  = HAL_I2C_DeInit(&hi2c1);
  return((int32_t)ret);
}

/**
* @brief  Write registers through bus (8 bits)
* @param  Addr: Device address on Bus.
* @param  Reg: The target register address to write
* @param  Value: The target register value to be written
* @retval BSP status
*/
int32_t BSP_I2C_Write(uint16_t DevAddr, uint16_t Reg, const uint8_t* pData, uint16_t Len)
{
  int32_t ret = (int32_t)BSP_ERROR_BUS_FAILURE;
  
  if (HAL_I2C_Mem_Write(&hi2c1, (uint8_t)DevAddr,
                        (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT,
                        (uint8_t *)pData, Len, TIMEOUT_DURATION) == HAL_OK)
  {
    ret = BSP_ERROR_NONE;
  }
  
  return ret;
}

/**
* @brief  Read registers through a bus (8 bits)
* @param  DevAddr: Device address on BUS
* @param  Reg: The target register address to read
* @retval BSP status
*/
int32_t BSP_I2C_Read(uint16_t DevAddr, uint16_t Reg, const uint8_t* pData, uint16_t Len)
{
  int32_t ret = BSP_ERROR_BUS_FAILURE;
  
  if (HAL_I2C_Mem_Read(&hi2c1, DevAddr, (uint16_t)Reg,
                       I2C_MEMADD_SIZE_8BIT, (uint8_t *)pData,
                       Len, TIMEOUT_DURATION) == HAL_OK)
  {
    ret = BSP_ERROR_NONE;
  }
  
  return ret;
}

/**
* @brief  Wrap Read register component function to Bus IO function
* @param  Handle the device handler
* @param  Reg the register address
* @param  pData the stored data pointer
* @param  Length the length
* @retval 0 in case of success, an error code otherwise
*/
int32_t ReadRegWrap(void *Handle, uint8_t Reg, const uint8_t *pData, uint16_t Length)
{
  LED1202_Object_TypeDef *led1202Obj = (LED1202_Object_TypeDef *)Handle;
  
  return led1202Obj->IO.Read(led1202Obj->IO.Address, Reg, pData, Length);
}


/**
* @brief  Wrap Write register component function to Bus IO function
* @param  Handle the device handler
* @param  Reg the register address
* @param  pData the stored data pointer
* @param  Length the length
* @retval 0 in case of success, an error code otherwise
*/
int32_t WriteRegWrap(void *Handle, uint8_t Reg, const uint8_t *pData, uint16_t Length)
{
  LED1202_Object_TypeDef *led1202Obj  = (LED1202_Object_TypeDef *)Handle;
  
  return led1202Obj->IO.Write(led1202Obj->IO.Address, Reg, pData, Length);
}

/**
* @brief  FunctionDescription
* @param xGpio can be 4 different GPIO used in Radio of S2LP
* @param  xGpioMode can be different Mode 
* @param  xGpioEdge The edge required for interrupt
* @retval None
*/
void LED12A1_GPIO_Init(void)  
{
  GPIO_InitTypeDef EXTI_InitStructure;
  
  LED12A1_GPIO_CLK_ENABLE();
  
  /* Configures MCU GPIO EXTI line */
  EXTI_InitStructure.Pull = GPIO_NOPULL;
  EXTI_InitStructure.Mode = GPIO_MODE_IT_FALLING;
  EXTI_InitStructure.Pin = LED12A1_GPIO_PIN;
  EXTI_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
  
  HAL_GPIO_Init(LED12A1_GPIO_PORT, &EXTI_InitStructure);   
}

/**
* @brief  Enable LED1202 Device
* @param  pObj pointer to Object
* @param  DevSelect Device selected (LED_DEVICE1, LED_DEVICE2 ,LED_DEVICE3 or LED_DEVICE_ALL)
* @retval 0 in case of success, an error code otherwise
*/
int32_t LED12A1_DeviceEnable( LED1202_Object_TypeDef* pObj , TypedefEnumDevAddr DevSelect)
{
  volatile int32_t ret = (int32_t) LED1202_OK;
  uint8_t tmp = 0x01;
  uint8_t devAddr;
  
  switch(DevSelect)
  {
  case LED_DEVICE1:
    devAddr = LED1202_DEV1_7BIT_ADDR;
    
    break;
    
  case LED_DEVICE2:
    devAddr = LED1202_DEV2_7BIT_ADDR;
    break;
    
  case LED_DEVICE3:
    devAddr = LED1202_DEV3_7BIT_ADDR;
    break;
    
  case LED_DEVICE4:
    devAddr = LED1202_DEV4_7BIT_ADDR;
    break;  
    
  case LED_DEVICE_ALL:
    devAddr = LED1202_GLOBAL_7BIT_ADDR; /*GLOBAL ADDRESS*/
    break;
    
  default:
    devAddr = LED1202_GLOBAL_7BIT_ADDR;
    break;
    
  }
  
  pObj->IO.Address = (uint8_t)(devAddr<<1);
  
  ret = LED1202_WriteReg(&(pObj->Ctx), LED1202_DEVICE_ENABLE, &tmp, 1);
  return(ret);
}


/**
* @brief  Set 7 bit Device address
* @param  pObj pointer to Object
* @param  DevSelect Device selected (LED_DEVICE1, LED_DEVICE2 ,LED_DEVICE3 or LED_DEVICE_ALL)
* @retval 0 in case of success, an error code otherwise
*/
int32_t LED12A1_SetDeviceAddr( LED1202_Object_TypeDef* pObj , TypedefEnumDevAddr DevSelect)
{
  volatile int32_t ret = (int32_t) LED1202_OK;
  uint8_t devAddr;
  
  switch(DevSelect)
  {
  case LED_DEVICE1:
    devAddr = LED1202_DEV1_7BIT_ADDR;
    
    break;
    
  case LED_DEVICE2:
    devAddr = LED1202_DEV2_7BIT_ADDR;
    break;
    
  case LED_DEVICE3:
    devAddr = LED1202_DEV3_7BIT_ADDR;
    break;
    
  case LED_DEVICE4:
    devAddr = LED1202_DEV4_7BIT_ADDR;
    break;
    
  case LED_DEVICE_ALL:
    devAddr = LED1202_GLOBAL_7BIT_ADDR; /*GLOBAL ADDRESS*/
    break;
    
  default:
    devAddr = LED1202_GLOBAL_7BIT_ADDR;
    break;
    
  }
  
  pObj->IO.Address = devAddr;
  
  return(ret);
}


/**
* @brief  Disable  selected LED1202 Device
* @param  pObj pointer to Object
* @param  DevSelect Device selected (LED_DEVICE1, LED_DEVICE2 ,LED_DEVICE3 or LED_DEVICE_ALL)
* @retval 0 in case of success, an error code otherwise
*/
int32_t LED12A1_DeviceDisable( LED1202_Object_TypeDef* pObj , TypedefEnumDevAddr DevSelect)
{
  volatile int32_t ret =  (int32_t)LED1202_OK;
  uint8_t tmp = 0x00;
  uint8_t devAddr;
  
  switch(DevSelect)
  {
  case LED_DEVICE1:
    devAddr = LED1202_DEV1_7BIT_ADDR;
    break;
    
  case LED_DEVICE2:
    devAddr = LED1202_DEV2_7BIT_ADDR;
    break;
    
  case LED_DEVICE3:
    devAddr = LED1202_DEV3_7BIT_ADDR;
    break;
    
  case LED_DEVICE4:
    devAddr = LED1202_DEV4_7BIT_ADDR;
    break;
    
  case LED_DEVICE_ALL:
    devAddr = LED1202_GLOBAL_7BIT_ADDR; /*GLOBAL ADDRESS*/
    break;
    
  default:
    devAddr = LED1202_GLOBAL_7BIT_ADDR;
    break;
    
  }
  
  pObj->IO.Address = (uint8_t)(devAddr<<1);
  
  ret = LED1202_WriteReg(&(pObj->Ctx), LED1202_DEVICE_ENABLE, &tmp, 1);
  return(ret);
}

/**
* @brief  Scan Available LED1202 Devices
* @param  pObj pointer to Object
* @param  pBuff Pointer to buffer to store the Available devices 7 bit addresses
* @retval Number of LED1202 devices available on board
*/
int32_t LED12A1_ScanAvailDevice( LED1202_Object_TypeDef* pObj ,uint8_t *pBuff)
{
  uint8_t i2cStartAddr = 0x58;
  uint8_t i2cEndAddr = 0x60;
  uint8_t addr;
  uint8_t *buffPtr = pBuff;
  uint8_t devId;
  int32_t status;
  int32_t numDev = 0;
  
  for (addr = i2cStartAddr; addr<=i2cEndAddr; addr++)
  {
    devId = 0;
    status =  LED1202_ReadID(pObj, &devId, addr);
    
    if(status == ((int32_t)LED1202_OK))
    {
      numDev++;
      *buffPtr = addr;
      buffPtr++;
    }
  }
  
  return(numDev);
}

/**
* @brief  Perform Analog Dimming
* @param  pObj pointer to Object
* @param  Current The value of current to be written( 1ma to 20ma)
* @param  Channel The channel to be written (0 to 11)
* @param  DevSelect Device selected (LED_DEVICE1, LED_DEVICE2 ,LED_DEVICE3 or LED_DEVICE_ALL)
* @retval Number of LED1202 devices available on board
*/
int32_t LED12A1_AnalogDimming( LED1202_Object_TypeDef* pObj , uint8_t Current, uint8_t Channel, TypedefEnumDevAddr DevSelect)
{
  volatile int32_t ret = (int32_t) LED1202_OK;
  ret = LED12A1_SetDeviceAddr(pObj ,DevSelect);
  ret = LED1202_WriteLEDCurrentReg(pObj ,Current, Channel, pObj->IO.Address); 
  return(ret);
}

/**
* @brief  Perform Digital Dimming
* @param  pObj pointer to Object
* @param  pBuff Pointer to buffer to be written
* @param  Channel The channel to be written (0 to 11)
* @param  PatternNum Pattern Number
* @param  DevSelect Selected Device(  LED_DEVICE1 ,LED_DEVICE2,LED_DEVICE3 or LED_DEVICE_ALL)
* @retval ret the status of the operartion
*/
int32_t LED12A1_DigitalDimming( LED1202_Object_TypeDef* pObj ,uint16_t *pBuff,uint8_t Channel, uint8_t PatternNum, TypedefEnumDevAddr DevSelect)
{
  volatile int32_t ret = (int32_t) LED1202_OK;
  ret = LED12A1_SetDeviceAddr(pObj ,DevSelect);
  ret = LED1202_WritePatternPWMConfig(pObj ,(uint8_t *)pBuff,Channel, PatternNum, pObj->IO.Address);
  return(ret);
}

/**
* @brief  Enable the channel of LED Device
* @param  pObj the device pObj
* @param  Channel any combination of LED_CHANNEL_0,LED_CHANNEL_1,LED_CHANNEL_2..LED_CHANNEL_11 can be passed
* @param  DevSelect Selected Device(  LED_DEVICE1 ,LED_DEVICE2,LED_DEVICE3 or LED_DEVICE_ALL)
* @retval 0 in case of success, an error code otherwise
*/
int32_t LED12A1_ChannelEnable( LED1202_Object_TypeDef* pObj , TypeDefChannel Channel, TypedefEnumDevAddr DevSelect)
{
  volatile int32_t ret = (int32_t) LED1202_OK;
  ret = LED12A1_SetDeviceAddr(pObj ,DevSelect);
  ret = LED1202_SetChannelState(pObj ,(uint16_t) Channel ,CH_STATE_ENABLE, pObj->IO.Address);
  
  return(ret);
}

/**
* @brief  Disble the channel of LED Device
* @param  pObj the device pObj
* @param  Channel any combination of LED_CHANNEL_0,LED_CHANNEL_1,LED_CHANNEL_2..LED_CHANNEL_11 can be passed
* @param  DevSelect Selected Device(  LED_DEVICE1 ,LED_DEVICE2,LED_DEVICE3 or LED_DEVICE_ALL)
* @retval 0 in case of success, an error code otherwise
*/
int32_t LED12A1_ChannelDisable( LED1202_Object_TypeDef* pObj , TypeDefChannel Channel,TypedefEnumDevAddr DevSelect)
{
  volatile int32_t ret =  (int32_t)LED1202_OK;
  ret = LED12A1_SetDeviceAddr(pObj ,DevSelect);
  ret = LED1202_SetChannelState(pObj , (uint16_t) Channel ,CH_STATE_DISABLE, pObj->IO.Address);
  
  return(ret);
}

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
