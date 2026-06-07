/*
 * 006SPI_tx_testing.c
 *
 *  Created on: 26-Apr-2026
 *      Author: TGT
 *
 */


//SPI2 ALT FUNC PIN MAPPING
//PB15 -> SPI2_MOSI
//PB14 -> SPI2_MISO
//PB13 -> SPI2_SCLK
//PB12 -> SPI2->NSS
//ALT FUN MODE 5

#include <string.h>
#include "stm32f401xx.h"





void SPI2_GPIOInit(void)
{
	GPIO_Handle_t	SPIPins;
	SPIPins.pGPIOx = GPIOB;
	SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode=5;
	SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	//SLK
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GPIO_Init(&SPIPins);

	//MOSI
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
	GPIO_Init(&SPIPins);






}

void SPI2_Inits(void)
{
	SPI_Handle_t SPI2handle;
	SPI2handle.pSPIx = SPI2;
	SPI2handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI2handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV2; //8mhz
	SPI2handle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
	SPI2handle.SPIConfig.SPI_CPOL = SPI_CPOL_HIGH;
	SPI2handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI2handle.SPIConfig.SPI_SSM = SPI_SSM_SW;

	SPI_Init(&SPI2handle);





}

int main(void)
{
	//func to init gpio alt func for SPI2
	SPI2_GPIOInit();


	SPI2_Inits();

	//makes nss internally high
	SPI_SSIConfig(SPI2,ENABLE);


	char user_data[] = "hello world";

	//enable the peripheral
	SPI_PeripheralControl(SPI2, ENABLE);

	SPI_SendData(SPI2,(uint8_t*)user_data, strlen(user_data));
//SPI_PeripheralControl(SPI2, DISABLE);

	while(1);



	return 0;

}


