/*
 * SPI.c
 *
 *  Created on: Jun 14, 2024
 *      Author: Yusuf
 */
#include "SPI.h"

/*
 * @brief Disables Transmit Interrupt for SPI.
 *
 * @param SPI_Handle = struct that contains the address
 *  of the SPI instance.
 *
 * @retval none
 */
static void SPI_CloseISR_TX(SPI_HandleTypedef_t *SPI_Handle){
	SPI_Handle->Instance->CR2 &= ~(0x1U << SPI_CR2_TXEIE);
	SPI_Handle->pTxDataAddr = NULL;
	SPI_Handle->busStateTx  = SPI_BUS_FREE;
}

/*
 * @brief Disables Receive Interrupt for SPI.
 *
 * @param SPI_Handle = struct that contains the address
 *  of the SPI instance.
 *
 * @retval none
 */
static void SPI_CloseISR_RX(SPI_HandleTypedef_t *SPI_Handle){
	SPI_Handle->Instance->CR2 &= ~(0x1U << SPI_CR2_RXNEIE);
	SPI_Handle->pRxDataAddr = NULL;
	SPI_Handle->busStateRx  = SPI_BUS_FREE;
}

/*
 * @brief Writes data as 16 bits to DR register.
 *
 * @param SPI_Handle = struct that contains the address
 *  of the SPI instance.
 *
 * @retval none
 */
static void SPI_TransmitHelper_16Bits(SPI_HandleTypedef_t *SPI_Handle){
	SPI_Handle->Instance->DR = *((uint16_t *)(SPI_Handle->pTxDataAddr));
	SPI_Handle->pTxDataAddr+= sizeof(uint16_t);
	SPI_Handle->txDataSize-=2;

	if (SPI_Handle->txDataSize == 0){
			SPI_CloseISR_TX(SPI_Handle);
	}
}

/*
 * @brief Writes data as 8 bits to DR register.
 *
 * @param SPI_Handle = struct that contains the address
 *  of the SPI instance.
 *
 * @retval none
 */
static void SPI_TransmitHelper_8Bits(SPI_HandleTypedef_t *SPI_Handle){
	SPI_Handle->Instance->DR = *(SPI_Handle->pTxDataAddr);
	// try to read from DR
	SPI_Handle->pTxDataAddr+= sizeof(uint8_t);
	SPI_Handle->txDataSize--;

	if (SPI_Handle->txDataSize == 0){
		SPI_CloseISR_TX(SPI_Handle);
	}
}

/*
 * @brief Reads data as 16 bits from DR register.
 *
 * @param SPI_Handle = struct that contains the address
 *  of the SPI instance.
 *
 * @retval none
 */
static void SPI_ReceiveHelper_16Bits(SPI_HandleTypedef_t *SPI_Handle){
	*(uint16_t *)SPI_Handle->pTxDataAddr =*( (__IO uint16_t *)(&SPI_Handle->Instance->DR));
	SPI_Handle->pRxDataAddr+= sizeof(uint16_t);
	SPI_Handle->rxDataSize-=2;

	if (SPI_Handle->rxDataSize == 0){
		SPI_CloseISR_RX(SPI_Handle);
	}
}

/*
 * @brief Reads data as 8 bits from DR register.
 *
 * @param SPI_Handle = struct that contains the address
 *  of the SPI instance.
 *
 * @retval none
 */
static void SPI_ReceiveHelper_8Bits(SPI_HandleTypedef_t *SPI_Handle){
	*(SPI_Handle->pTxDataAddr)= *( (__IO uint8_t *)(&SPI_Handle->Instance->DR));
	SPI_Handle->pRxDataAddr+= sizeof(uint8_t);
	SPI_Handle->rxDataSize--;

	if (SPI_Handle->rxDataSize == 0){
		SPI_CloseISR_RX(SPI_Handle);
	}
}


/*
 * @brief Initializes the SPI Port[1-3].
 *
 * @param SPI_Handle = struct that contains the configuration and
 * address of the SPI instance to apply the configuration to.
 *
 * @retval none
 */
void SPI_Init(SPI_HandleTypedef_t *SPI_Handle){
	uint32_t tempValue = 0;

	tempValue = SPI_Handle->Instance->CR1;

	tempValue |= (SPI_Handle->Init.BaudRate) | (SPI_Handle->Init.CPHA) | (SPI_Handle->Init.Mode) |
			(SPI_Handle->Init.CPOL) | (SPI_Handle->Init.DFF) | (SPI_Handle->Init.FrameFormat) |
			(SPI_Handle->Init.BusConfig) | (SPI_Handle->Init.SSM_Cmd);

	SPI_Handle->Instance->CR1 = tempValue;
}


/*
 * @brief Changes the state of the SPI.
 *
 * @param SPI_Handle = struct that contains the address
 *  of the SPI instance.
 *
 *  @param Cmd = State to apply to the SPI (enable | disable).
 *
 * @retval none
 */
void SPI_Peripheral_Cmd(SPI_HandleTypedef_t *SPI_Handle, FUNCTIONALState_t Cmd){
	if (Cmd == ENABLE){
		SPI_Handle->Instance->CR1 |= (0x1U << SPI_CR1_SPE);
	}else{
		SPI_Handle->Instance->CR1 &= ~(0x1U << SPI_CR1_SPE);

	}
}

/*
 * @brief Transmits the data over the SPI port.
 *
 * @param SPI_Handle = Struct that contains the address
 *  of the configured SPI instance.
 *
 * @param *pData = Pointer to the data to be transmitted.
 *
 * @param sizeOfData = Size of the data in bytes.
 *
 * @retval none
 */
void SPI_TransmitData(SPI_HandleTypedef_t *SPI_Handle, uint8_t *pData, uint16_t sizeOfData){

	if (SPI_Handle->Init.DFF == SPI_DFF_16_BITS){
		while (sizeOfData > 0){
			if (SPI_GetFlagStatus(SPI_Handle, SPI_FLAG_TXE)){		// Check TXE (transmit buffer empty) bit
				SPI_Handle->Instance->DR = *((uint16_t*)pData);
				pData+=sizeof(uint16_t);
				sizeOfData-=2;
			}

		}
	}else{
		while (sizeOfData > 0){
			if (SPI_GetFlagStatus(SPI_Handle, SPI_FLAG_TXE)){		// Check TXE (transmit buffer empty) bit
				SPI_Handle->Instance->DR = *pData;				// transmit the data
				pData+=sizeof(uint8_t);
				sizeOfData--;
			}
		}
	}

	while(SPI_GetFlagStatus(SPI_Handle,SPI_FLAG_BUSY));				// Check BSY flag, block untill it is no longer busy
}

/*
 * @brief Receives the data over the SPI port.
 *
 * @param SPI_Handle = Struct that contains the address
 *  of the configured SPI instance.
 *
 * @param *pData = Pointer to the buffer that the data will be stored.
 *
 * @param sizeOfData = Size of the data in bytes.
 *
 * @retval none
 */
void SPI_ReceiveData(SPI_HandleTypedef_t *SPI_Handle, uint8_t *pBuffer, uint16_t sizeOfData){
	if (SPI_Handle->Init.DFF == SPI_DFF_16_BITS){
		while(sizeOfData > 0){
			 if(SPI_GetFlagStatus(SPI_Handle, SPI_FLAG_RXNE)){
				 *((uint16_t *)pBuffer) = (uint16_t)SPI_Handle->Instance->DR;
				 pBuffer+= sizeof(uint16_t);
				 sizeOfData-=2;
			 }
		}
	}else{
		while(sizeOfData > 0){
			 if(SPI_GetFlagStatus(SPI_Handle, SPI_FLAG_RXNE)){
				*pBuffer = *((__IO uint8_t*)&SPI_Handle->Instance->DR);
				pBuffer+= sizeof(uint8_t);
				sizeOfData--;
			}
		}
	}

	while(SPI_GetFlagStatus(SPI_Handle,SPI_FLAG_BUSY));
}

/*
 * @brief Does the configuration for data transmit with interrupt over the SPI port.
 *
 * @param SPI_Handle = Struct that contains the address
 *  of the configured SPI instance.
 *
 * @param *pData = Pointer to the data to be transmitted.
 *
 * @param sizeOfData = Size of the data in bytes.
 *
 * @retval none
 */
void SPI_TransmitDataINT(SPI_HandleTypedef_t *SPI_Handle, uint8_t *pData, uint16_t sizeOfData){
	SPI_BUSStatus_t busState = SPI_Handle->busStateTx;

	if (busState != SPI_BUS_TX_BUSY){
		SPI_Handle->busStateTx = SPI_BUS_TX_BUSY;
		SPI_Handle->pTxDataAddr = pData;
		SPI_Handle->txDataSize = sizeOfData;

		if (SPI_Handle->Instance->CR1 & (0x1U << SPI_CR1_DFF)){
			// handle 16 bit data
			SPI_Handle->TxISRFunction = SPI_TransmitHelper_16Bits;
		}else{
			SPI_Handle->TxISRFunction = SPI_TransmitHelper_8Bits;
		}

		SPI_Handle->Instance->CR2 |= (0x1U << SPI_CR2_TXEIE);		// Enable interupt
	}
}

/*
 * @brief Does the configuration for data receive with interrupt over the SPI port.
 *
 * @param SPI_Handle = Struct that contains the address
 *  of the configured SPI instance.
 *
 * @param *pData = Pointer to the data to be stored.
 *
 * @param sizeOfData = Size of the data in bytes.
 *
 * @retval none
 */
void SPI_ReceiveDataINT(SPI_HandleTypedef_t *SPI_Handle, uint8_t *pBuffer, uint16_t sizeOfData){
	SPI_BUSStatus_t busState = SPI_Handle->busStateRx;

		if (busState != SPI_BUS_TX_BUSY){
			SPI_Handle->busStateRx = SPI_BUS_RX_BUSY;
			SPI_Handle->pRxDataAddr = pBuffer;
			SPI_Handle->rxDataSize = sizeOfData;

			if (SPI_Handle->Instance->CR1 & (0x1U << SPI_CR1_DFF)){
				// handle 16 bit data
				SPI_Handle->RxISRFunction = SPI_ReceiveHelper_16Bits;
			}else{
				SPI_Handle->RxISRFunction = SPI_ReceiveHelper_8Bits;
			}

			SPI_Handle->Instance->CR2 |= (0x1U << SPI_CR2_RXNEIE);		// Enable interupt

		}
}

void SPI_InterruptHandler(SPI_HandleTypedef_t *SPI_Handle){
	uint8_t interruptSource = 0;
	uint8_t interruptFlag = 0;

	interruptSource = SPI_Handle->Instance->CR2 & (0x1U << SPI_CR2_TXEIE);
	interruptFlag = SPI_Handle->Instance->SR & (0x1U << SPI_SR_TXE);

	if ((interruptSource !=0) && (interruptFlag != 0)){
		// Transmit Interrupt enabled and triggered
		SPI_Handle->TxISRFunction(SPI_Handle);
	}

	interruptSource = SPI_Handle->Instance->CR2 & (0x1U << SPI_CR2_RXNEIE);
	interruptFlag = SPI_Handle->Instance->SR & (0x1U << SPI_SR_RXNE);

	if ((interruptSource !=0) && (interruptFlag != 0)){
		// Receive Interrupt enabled and triggered
		SPI_Handle->RxISRFunction(SPI_Handle);
	}
}

/*
 * @brief Returns the status of given flag on SPI.
 *
 * @param SPI_Handle = Struct that contains the address
 *  of the configured SPI instance.
 *
 * @param SPI_Flag = Flag value on SR @def_group SPI_SR_FlagValues.
 *
 * @retval Status of the flag.
 */
SPI_FlagStatus_t SPI_GetFlagStatus(SPI_HandleTypedef_t *SPI_Handle, uint16_t SPI_Flag){
	return (SPI_FlagStatus_t)(SPI_Handle->Instance->SR & SPI_Flag);
}













