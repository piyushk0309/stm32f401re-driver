/*
 * stm32f401xx_gpio_driver.h
 *
 *  Created on: 03-Apr-2026
 *      Author: TGT
 */

#ifndef INC_STM32F401XX_GPIO_DRIVER_H_
#define INC_STM32F401XX_GPIO_DRIVER_H_

#include "stm32f401xx.h"



#endif /* INC_STM32F401XX_GPIO_DRIVER_H_ */

/* this is configuration structure for a gpio pin*/

typedef struct
{
	uint8_t GPIO_PinNumber;
	uint8_t GPIO_PinMode;   // POSSIBLE VALUES FROM @GPIO_PINMODES
	uint8_t GPIO_PinSpeed;	//POSSIBLE VALUES FROM @GPIO_PINSPEEEDS
	uint8_t GPIO_PinPuPdControl;
	uint8_t GPIO_PinOPType;      // POSSIBLE VALUES FROM  //@GPIO_PINOUTPUTTYPES
	uint8_t GPIO_PinAltFunMode;
} GPIO_PinConfig_t;


/* THIS IS THE HANDLE STRUCTURE OF GPIO PIN */

typedef struct {
	GPIO_Reg_Def_t *pGPIOx;      /*this holds the base address of the gpio port to which the pin belongs */
	GPIO_PinConfig_t GPIO_PinConfig;  /* this  holds gpio pin configuration settings */
} GPIO_Handle_t;

//GPIO PIN POSSIBLE MODES
//@GPIO_PINMODES

#define GPIO_MODE_INPUT  0
#define GPIO_MODE_OUTPUT 1
#define GPIO_MODE_ALTFN  2
#define GPIO_MODE_ANALOG 3
#define GPIO_MODE_IT_FT  4
#define GPIO_MODE_IT_RT  5
#define GPIO_MODE IT_RFT 6

//GPIO PIN DEFINITIONS
// @GPIO_PIN_NUMBERS
#define GPIO_PIN_NO_0		0
#define GPIO_PIN_NO_1		1
#define GPIO_PIN_NO_2		2
#define GPIO_PIN_NO_3		3
#define GPIO_PIN_NO_4		4
#define GPIO_PIN_NO_5		5
#define GPIO_PIN_NO_6		6
#define GPIO_PIN_NO_7		7
#define GPIO_PIN_NO_8		8
#define GPIO_PIN_NO_9		9
#define GPIO_PIN_NO_10		10
#define GPIO_PIN_NO_11		11
#define GPIO_PIN_NO_12		12
#define GPIO_PIN_NO_13		13
#define GPIO_PIN_NO_14		14
#define GPIO_PIN_NO_15		15
















// DEFINE POSSIBLE PIN OUTPOUT TYPES
//@GPIO_PINOUTPUTTYPES

#define GPIO_OP_TYPE_PP 0
#define GPIO_OP_TYPE_OD 1


// DEFINE  GPIO POSSIBLE OUTPUT SPEEDS
//@GPIO_PINSPEEDS
#define GPIO_SPEED_LOW 	  0
#define GPIO_SPEED_MEDIUM 1
#define GPIO_SPEED_FAST   2
#define GPIO_SPEED_HIGH   3

//GPIO PIN PULL UP AND PULL DOWN CONFIG MACROS

#define GPIO_NO_PUPD      0
#define GPIO_PIN_PU       1
#define GPIO_PIN_PD       2






										/* API SUPPORTED BY THIS DRIVER */



/* PERIPHERAL CLOCK SETUP*/

void GPIO_PeriClockControl(GPIO_Reg_Def_t *pGPIOx,uint8_t EnorDi);

/*INIT AND DE-INIT*/

void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_Reg_Def_t *pGPIOx);

/*data read and write */
uint8_t GPIO_ReadFromInputPin(GPIO_Reg_Def_t *pGPIOx,uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_Reg_Def_t *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_Reg_Def_t *pGPIOx,uint8_t PinNumber,uint8_t Value);
void GPIO_WriteToOuputPort(GPIO_Reg_Def_t *pGPIOx,uint16_t Value);
void GPIO_ToggleOutputPin(GPIO_Reg_Def_t *pGPIOx,uint8_t PinNumber);


/* IRQ CONFIGURATION AND ISR HANDLING */
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber,uint32_t Priority);
void GPIO_IRQHandling(uint8_t PinNumber);










