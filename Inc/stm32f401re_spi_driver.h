/*
 * stm32f401xx_SPI_driver.h
 *
 *  Created on: 15-Apr-2026
 *      Author: TGT
 */
#ifndef INC_STM32F401XX_SPI_DRIVER_H_
#define INC_STM32F401XX_SPI_DRIVER_H_


#include "stm32f401xx.h"
#include "stdint.h"





// CONFIGURATION STRUCTURE FOR SPIX PERIPHERAL
typedef struct
{
	uint8_t SPI_DeviceMode;
	uint8_t SPI_BusConfig;
	uint8_t SPI_SclkSpeed;
	uint8_t SPI_DFF;
	uint8_t SPI_CPOL;
	uint8_t SPI_CPHA;
	uint8_t SPI_SSM;
} SPI_Config_t;


// HANDLE STRUCTURE FOR SPIx PERIPHERAL

typedef struct
{
	SPI_Reg_Def_t	*pSPIx;
	SPI_Config_t	SPIConfig;
	uint8_t 		*pTxBuffer; //to store app tx buffer address
	uint8_t			*pRxBuffer; //to store app rx bufffer address
	uint32_t 		TxLen;		//to store tx len
	uint32_t		RxLen;		//to store rx ken
	uint8_t			TxState;	//to store Tx state
	uint8_t 		RxState; 	//to store rx state
} SPI_Handle_t;



//POSSIBLE SPI APPLICATION EVENTS
#define		SPI_EVENT_TX_CMPLT		1
#define		SPI_EVENT_RX_CMPLT		2
#define		SPI_EVENT_OVR_ERR		3
#define		SPI_EVENT_CRC_ERR		4





//SPI application states

#define SPI_READY 		0
#define SPI_BUSY_IN_RX 	1
#define SPI_BUSY_IN_TX	2




//@SPI_DeviceMode
//SPI MODES MACROS

#define SPI_DEVICE_MODE_MASTER	1
#define SPI_DEVICE_MODE_SLAVE	0


//@SPI_BusConfig
//SPI BUS MODE MACROS
#define SPI_BUS_CONFIG_FD					1
#define SPI_BUS_CONFIG_HD					2
#define SPI_BUS_CONFIG_SIMPLEX_TXONLY 		3
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY 		4


//@SPI_SclkSpeed
//BAUD RATE
#define SPI_SCLK_SPEED_DIV2					0
#define SPI_SCLK_SPEED_DIV4 				1
#define SPI_SCLK_SPEED_DIV8					2
#define SPI_SCLK_SPEED_DIV16				3
#define SPI_SCLK_SPEED_DIV32				4
#define SPI_SCLK_SPEED_DIV64				5
#define SPI_SCLK_SPEED_DIV128				6
#define SPI_SCLK_SPEED_DIV256				7

//@SPI_DFF
#define SPI_DFF_8BITS  0
#define SPI_DFF_16BITS 1


//@SPI_CPOL
#define SPI_CPOL_HIGH	1
#define SPI_CPOL_LOW	0

//SPI_CPHA
#define SPI_CPHA_HIGH	1
#define SPI_CPHA_LOW	0

//SPI_SSM
#define SPI_SSM_HW		0
#define SPI_SSM_SW		1


/* PERIPHERAL CLOCK SETUP*/

void SPI_PeriClockControl(SPI_Reg_Def_t *pSPIx,uint8_t EnorDi);

/*INIT AND DE-INIT*/

void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_Reg_Def_t *pSPIx);

//data send and receive
void SPI_SendData(SPI_Reg_Def_t *pSPIx,uint8_t *pTxBuffer, uint32_t Len);
void SPI_ReceiveData(SPI_Reg_Def_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len);

//data send and receive WITH INTERRUPT
uint8_t SPI_SendDataIT(SPI_Handle_t*pSPIHandle,uint8_t *pTxBuffer, uint32_t Len);
uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer, uint32_t Len);


//SPI IRQ CONFIG
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber,uint32_t Priority );
void SPI_IRQHandling(SPI_Handle_t *pSPIHandle);


// other apis

void SPI_PeripheralControl(SPI_Reg_Def_t *pSPIx, uint8_t ENorDI);
void SPI_SSIConfig(SPI_Reg_Def_t *pSPIx, uint8_t ENorDI);
void SPI_ClearOVRFlag(SPI_Reg_Def_t *pSPIx);
void SPI_CloseTx(SPI_Handle_t *pSPIHandle);
void SPI_CloseRx(SPI_Handle_t *pSPIHandle);

void SPI_ApplicationEventCallback(SPI_Handle_t *SPI_Handle_t, uint8_t AppEv);




#endif /* INC_STM3F407XX_H_ */
