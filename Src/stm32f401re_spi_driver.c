/*
 * stm32f401xx_SPI_driver.c
 *
 *  Created on: 15-Apr-2026
 *      Author: TGT
 */


#include "stm32f401xx_SPI_driver.h"


static void SPI_txe_interrupt_handle(SPI_Handle_t *pSPIHandle);
static void SPI_rxne_interrupt_handle(SPI_Handle_t *pSPIHandle);
static void SPI_ovr_err_interrupt_handle(SPI_Handle_t *pSPIHandle);



/* PERIPHERAL CLOCK SETUP*/
/*********************************************************************
 * @fn      		  - SPI_PeriClockControl
 *
 * @brief             - This function enables or disables peripheral clock for the given SPI port
 *
 * @param[in]         - base address of the SPI peripheral
 * @param[in]         - ENABLE or DISABLE macros
 * @param[in]         -
 *
 * @return            -  none
 *
 * @Note              -  none

 */


void SPI_PeriClockControl(SPI_Reg_Def_t *pSPIx,uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pSPIx == SPI1)
		{
			SPI1_PCLK_EN();
		}
		else if(pSPIx == SPI2)
		{
			SPI2_PCLK_EN();
		}
		else if(pSPIx == SPI3)
		{
			SPI3_PCLK_EN();
		}
		else if(pSPIx == SPI4)
		{
			SPI4_PCLK_EN();
		}

	}
	else
	{
		if(pSPIx == SPI1)
				{
					SPI1_PCLK_DI();
				}
				else if(pSPIx == SPI2)
				{
					SPI2_PCLK_DI();
				}
				else if(pSPIx == SPI3)
				{
					SPI3_PCLK_DI();
				}
				else if(pSPIx == SPI4)
				{
					SPI4_PCLK_DI();
				}
	}

}

/*INIT AND DE-INIT*/

/*********************************************************************
 * @fn      		  - SPI_Init
 *
 * @brief             - This function is used to initialise the SPI pin
 *
 * @param[in]         - SPI_Handle_t
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -  none
 *
 * @Note              -  none

 */

void SPI_Init(SPI_Handle_t *pSPIHandle){

	//CLOCK ENABLE
	SPI_PeriClockControl(pSPIHandle->pSPIx, ENABLE);

	// CONFIGURING SPI CR1 REGISTER
	uint32_t tempreg =0;

	//1. configuring the device mode
	tempreg |= pSPIHandle->SPIConfig.SPI_DeviceMode<<2;

	//2. configuring the bus config
	if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD)
	{
		//BIDI MODE SHOULD BE CLARED
		tempreg &= ~(1 << 15);
	}
	else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD)
	{
		//BIDI MODE SHOULD BE SET
		tempreg |= (1 << 15);

	}
	else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY)
	{
			//BIDI MODE SHOULD BE SET
			tempreg |= (1 << 15);
	}

	//3. Configuring SPI serial clock speed (baud rate)
	tempreg |= pSPIHandle->SPIConfig.SPI_SclkSpeed<<3;

	//4. configuring the DFF
	tempreg |= pSPIHandle->SPIConfig.SPI_DFF<<11;


	//5.configuring CPOL  and CPHA
	tempreg |= pSPIHandle->SPIConfig.SPI_CPOL<<1;
	tempreg |= pSPIHandle->SPIConfig.SPI_CPHA;

	//6. CONFIGURE SSM
	tempreg |= pSPIHandle->SPIConfig.SPI_SSM <<9;

	pSPIHandle->pSPIx->CR1 = tempreg;
}


void SPI_DeInit(SPI_Reg_Def_t *pSPIx)
{

			if(pSPIx == SPI1)
			{
				SPI1_REG_RESET();
			}
			else if(pSPIx == SPI2)
			{
				SPI2_REG_RESET();
			}
			else if(pSPIx == SPI3)
			{
				SPI3_REG_RESET();
			}
			else if(pSPIx == SPI4)
			{
				SPI4_REG_RESET();
			}


}

/*SEND DATA*/

/*********************************************************************
 * @fn      		  - SPI_SendData
 *
 * @brief             - This function is used to send data from the SPI pin
 *
 * @param[in]         - SPI_Reg_Def_t, ptxbuffer, length
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -  none
 *
 * @Note              -  this is a blocking call or polling type function

 */

void SPI_SendData(SPI_Reg_Def_t *pSPIx,uint8_t *pTxBuffer, uint32_t Len)
{


	while(Len>0)
	{
		//1.WAIT UNTIL TxE IS SET
		while(!(pSPIx->SR&(1<<1)));

			//2.CHECK THE DFF BIT  IN CR1
		if(pSPIx->CR1 &(1<<11))
			{
				//16 BIT DFF FORMAT
				//1. load the data into data register
				pSPIx->DR = *((uint16_t*)pTxBuffer);
				Len--;
				Len--;
				(uint16_t*)pTxBuffer++;
			}
		else
			{
				//8 bit dff format
				pSPIx->DR = *(pTxBuffer);
				Len--;
				pTxBuffer++;
			}

	}

}

/*RX DATA*/

/*********************************************************************
 * @fn      		  - SPI_RecieveData
 *
 * @brief             - This function is used to RECIEVE data from the SPI pin
 *
 * @param[in]         - SPI_Reg_Def_t, prxbuffer, length
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -  this is a blocking call or polling type function

 */

void SPI_RecieveData(SPI_Reg_Def_t *pSPIx,uint8_t *pRxBuffer, uint32_t Len)
{


	while(Len>0)
	{
		//1.WAIT UNTIL TxE IS SET
		while(!(pSPIx->SR&(1<<0)));

			//2.CHECK THE DFF BIT  IN CR1
		if(pSPIx->CR1 &(1<<11))
			{
				//16 BIT DFF FORMAT
				//1. load the data from data register
			*((uint16_t*)pRxBuffer) = pSPIx->DR ;
				Len--;
				Len--;
				(uint16_t*)pRxBuffer++;
			}
		else
			{
				//8 bit dff format
			    *(pRxBuffer)	= pSPIx->DR ;
				Len--;
				pRxBuffer++;
			}

	}

}



/*********************************************************************
 * @fn      		  - SPI_SendDataIT
 *
 * @brief             - This function is used to SEND data from the SPI pin
 *
 * @param[in]         - SPI_Handle_t, prxbuffer, length
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -  uint8_t (state of tx)
 *
 * @Note              -  this is a non blocking call or interrupt type function

 */

uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIHandle,uint8_t *pTxBuffer, uint32_t Len)
{

	uint8_t State	 = pSPIHandle->TxState;

	if(State!= SPI_BUSY_IN_TX)
	{
		//1. save tx buffer address and len in global variables
		pSPIHandle->pTxBuffer = pTxBuffer;
		pSPIHandle->TxLen = Len;

		//2. mark the SPI state as busy in tx
		// no other code can takeover while same SPI peripheral until tx is over
		pSPIHandle->TxState = SPI_BUSY_IN_TX;


		//3. enable the txeie control bit to get interrupt whenever the txe flag  is set in SR
		pSPIHandle->pSPIx->CR2 |= 1<<7;


	}

	return State;

}

/*********************************************************************
 * @fn      		  - SPI_RecieveDataIT
 *
 * @brief             - This function is used to RECIEVE data from the SPI pin
 *
 * @param[in]         - SPI_Handle_t, prxbuffer, length
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -  uint8_t (state of tx)
 *
 * @Note              -  this is a non blocking call or interrupt type function

 */

uint8_t SPI_RecieveDataIT(SPI_Handle_t *pSPIHandle,uint8_t *pRxBuffer, uint32_t Len)
{

	uint8_t State	 = pSPIHandle->RxState;

	if(State!= SPI_BUSY_IN_RX)
	{
		//1. save rx buffer address and len in global variables
		pSPIHandle->pRxBuffer = pRxBuffer;
		pSPIHandle->RxLen = Len;

		//2. mark the SPI state as busy in rx
		// no other code can takeover while same SPI peripheral until rx is over
		pSPIHandle->RxState = SPI_BUSY_IN_RX;


		//3. enable the rxeie control bit to get interrupt whenever the rxe flag  is set in SR
		pSPIHandle->pSPIx->CR2 |= 1<<6;


	}

	return State;

}




/*********************************************************************
 * @fn      		  - SPI_PeripheralControl
 *
 * @brief             - This function is used to inable or disable the SPI peripheral
 *
 * @param[in]         - SPI_Reg_Def_t
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -  none
 *
 * @Note              -  none

 */




void SPI_PeripheralControl(SPI_Reg_Def_t *pSPIx,uint8_t ENorDI)
{
	if(ENorDI == ENABLE)
	{
		pSPIx->CR1 |= 1<<6;
	}
	else
	{
		pSPIx->CR1 &= ~(1<<6);
	}


}


void SPI_SSIConfig(SPI_Reg_Def_t *pSPIx, uint8_t ENorDI)
{
	if(ENorDI == ENABLE)
	{
		pSPIx->CR1 |= 1<<8;
	}
	else
	{
		pSPIx->CR1 &= ~(1<<8);
	}

}


/*********************************************************************
 * @fn      		  - SPI_IRQConfig
 *
 * @brief             - interrupt request configuration of that SPI port
 *
 * @param[in]         - irq number of that interrupt
 * @param[in]         - priority number of that interrupt
 * @param[in]         - enable or disable macros
 *
 * @return            -  none
 *
 * @Note              -  none

 */

void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
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


void  SPI_IRQPriorityConfig(uint8_t IRQNumber,uint32_t Priority )
{
	// first lets find out priority register
	uint8_t iprx = IRQNumber/4;
	uint8_t iprx_section = IRQNumber %4;

	*(NVIC_PR_BASE_ADDR +(iprx)) |= (Priority << (8*iprx_section+4)); // FOR ARM CROTEX M4 ONLY AS LOWER 4 BITS ARE NOT APPLICABLE


}

void SPI_IRQHandling(SPI_Handle_t *pSPIHandle)
{

	uint8_t temp1 , temp2;

	//txe check
	temp1 = pSPIHandle->pSPIx->SR&(1<<1);
	temp2 = pSPIHandle->pSPIx->CR2&(1<<7);

	if(temp1&&temp2)
	{
		SPI_txe_interrupt_handle(pSPIHandle);
	}

	//rxe check
	temp1 = pSPIHandle->pSPIx->SR&(1<<0);
	temp2 = pSPIHandle->pSPIx->CR2&(1<<6);

	if(temp1&&temp2)
	{
		SPI_rxne_interrupt_handle(pSPIHandle);
	}

	//overrun check
	temp1 = pSPIHandle->pSPIx->SR&(1<<6);
	temp2 = pSPIHandle->pSPIx->CR2&(1<<5);

	if(temp1&&temp2)
	{
		SPI_ovr_err_interrupt_handle(pSPIHandle);
	}



}


// some helper functions implementations
static void SPI_txe_interrupt_handle(SPI_Handle_t *pSPIHandle)
{
	//2.CHECK THE DFF BIT  IN CR1
		if(pSPIHandle->pSPIx->CR1 &(1<<11))
			{
				//16 BIT DFF FORMAT
				//1. load the data into data register
				pSPIHandle->pSPIx->DR = *((uint16_t*)pSPIHandle->pTxBuffer);
				pSPIHandle->TxLen--;
				pSPIHandle->TxLen--;
				(uint16_t*)pSPIHandle->pTxBuffer++;
			}
		else
			{
				//8 bit dff format
				pSPIHandle->pSPIx->DR = *(pSPIHandle->pTxBuffer);
				pSPIHandle->TxLen--;
				pSPIHandle->pTxBuffer++;
			}

		if(!pSPIHandle->TxLen)
		{
			//txlen is zero , so close the SPI transmission and inform the application that
			//tx is over

			//this prevents interrupt from setting up of txe flag
			SPI_CloseTx(pSPIHandle);
			SPI_ApplicationEventCallback(pSPIHandle,SPI_EVENT_TX_CMPLT);


		}

}
static void SPI_rxne_interrupt_handle(SPI_Handle_t *pSPIHandle)
{
	//2.CHECK THE DFF BIT  IN CR1
		if(pSPIHandle->pSPIx->CR1 &(1<<11))
			{
				//16 BIT DFF FORMAT
				//1. load the data from data register
			*((uint16_t*)pSPIHandle->pRxBuffer) = (uint16_t)pSPIHandle->pSPIx->DR ;
				pSPIHandle->RxLen--;
				pSPIHandle->RxLen--;
				(uint16_t*)pSPIHandle->pRxBuffer++;
			}
		else
			{
				//8 bit dff format
			    *(pSPIHandle->pRxBuffer)	= pSPIHandle->pSPIx->DR ;
				pSPIHandle->RxLen--;
				pSPIHandle->pRxBuffer++;
			}
		if(!pSPIHandle->RxLen)
			{
				//Rxlen is zero , so close the SPI transmission and inform the application that
				//Rx is over

				//this prevents interrupt from setting up of RXNEIE flag
				SPI_CloseRx(pSPIHandle);
				SPI_ApplicationEventCallback(pSPIHandle,SPI_EVENT_RX_CMPLT);


			}

}
static void SPI_ovr_err_interrupt_handle(SPI_Handle_t *pSPIHandle)
{

	uint8_t temp;

	//1.clear the ovr flag
	if(pSPIHandle->TxState != SPI_BUSY_IN_TX)
	{
		temp = pSPIHandle->pSPIx->DR;
		temp = pSPIHandle->pSPIx->SR;
	}

	(void) temp;
	//inform the application
	SPI_ApplicationEventCallback(pSPIHandle,SPI_EVENT_OVR_ERR);


}


void SPI_ClearOVRFlag(SPI_Reg_Def_t *pSPIx)
{
	uint8_t temp;
	temp = pSPIx->DR;
	temp = pSPIx->SR;

	(void) temp;


}



void SPI_CloseTx(SPI_Handle_t *pSPIHandle)
{
	pSPIHandle->pSPIx->CR2 &= ~(1<<7);
	pSPIHandle->pTxBuffer =NULL;
	pSPIHandle->TxLen =0;
	pSPIHandle->TxState = SPI_READY;
}
void SPI_CloseRx(SPI_Handle_t *pSPIHandle)
{
	pSPIHandle->pSPIx->CR2 &= ~(1<<6);
	pSPIHandle->pRxBuffer =NULL;
	pSPIHandle->RxLen =0;
	pSPIHandle->RxState = SPI_READY;

}

__weak void SPI_ApplicationEventCallback(SPI_Handle_t *pSPIHandle, uint8_t AppEv)
{
	//weak implementation
}

