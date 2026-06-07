/*
 * stm32f401xx.h
 *
 *  Created on: Mar 30, 2026
 *      Author: TGT
 */

#ifndef INC_STM32F401XX_H_
#define INC_STM32F401XX_H_


#include "stdint.h"
#include "stddef.h"



#define __weak __attribute__ ((weak))


/**************PROCESSOR SPECIFIC DETAILS***************/

// ARM CROTEX M4 NVIC ISERX REGISTER ADDRESSES

#define NVIC_ISER0			((volatile uint32_t*) 0xE000E100)
#define NVIC_ISER1   		((volatile uint32_t*) 0xE000E104)
#define NVIC_ISER2  		((volatile uint32_t*) 0xE000E108)
#define NVIC_ISER3  		((volatile uint32_t*) 0xE000E10c)

// ARM CORTEX M4 PRIOCESSOR NVIC ICERX REGISTER ADDRESSES

#define NVIC_ICER0			((volatile uint32_t*)0xE000E180)
#define NVIC_ICER1			((volatile uint32_t*)0xE000E184)
#define NVIC_ICER2			((volatile uint32_t*)0xE000E188)
#define NVIC_ICER3			((volatile uint32_t*)0xE000E18C)


#define NVIC_PR_BASE_ADDR	((volatile uint32_t*)0xE000E400)



#define SRAM_BASEADDR 0x20000000U   /* 	SRAM BASE ADDRESS */
#define FLASH_BASEADDR 0x08000000U /* FLASH BASE ADDRESS */

#define ROM 0x1FFF0000U  /* ROM */

#define PERIPH_BASE	0x40000000U
#define APB1PERIPH_BASE PERIPH_BASE
#define APB2PERIPH_BASE 0x40010000
#define AHB1PERIPH_BASE 0x40020000
#define AHB2PERIPH_BASE 0x50000000

/*PERIPHERALS HANGING ON AHB1 */

#define GPIOA_BASEADDR (AHB1PERIPH_BASE + 0x0000)
#define GPIOB_BASEADDR (AHB1PERIPH_BASE + 0x0400)
#define GPIOC_BASEADDR (AHB1PERIPH_BASE + 0x0800)
#define GPIOD_BASEADDR (AHB1PERIPH_BASE + 0x0C00)
#define GPIOE_BASEADDR (AHB1PERIPH_BASE + 0x1000)
#define GPIOH_BASEADDR (AHB1PERIPH_BASE + 0x1C00)
#define CRC_BASEADDR (AHB1PERIPH_BASE + 0x3000)
#define RCC_BASEADDR (AHB1PERIPH_BASE + 0x3800)
#define FIR_BASEADDR (AHB1PERIPH_BASE + 0x3C00) /* FLAG INTERFACE REGISTER */
#define DMA1_BASEADDR (AHB1PERIPH_BASE + 0x6000)
#define DMA2_BASEADDR (AHB1PERIPH_BASE + 0x6400)
#define USBOTGFS_BASEADDR (AHB1PERIPH_BASE + 0x10000000)

/*PERIPHERALS HANGING ON APB1 BUS*/

#define I2C1_BASEADDR (APB1PERIPH_BASE + 0x5400)
#define I2C2_BASEADDR (APB1PERIPH_BASE + 0x5800)
#define I2C3_BASEADDR (APB1PERIPH_BASE + 0x5C00)
#define SPI2_BASEADDR (APB1PERIPH_BASE + 0x3800)
#define SPI3_BASEADDR (APB1PERIPH_BASE + 0x3C00)
#define USART2_BASEADDR (APB1PERIPH_BASE + 0x4400)

/*PERPHERALS HANGING ON APB2 BUS */
#define EXTI_BASEADDR (APB2PERIPH_BASE + 0x3C00)
#define SPI1_BASEADDR (APB2PERIPH_BASE + 0x3000)
#define SPI4_BASEADDR (APB2PERIPH_BASE + 0x3400)
#define SYSCFG_BASEADDR (APB2PERIPH_BASE + 0x3800)
#define USART1_BASEADDR (APB2PERIPH_BASE + 0x1000)
#define USART6_BASEADDR (APB2PERIPH_BASE + 0x1400)


/* GPIO REGISTER DEFINITION STRUCTURE*/

typedef struct
{
	 volatile uint32_t MODER;				 /*GPIO port mode register*/
	 volatile uint32_t OTYPER;			/*GPIO port output type register*/
	 volatile uint32_t OSPEEDR;			/*GPIO port output speed register*/
	 volatile uint32_t PUPDR;			/*GPIO port pull-up/pull-down register*/
	 volatile uint32_t IDR;				/*GPIO port input data register*/
	 volatile uint32_t ODR;				/*GPIO port output data register*/
	 volatile uint32_t BSRR;				/*GPIO port bit set/reset register*/
	 volatile uint32_t LCKR;				/*GPIO port configuration lock register*/
	 volatile uint32_t AFR[2];			/*AFH[1]: GPIO alternate function low register AFH[2]: GPIO alternate function high register */
} GPIO_Reg_Def_t;

typedef struct
{
	volatile uint32_t CR;
	volatile uint32_t PLLCFGR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t AHB1RSTR;
	volatile uint32_t AHB2RSTR;
	volatile uint32_t RESERVED1;
	volatile uint32_t RESERVED2;
	volatile uint32_t APB1RSTR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t RESERVED3;
	volatile uint32_t RESERVED4;
	volatile uint32_t AHB1ENR;
	volatile uint32_t AHB2ENR;
	volatile uint32_t RESERVEDd3;
	volatile uint32_t RESERVEDd4;
	volatile uint32_t APB1ENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t RSERVED5;
	volatile uint32_t RESERVED6;
	volatile uint32_t AHB1LPENR;
	volatile uint32_t AHB2LPENR;
	volatile uint32_t RESERVED7;
	volatile uint32_t RESERVED8;
	volatile uint32_t APB1LPENR;
	volatile uint32_t APB2LPENR;
	volatile uint32_t RESERVED9;
	volatile uint32_t RESERVED10;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	volatile uint32_t RESERVED11;
	volatile uint32_t RESERVED12;
	volatile uint32_t SSCGR;
	volatile uint32_t PLLI2SCGR;
	volatile uint32_t DCKCFGR;
} RCC_Reg_Def_t;

// EXTI REGISTER DEFINITION STRUCTURE

typedef  struct
{
	volatile uint32_t  IMR;   // INTERRUPT MASK REGISTER
	volatile uint32_t  EMR;  // EVENT MASK REGISTER
	volatile uint32_t  RTSR; //RISING TRIGGER  SELECTION REGISTER
	volatile uint32_t  FTSR; // FALLING TRIGGER SELECTION REGISTER
	volatile uint32_t  SWIER; //SOFTWARE INTERRUPT EVENT REGISTER
	volatile uint32_t  PR; //PENDING REGISTER



} EXTI_Reg_Def_t;

// SYSCONFIG REGISTER DEFINITION STRUCTURE

typedef struct
{
	volatile uint32_t MEMRMP; // memory remap register
	volatile uint32_t PMC;    // peripheral control mode register
	volatile uint32_t EXTICR[4]; //external interrupt configure registers
	volatile uint32_t RESERVED1[2]; // reserved
	volatile uint32_t CMPCR; // compensation cell control register
} SYSCONFIG_Reg_Def_t;

typedef struct
{
	volatile uint32_t  CR1;
	volatile uint32_t  CR2;
	volatile uint32_t  SR;
	volatile uint32_t  DR;
	volatile uint32_t  CRCPR;
	volatile uint32_t  RXCRCR;
	volatile uint32_t  TXCRCR;
	volatile uint32_t  I2SCFGR;
	volatile uint32_t  I2SPR;

} SPI_Reg_Def_t;

typedef struct
{
	volatile uint32_t  CR1;
	volatile uint32_t  CR2;
	volatile uint32_t  OAR1;
	volatile uint32_t  OAR2;
	volatile uint32_t  DR;
	volatile uint32_t  SR1;
	volatile uint32_t  SR2;
	volatile uint32_t  CCR;
	volatile uint32_t  TRISE;
	volatile uint32_t  FLTR;



}I2C_Reg_Def_t;








/*peripheral definitons typecaseted to regdef*/

//GPIO REGDEFS
#define GPIOA	((GPIO_Reg_Def_t*)GPIOA_BASEADDR)
#define GPIOB	((GPIO_Reg_Def_t*)GPIOB_BASEADDR)
#define GPIOC	((GPIO_Reg_Def_t*)GPIOC_BASEADDR)
#define GPIOD	((GPIO_Reg_Def_t*)GPIOD_BASEADDR)
#define GPIOE	((GPIO_Reg_Def_t*)GPIOE_BASEADDR)
#define GPIOH	((GPIO_Reg_Def_t*)GPIOH_BASEADDR)

//I2C REGDEFS
#define SPI1	((SPI_Reg_Def_t*)SPI1_BASEADDR)
#define SPI2	((SPI_Reg_Def_t*)SPI2_BASEADDR)
#define SPI3	((SPI_Reg_Def_t*)SPI3_BASEADDR)
#define SPI4	((SPI_Reg_Def_t*)SPI4_BASEADDR)

//I2C REG DEFS
#define I2C1	((I2C_Reg_Def_t*)I2C1_BASEADDR)
#define I2C2	((I2C_Reg_Def_t*)I2C2_BASEADDR)
#define I2C3	((I2C_Reg_Def_t*)I2C3_BASEADDR)





#define RCC		((RCC_Reg_Def_t*)RCC_BASEADDR)

#define EXTI 	((EXTI_Reg_Def_t*)EXTI_BASEADDR)

#define SYSCFG  ((SYSCONFIG_Reg_Def_t* )SYSCFG_BASEADDR)


/* CLOCK ENABLE MACROS FOR GPIO */

#define GPIOA_PCLK_EN()		(RCC->AHB1ENR |= (1<<0))
#define GPIOB_PCLK_EN()		(RCC->AHB1ENR |= (1<<1))
#define GPIOC_PCLK_EN()		(RCC->AHB1ENR |= (1<<2))
#define GPIOD_PCLK_EN()		(RCC->AHB1ENR |= (1<<3))
#define GPIOE_PCLK_EN()		(RCC->AHB1ENR |= (1<<4))
#define GPIOH_PCLK_EN()		(RCC->AHB1ENR |= (1<<7))

/*CLOCK ENABLE MACROS FOR I2CX */

#define I2C1_PCLK_EN()		(RCC->APB1ENR |=(1<<21))
#define I2C2_PCLK_EN()		(RCC->APB1ENR |=(1<<22))
#define I2C3_PCLK_EN()		(RCC->APB1ENR |=(1<<23))

/* CLOCK ENABLE MACROS FOR SPI */

#define  SPI1_PCLK_EN()		(RCC->APB2ENR |= (1<<12))
#define  SPI2_PCLK_EN()		(RCC->APB1ENR |= (1<<14))
#define  SPI3_PCLK_EN()		(RCC->APB1ENR |= (1<<15))
#define  SPI4_PCLK_EN()		(RCC->APB2ENR |= (1<<13))

/*CLOCK ENABLE MACROS FOR  USART */
#define USART1_PCLK_EN()	(RCC->APB2ENR |= (1<<4))
#define USART6_PCLK_EN()	(RCC->APB2ENR |= (1<<5))
#define USART2_PCLK_EN()	(RCC->APB1ENR |= (1<<17))

/*CLOCK ENABLE MACROS FOR SYSCFG PERIPHERAL*/
#define SYSCFG_PCLK_EN()	(RCC->APB2ENR |= (1<<14))

/* CLOCK DISABLE MACROS FOR GPIO */

#define GPIOA_PCLK_DI()		(RCC->AHB1ENR &= ~(1<<0))
#define GPIOB_PCLK_DI()		(RCC->AHB1ENR &= ~(1<<1))
#define GPIOC_PCLK_DI()		(RCC->AHB1ENR &= ~(1<<2))
#define GPIOD_PCLK_DI()		(RCC->AHB1ENR &= ~(1<<3))
#define GPIOE_PCLK_DI()		(RCC->AHB1ENR &= ~(1<<4))
#define GPIOH_PCLK_DI()		(RCC->AHB1ENR &= ~(1<<7))

/*CLOCK DISABLE MACROS FOR I2CX */

#define I2C1_PCLK_DI()		(RCC->APB1ENR &= ~(1<<21))
#define I2C2_PCLK_DI()		(RCC->APB1ENR &= ~(1<<22))
#define I2C3_PCLK_DI()		(RCC->APB1ENR &= ~(1<<23))

/* CLOCK DISABLE MACROS FOR SPI */

#define  SPI1_PCLK_DI()		(RCC->APB2ENR &= ~(1<<12))
#define  SPI2_PCLK_DI()		(RCC->APB1ENR &= ~(1<<14))
#define  SPI3_PCLK_DI()		(RCC->APB1ENR &= ~(1<<15))
#define  SPI4_PCLK_DI()		(RCC->APB2ENR &= ~(1<<13))

/*CLOCK DISABLE MACROS FOR  USART */
#define USART1_PCLK_DI()	(RCC->APB2ENR &= ~(1<<4))
#define USART6_PCLK_DI()	(RCC->APB2ENR &= ~(1<<5))
#define USART2_PCLK_DI()	(RCC->APB1ENR &= ~(1<<17))

/*CLOCK DISABLE MACROS FOR SYSCFG PERIPHERAL*/
#define SYSCFG_PCLK_DI()	(RCC->APB2ENR &= ~(1<<14))

// MACROS TO DISABLE GPIOX PERIPHERAL
#define GPIOA_REG_RESET()  do { (RCC->AHB1RSTR |=(1<<0)); (RCC->AHB1RSTR &= ~(1<<0));}while(0)
#define GPIOB_REG_RESET()  do { (RCC->AHB1RSTR |=(1<<1)); (RCC->AHB1RSTR &= ~(1<<1));}while(0)
#define GPIOC_REG_RESET()  do { (RCC->AHB1RSTR |=(1<<2)); (RCC->AHB1RSTR &= ~(1<<2));}while(0)
#define GPIOD_REG_RESET()  do { (RCC->AHB1RSTR |=(1<<3)); (RCC->AHB1RSTR &= ~(1<<3));}while(0)
#define GPIOE_REG_RESET()  do { (RCC->AHB1RSTR |=(1<<4)); (RCC->AHB1RSTR &= ~(1<<4));}while(0)
#define GPIOH_REG_RESET()  do { (RCC->AHB1RSTR |=(1<<7)); (RCC->AHB1RSTR &= ~(1<<7));}while(0)



//MACROS TO DISABLE SPI PERIPHERALS
#define SPI2_REG_RESET()  do { (RCC->APB1RSTR |=(1<<14)); (RCC->APB1RSTR &= ~(1<<14));}while(0)
#define SPI3_REG_RESET()  do { (RCC->APB1RSTR |=(1<<15)); (RCC->APB1RSTR &= ~(1<<15));}while(0)
#define SPI1_REG_RESET()  do { (RCC->APB2RSTR |=(1<<12)); (RCC->APB2RSTR &= ~(1<<12));}while(0)
#define SPI4_REG_RESET()  do { (RCC->APB2RSTR |=(1<<13)); (RCC->APB2RSTR &= ~(1<<13));}while(0)

//MACROS TO DISABLE I2C PERIPHERALS
#define I2C1_REG_RESET()  do { (RCC->APB1RSTR |=(1<<21)); (RCC->APB1RSTR &= ~(1<<21));}while(0)
#define I2C2_REG_RESET()  do { (RCC->APB1RSTR |=(1<<22)); (RCC->APB1RSTR &= ~(1<<22));}while(0)
#define I2C3_REG_RESET()  do { (RCC->APB1RSTR |=(1<<23)); (RCC->APB1RSTR &= ~(1<<23));}while(0)







#define  gpio_baseaddr_to_code(x) 	((x == GPIOA)?0:\
									 (x == GPIOB)?1:\
									 (x == GPIOC)?2:\
									 (x == GPIOD)?3:\
									 (x == GPIOE)?4:\
									 (x == GPIOH)?7:0)

// IRQ NUMBER DEFINITION

#define IRQ_NO_EXTI0		6
#define IRQ_NO_EXTI1		7
#define IRQ_NO_EXTI2		8
#define IRQ_NO_EXTI3		9
#define IRQ_NO_EXTI4		10
#define IRQ_NO_EXTI9_5		23
#define IRQ_NO_EXTI15_10    40




// some generic macros
#define ENABLE			1
#define DISABLE		 	0
#define SET 		 	ENABLE
#define RESET 		 	DISABLE
#define GPIO_PIN_SET	SET
#define GPIO_PIN_RESET	RESET


#include "stm32f401xx_gpio_driver.h"
#include "stm32f401xx_spi_driver.h"
#include "stm32f401xx_i2c_driver.h"


#endif /* INC_STM3F407XX_H_ */






