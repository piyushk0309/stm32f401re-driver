/*
 * stm32f401xx_gpio_driver.c
 *
 *  Created on: 03-Apr-2026
 *      Author: hp
 */


#include "stm32f401xx_gpio_driver.h"


										/* API SUPPORTED BY THIS DRIVER */



/* PERIPHERAL CLOCK SETUP*/
/*********************************************************************
 * @fn      		  - GPIO_PeriClockControl
 *
 * @brief             - This function enables or disables peripheral clock for the given GPIO port
 *
 * @param[in]         - base address of the gpio peripheral
 * @param[in]         - ENABLE or DISABLE macros
 * @param[in]         -
 *
 * @return            -  none
 *
 * @Note              -  none

 */


void GPIO_PeriClockControl(GPIO_Reg_Def_t *pGPIOx,uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_EN();
		}
		else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_EN();
		}
		else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_EN();
		}
		else if(pGPIOx == GPIOD)
		{
			GPIOD_PCLK_EN();
		}
		else if(pGPIOx == GPIOE)
		{
			GPIOE_PCLK_EN();
		}
		else if(pGPIOx == GPIOH)
		{
			GPIOH_PCLK_EN();
		}
	}
	else
	{
				if(pGPIOx == GPIOA)
				{
					GPIOA_PCLK_DI();
				}
				else if(pGPIOx == GPIOB)
				{
					GPIOB_PCLK_DI();
				}
				else if(pGPIOx == GPIOC)
				{
					GPIOC_PCLK_DI();
				}
				else if(pGPIOx == GPIOD)
				{
					GPIOD_PCLK_DI();
				}
				else if(pGPIOx == GPIOE)
				{
					GPIOE_PCLK_DI();
				}
				else if(pGPIOx == GPIOH)
				{
					GPIOH_PCLK_DI();
				}

	}

}





/*INIT AND DE-INIT*/

/*********************************************************************
 * @fn      		  - GPIO_Init
 *
 * @brief             - This function is used to initialise the gpio pin
 *
 * @param[in]         - GPIO_Handle_t
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -  none
 *
 * @Note              -  none

 */

void GPIO_Init(GPIO_Handle_t *pGPIOHandle){

	// CONFIG THE MODE OF GPIO PIN
	uint32_t temp; // temp register

	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
	{ //NON INTERRUPT MODE
		temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		pGPIOHandle->pGPIOx->MODER	&= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandle->pGPIOx->MODER  |= temp;

	}
	else
	{
		//this part we will code later (interrupt mode)

		if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
		{
			//1.configure the ftsr
			EXTI->FTSR  |= (1<<pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			//clear corresponding rtsr bit
			EXTI->RTSR &= (1<<pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

		}
		else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
		{
			//1. configure figure the rtsr
			EXTI->RTSR |= (1<<pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			// clear corresponding ftsr bit
			EXTI->FTSR  |= (1<<pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);



		}
		else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode ==  GPIO_MODE_IT_RT)
		{
			//1. configure  both ftsr and rtsr
			EXTI->FTSR  |= (1<<pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->RTSR  |= (1<<pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}

		//2. configure the gpio port selection in SYSCONFIG_EXTICR
		uint8_t temp1= pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber/4;
		uint8_t temp2= pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber%4;
		uint8_t portcode = gpio_baseaddr_to_code(pGPIOHandle->pGPIOx);
		SYSCFG_PCLK_EN();
		SYSCFG->EXTICR[temp1] &= ~(0xF << (4 * temp2));
		SYSCFG->EXTICR[temp1] |= portcode <<(temp2*4);

		//3. ENABLE THE EXTI INTERRUPT  DELIVERY USING IMR
		EXTI->IMR  |= (1<<pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

	}


	// CONFIG THE SPEED

	temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed<< (2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OSPEEDR |= temp;

	//CONFIG THE PUPD SETTINGS
	temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl<< (2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->PUPDR |= temp;


	//CONFIG THE OUTPUT TYPES
	temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OTYPER &= ~(0x1 << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OTYPER |= temp;

	//CONFIG THE ALT FUNCTIONALITY
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode==GPIO_MODE_ALTFN)
	{
		// config alt functionality
		uint8_t temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber/8;
		uint8_t temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber%8;
		pGPIOHandle->pGPIOx->AFR[temp1] |= (0x4<< (4*temp2));
		pGPIOHandle->pGPIOx->AFR[temp1] &= ~(pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4*temp2));


	}

}



/*********************************************************************
 * @fn      		  - GPIO_DeInit
 *
 * @brief             - This function is used to dinitialise GPIO port
 *
 * @param[in]         - base address of gpio port
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -  none
 *
 * @Note              -  none

 */

void GPIO_DeInit(GPIO_Reg_Def_t *pGPIOx)
{

			if(pGPIOx == GPIOA)
			{
				GPIOA_REG_RESET();
			}
			else if(pGPIOx == GPIOB)
			{
				GPIOB_REG_RESET();
			}
			else if(pGPIOx == GPIOC)
			{
				GPIOC_REG_RESET();
			}
			else if(pGPIOx == GPIOD)
			{
				GPIOD_REG_RESET();
			}
			else if(pGPIOx == GPIOE)
			{
				GPIOE_REG_RESET();
			}
			else if(pGPIOx == GPIOH)
			{
				GPIOH_REG_RESET();
			}

}








/*data read and write */


/*********************************************************************
 * @fn      		  - GPIO_ReadFromInputPin
 *
 * @brief             - This function is used to read from an gpio input pin
 *
 * @param[in]         - base address of the gpio peripheral
 * @param[in]         - pin number of that port
 * @param[in]         -
 *
 * @return            -  0 or 1
 *
 * @Note              -  none

 */

uint8_t GPIO_ReadFromInputPin(GPIO_Reg_Def_t *pGPIOx,uint8_t PinNumber){

	uint8_t value;

	value  = (uint8_t)((pGPIOx->IDR >>PinNumber)& 0x00000001);

	return value;

}

/*********************************************************************
 * @fn      		  - GPIO_ReadFromInputPort
 *
 * @brief             - This function is used to read from an gpio input port
 *
 * @param[in]         - base address of the gpio peripheral
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -  uint8_t
 *
 * @Note              -  none

 */

uint16_t GPIO_ReadFromInputPort(GPIO_Reg_Def_t *pGPIOx)
{
	uint16_t value;

	value  = (uint16_t)(pGPIOx->IDR);

	return value;

}

/*********************************************************************
 * @fn      		  - GPIO_WriTeToOutputPin
 *
 * @brief             - This function is used to write to an gpio output pin
 *
 * @param[in]         - base address of the gpio peripheral
 * @param[in]         - pin number of that gpio port
 * @param[in]         - value to write
 *
 * @return            -  uint16_t
 *
 * @Note              -  none

 */

void GPIO_WriteToOutputPin(GPIO_Reg_Def_t *pGPIOx,uint8_t PinNumber,uint8_t Value)
{
	if(Value == GPIO_PIN_SET)
	{
		// WRITE 1 TO THE OUTPUT DATA REGISTER CORRESPONDING TO THE PIN NUMBER
		pGPIOx->ODR |= (1<<PinNumber);
	}
	else
	{
		pGPIOx->ODR &= ~(1<<PinNumber);

	}

}

/*********************************************************************
 * @fn      		  - GPIO_WriteToOutputPort
 *
 * @brief             - This function is used to write to an gpio input port
 *
 * @param[in]         - base address of the gpio peripheral
 * @param[in]         - value to be written
 * @param[in]         -
 *
 * @return            -  none
 *
 * @Note              -  none

 */

void GPIO_WriteToOuputPort(GPIO_Reg_Def_t *pGPIOx,uint16_t Value){

	pGPIOx->ODR = Value;

}


/*********************************************************************
 * @fn      		  - GPIO_ToggleOutputPin
 *
 * @brief             - This function is used to toggle the output pins value
 *
 * @param[in]         - base address of the gpio peripheral
 * @param[in]         - pin number of that port
 * @param[in]         -
 *
 * @return            -  none
 *
 * @Note              -  none

 */

void GPIO_ToggleOutputPin(GPIO_Reg_Def_t *pGPIOx,uint8_t PinNumber)
{

	pGPIOx->ODR ^= (0x1<<PinNumber);

}



/*********************************************************************
 * @fn      		  - GPIO_IRQConfig
 *
 * @brief             - interrupt request configuration of that gpio port
 *
 * @param[in]         - irq number of that interrupt
 * @param[in]         - priority number of that interrupt
 * @param[in]         - enable or disable macros
 *
 * @return            -  none
 *
 * @Note              -  none

 */

void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
{

	if(EnorDi == ENABLE)
	{
	if(IRQNumber <= 31)
	{
		//program iser0 register
		*NVIC_ISER0 |= (1 << IRQNumber);
	}
	else if (IRQNumber >31 && IRQNumber <64)
	{
		//program iser1 register
		*NVIC_ISER1 |= (1 << (IRQNumber%32));

	}
	else if(IRQNumber >= 64 && IRQNumber < 96)
	{
		//program iser2 register
		*NVIC_ISER2 |= (1 << (IRQNumber%64));
	}
	}

	else
	{

		if(IRQNumber <= 31)
			{
				//program icer0 register
			*NVIC_ICER0 |= (1 << IRQNumber);

			}
			else if (IRQNumber >31 && IRQNumber <64)
			{
				//program icer1 register
				*NVIC_ICER1 |= (1 << (IRQNumber%32));
			}
			else if(IRQNumber >= 64 && IRQNumber < 96)
			{
				//program icer2 register
				*NVIC_ICER2 |= (1 << (IRQNumber%64));
			}

	}

}


void  GPIO_IRQPriorityConfig(uint8_t IRQNumber,uint32_t Priority )
{
	// first lets find out priority register
	uint8_t iprx = IRQNumber/4;
	uint8_t iprx_section = IRQNumber %4;

	*(NVIC_PR_BASE_ADDR +(iprx)) |= (Priority << (8*iprx_section+4)); // FOR ARM CROTEX M4 ONLY AS LOWER 4 BITS ARE NOT APPLICABLE


}


/*********************************************************************
 * @fn      		  - GPIO_IRQHandling
 *
 * @brief             - interrupt request handling function
 *
 * @param[in]         - pin number where the interrupt has arrived on
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -  none
 *
 * @Note              -  none

 */


void GPIO_IRQHandling(uint8_t PinNumber)
{
	if(EXTI->PR& (1<<PinNumber))
	{
		EXTI->PR  |= (1<<PinNumber);

	}


}





