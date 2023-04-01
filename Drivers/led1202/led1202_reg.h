/**
******************************************************************************
* @file    led1202_reg.h
* @author  SRA NOIDA
* @date    30-Jun-21
* @brief   Header file for led1202_reg.c.
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

#ifndef _LED1202_REG_H_
#define _LED1202_REG_H_

/* Exported includes ---------------------------------------------------------*/
#include <stdint.h>


/* Exported Constants --------------------------------------------------------*/
#define I_AM_LED1202   ((uint8_t)0x12)

#define LED1202_DEVICE_ID          ((uint8_t)0x00)
#define LED1202_DEVICE_ENABLE      ((uint8_t)0x01)
#define LED1202_LED_CH_ENABLE      ((uint8_t)0x02)
#define LED1202_CONFIGURATION      ((uint8_t)0x04)
#define LED1202_FAULT_AND_STATUS_MASK ((uint8_t)0x05)
#define LED1202_FAULT_AND_STATUS_INTERRUPT ((uint8_t)0x06)
#define LED1202_OPEN_LED ((uint8_t)0x07)


/* CS0-11 LED Current Reg Address --------------------------------------------*/
#define LED1202_CS0_LED_CURRENT  ((uint8_t)0x09)
#define LED1202_CS1_LED_CURRENT  ((uint8_t)0x0A)
#define LED1202_CS2_LED_CURRENT  ((uint8_t)0x0B)
#define LED1202_CS3_LED_CURRENT  ((uint8_t)0x0C)
#define LED1202_CS4_LED_CURRENT  ((uint8_t)0x0D)
#define LED1202_CS5_LED_CURRENT  ((uint8_t)0x0E)
#define LED1202_CS6_LED_CURRENT  ((uint8_t)0x0F)
#define LED1202_CS7_LED_CURRENT  ((uint8_t)0x10)
#define LED1202_CS8_LED_CURRENT  ((uint8_t)0x11)
#define LED1202_CS9_LED_CURRENT  ((uint8_t)0x12)
#define LED1202_CS10_LED_CURRENT ((uint8_t)0x13)
#define LED1202_CS11_LED_CURRENT ((uint8_t)0x14)

/* Pattern 0-7 Duration Register Address -------------------------------------*/
#define LED1202_PATTERN_SEQUENCE_REPETITION ((uint8_t)0x15)
#define LED1202_PATTERN0_DURATION           ((uint8_t)0x16)
#define LED1202_PATTERN1_DURATION           ((uint8_t)0x17)
#define LED1202_PATTERN2_DURATION           ((uint8_t)0x18)
#define LED1202_PATTERN3_DURATION           ((uint8_t)0x19)
#define LED1202_PATTERN4_DURATION           ((uint8_t)0x1A)
#define LED1202_PATTERN5_DURATION           ((uint8_t)0x1B)
#define LED1202_PATTERN6_DURATION           ((uint8_t)0x1C)
#define LED1202_PATTERN7_DURATION           ((uint8_t)0x1D)

/* Pattern 0 PWM Register Address --------------------------------------------*/
#define LED1202_PATTERN0_CS0_PWM  ((uint8_t)0x1E)
#define LED1202_PATTERN0_CS1_PWM  ((uint8_t)0x20)
#define LED1202_PATTERN0_CS2_PWM  ((uint8_t)0x22)
#define LED1202_PATTERN0_CS3_PWM  ((uint8_t)0x24)
#define LED1202_PATTERN0_CS4_PWM  ((uint8_t)0x26)
#define LED1202_PATTERN0_CS5_PWM  ((uint8_t)0x28)
#define LED1202_PATTERN0_CS6_PWM  ((uint8_t)0x2A)
#define LED1202_PATTERN0_CS7_PWM  ((uint8_t)0x2C)
#define LED1202_PATTERN0_CS8_PWM  ((uint8_t)0x2E)
#define LED1202_PATTERN0_CS9_PWM  ((uint8_t)0x30)
#define LED1202_PATTERN0_CS10_PWM ((uint8_t)0x32)
#define LED1202_PATTERN0_CS11_PWM ((uint8_t)0x34)

/* Pattern 1 PWM Register Address --------------------------------------------*/
#define LED1202_PATTERN1_CS0_PWM  ((uint8_t)0x36)
#define LED1202_PATTERN1_CS1_PWM  ((uint8_t)0x38)
#define LED1202_PATTERN1_CS2_PWM  ((uint8_t)0x3A)
#define LED1202_PATTERN1_CS3_PWM  ((uint8_t)0x3C)
#define LED1202_PATTERN1_CS4_PWM  ((uint8_t)0x3E)
#define LED1202_PATTERN1_CS5_PWM  ((uint8_t)0x40)
#define LED1202_PATTERN1_CS6_PWM  ((uint8_t)0x42)
#define LED1202_PATTERN1_CS7_PWM  ((uint8_t)0x44)
#define LED1202_PATTERN1_CS8_PWM  ((uint8_t)0x46)
#define LED1202_PATTERN1_CS9_PWM  ((uint8_t)0x48)
#define LED1202_PATTERN1_CS10_PWM ((uint8_t)0x4A)
#define LED1202_PATTERN1_CS11_PWM ((uint8_t)0x4C)

/* Pattern 2 PWM Register Address --------------------------------------------*/
#define LED1202_PATTERN2_CS0_PWM  ((uint8_t)0x4E)
#define LED1202_PATTERN2_CS1_PWM  ((uint8_t)0x50)
#define LED1202_PATTERN2_CS2_PWM  ((uint8_t)0x52)
#define LED1202_PATTERN2_CS3_PWM  ((uint8_t)0x54)
#define LED1202_PATTERN2_CS4_PWM  ((uint8_t)0x56)
#define LED1202_PATTERN2_CS5_PWM  ((uint8_t)0x58)
#define LED1202_PATTERN2_CS6_PWM  ((uint8_t)0x5A)
#define LED1202_PATTERN2_CS7_PWM  ((uint8_t)0x5C)
#define LED1202_PATTERN2_CS8_PWM  ((uint8_t)0x5E)
#define LED1202_PATTERN2_CS9_PWM  ((uint8_t)0x60)
#define LED1202_PATTERN2_CS10_PWM ((uint8_t)0x62)
#define LED1202_PATTERN2_CS11_PWM ((uint8_t)0x64)

/* Pattern 3 PWM Register Address --------------------------------------------*/
#define LED1202_PATTERN3_CS0_PWM  ((uint8_t)0x66)
#define LED1202_PATTERN3_CS1_PWM  ((uint8_t)0x68)
#define LED1202_PATTERN3_CS2_PWM  ((uint8_t)0x6A)
#define LED1202_PATTERN3_CS3_PWM  ((uint8_t)0x6C)
#define LED1202_PATTERN3_CS4_PWM  ((uint8_t)0x6E)
#define LED1202_PATTERN3_CS5_PWM  ((uint8_t)0x70)
#define LED1202_PATTERN3_CS6_PWM  ((uint8_t)0x72)
#define LED1202_PATTERN3_CS7_PWM  ((uint8_t)0x74)
#define LED1202_PATTERN3_CS8_PWM  ((uint8_t)0x76)
#define LED1202_PATTERN3_CS9_PWM  ((uint8_t)0x78)
#define LED1202_PATTERN3_CS10_PWM ((uint8_t)0x7A)
#define LED1202_PATTERN3_CS11_PWM ((uint8_t)0x7C)

/* Pattern 4 PWM Register Address --------------------------------------------*/
#define LED1202_PATTERN4_CS0_PWM  ((uint8_t)0x7E)
#define LED1202_PATTERN4_CS1_PWM  ((uint8_t)0x80)
#define LED1202_PATTERN4_CS2_PWM  ((uint8_t)0x82)
#define LED1202_PATTERN4_CS3_PWM  ((uint8_t)0x84)
#define LED1202_PATTERN4_CS4_PWM  ((uint8_t)0x86)
#define LED1202_PATTERN4_CS5_PWM  ((uint8_t)0x88)
#define LED1202_PATTERN4_CS6_PWM  ((uint8_t)0x8A)
#define LED1202_PATTERN4_CS7_PWM  ((uint8_t)0x8C)
#define LED1202_PATTERN4_CS8_PWM  ((uint8_t)0x8E)
#define LED1202_PATTERN4_CS9_PWM  ((uint8_t)0x90)
#define LED1202_PATTERN4_CS10_PWM ((uint8_t)0x92)
#define LED1202_PATTERN4_CS11_PWM ((uint8_t)0x94)

/* Pattern 5 PWM Register Address --------------------------------------------*/
#define LED1202_PATTERN5_CS0_PWM  ((uint8_t)0x96)
#define LED1202_PATTERN5_CS1_PWM  ((uint8_t)0x98)
#define LED1202_PATTERN5_CS2_PWM  ((uint8_t)0x9A)
#define LED1202_PATTERN5_CS3_PWM  ((uint8_t)0x9C)
#define LED1202_PATTERN5_CS4_PWM  ((uint8_t)0x9E)
#define LED1202_PATTERN5_CS5_PWM  ((uint8_t)0xA0)
#define LED1202_PATTERN5_CS6_PWM  ((uint8_t)0xA2)
#define LED1202_PATTERN5_CS7_PWM  ((uint8_t)0xA4)
#define LED1202_PATTERN5_CS8_PWM  ((uint8_t)0xA6)
#define LED1202_PATTERN5_CS9_PWM  ((uint8_t)0xA8)
#define LED1202_PATTERN5_CS10_PWM ((uint8_t)0xAA)
#define LED1202_PATTERN5_CS11_PWM ((uint8_t)0xAC)

/* Pattern 6 PWM Register Address --------------------------------------------*/
#define LED1202_PATTERN6_CS0_PWM  ((uint8_t)0xAE)
#define LED1202_PATTERN6_CS1_PWM  ((uint8_t)0xB0)
#define LED1202_PATTERN6_CS2_PWM  ((uint8_t)0xB2)
#define LED1202_PATTERN6_CS3_PWM  ((uint8_t)0xB4)
#define LED1202_PATTERN6_CS4_PWM  ((uint8_t)0xB6)
#define LED1202_PATTERN6_CS5_PWM  ((uint8_t)0xB8)
#define LED1202_PATTERN6_CS6_PWM  ((uint8_t)0xBA)
#define LED1202_PATTERN6_CS7_PWM  ((uint8_t)0xBC)
#define LED1202_PATTERN6_CS8_PWM  ((uint8_t)0xBE)
#define LED1202_PATTERN6_CS9_PWM  ((uint8_t)0xC0)
#define LED1202_PATTERN6_CS10_PWM ((uint8_t)0xC2)
#define LED1202_PATTERN6_CS11_PWM ((uint8_t)0xC4)

/* Pattern 7 PWM Register Address --------------------------------------------*/
#define LED1202_PATTERN7_CS0_PWM  ((uint8_t)0xC6)
#define LED1202_PATTERN7_CS1_PWM  ((uint8_t)0xC8)
#define LED1202_PATTERN7_CS2_PWM  ((uint8_t)0xCA)
#define LED1202_PATTERN7_CS3_PWM  ((uint8_t)0xCC)
#define LED1202_PATTERN7_CS4_PWM  ((uint8_t)0xCE)
#define LED1202_PATTERN7_CS5_PWM  ((uint8_t)0xD0)
#define LED1202_PATTERN7_CS6_PWM  ((uint8_t)0xD2)
#define LED1202_PATTERN7_CS7_PWM  ((uint8_t)0xD4)
#define LED1202_PATTERN7_CS8_PWM  ((uint8_t)0xD6)
#define LED1202_PATTERN7_CS9_PWM  ((uint8_t)0xD8)
#define LED1202_PATTERN7_CS10_PWM ((uint8_t)0xDA)
#define LED1202_PATTERN7_CS11_PWM ((uint8_t)0xDC)

#define LED1202_CLK_SYNC         ((uint8_t)0xE0)
#define LED1202_GLOBAL_ADDRESS   ((uint8_t)0x5C)

/* Exported Types ------------------------------------------------------------*/
typedef enum
{
  LED1202_OK = 0,
  LED1202_BUSY,
  LED1202_RUNNING,
  LED1202_ERROR
}LED1202_STATUS_TypeDef;


typedef int32_t (*LED1202_WriteReg_Func)(void *, uint8_t, const uint8_t *,
                                         uint16_t);
typedef int32_t (*LED1202_ReadReg_Func) (void *, uint8_t,const  uint8_t *,
                                         uint16_t);

typedef struct {
  LED1202_WriteReg_Func WriteReg;
  LED1202_ReadReg_Func ReadReg;
  void *handle;
} LED1202_Ctx_TypeDef;

/* Exported Functions --------------------------------------------------------*/
int32_t LED1202_ReadReg (const LED1202_Ctx_TypeDef *pLed, uint16_t Reg, const uint8_t* Data, uint16_t len);
int32_t LED1202_WriteReg (const LED1202_Ctx_TypeDef *pLed, uint16_t Reg, const uint8_t  *Data, uint16_t len);



#endif
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
