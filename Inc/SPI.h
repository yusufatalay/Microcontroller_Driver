/*
 * SPI.h
 *
 *  Created on: Jun 14, 2024
 *      Author: Yusuf
 */

#ifndef INC_SPI_H_
#define INC_SPI_H_

#include "stm32f407xx.h"

typedef enum{
	SPI_BUS_FREE = 0x0U,
	SPI_BUS_TX_BUSY = 0x1U,
	SPI_BUS_RX_BUSY = 0x2U
}SPI_BUSStatus_t;

/*
 * @def_group SPI_BaudRates
 */
#define SPI_BAUDRATE_DIV_2					((uint32_t)(0x00000000))
#define SPI_BAUDRATE_DIV_4					((uint32_t)(0x00000008))
#define SPI_BAUDRATE_DIV_8					((uint32_t)(0x00000010))
#define SPI_BAUDRATE_DIV_16					((uint32_t)(0x00000018))
#define SPI_BAUDRATE_DIV_32					((uint32_t)(0x00000020))
#define SPI_BAUDRATE_DIV_64					((uint32_t)(0x00000028))
#define SPI_BAUDRATE_DIV_128				((uint32_t)(0x00000030))
#define SPI_BAUDRATE_DIV_256				((uint32_t)(0x00000038))

/*
 * @def_group SPI_ModeValues
 */
#define SPI_MODE_SLAVE						((uint32_t)(0x00000000))
#define SPI_MODE_MASTER						((uint32_t)(0x00000004))

/*
 * @def_group SPI_CPHAValues
 */
#define SPI_CPHA_FIRST						((uint32_t)(0x00000000))
#define SPI_CPHA_SECOND						((uint32_t)(0x00000001))

/*
 * @def_group SPI_CPOLValues
 */
#define SPI_CPOL_IDLE_LOW					((uint32_t)(0x00000000))
#define SPI_CPOL_IDLE_HIGH					((uint32_t)(0x00000002))

/*
 * @def_group SPI_DFFValues
 */
#define SPI_DFF_8_BITS						((uint32_t)(0x00000000))
#define SPI_DFF_16_BITS						((uint32_t)(0x00000800))

/*
 * @def_group SPI_FFValues
 */
#define SPI_FF_LSB							((uint32_t)(0x00000000))
#define SPI_FF_MSB 							((uint32_t)(0x00000080))

/*
 * @def_group SPI_BusConfigValues
 */
#define SPI_BUS_FULL_DUPLEX					((uint32_t)(0x00000000))
#define SPI_BUS_RECEIVE_ONLY				((uint32_t)(0x00000400))
#define SPI_BUS_HALF_DUPLEX_TRANSMIT		((uint32_t)(0x0000C000))
#define SPI_BUS_HALF_DUPLEX_RECEIVE			((uint32_t)(0x00008000))

/*
 * @def_group SPI_SSMValues
 */
#define SPI_SSM_DISABLE						((uint32_t)(0x00000000))
#define SPI_SSM_ENABLE						((uint32_t)(0x00000300))


/*
 * @def_group SPI_SR_FlagValues
 */
#define SPI_FLAG_RXNE						(0x1U << SPI_SR_RXNE)
#define SPI_FLAG_TXE						(0x1U << SPI_SR_TXE)
#define SPI_FLAG_BUSY						(0x1U << SPI_SR_BSY)

typedef enum{
	SPI_FLAG_RESET = 0x0U,
	SPI_FLAG_SET = !SPI_FLAG_RESET
}SPI_FlagStatus_t;

typedef struct{
	uint32_t Mode;							/*!< Mode (Master or Slave) for SPI @def_group SPI_ModeValues 				*/
	uint32_t CPHA;							/*!< CPHA values for SPI @def_group SPI_CPHAValues 							*/
	uint32_t CPOL;							/*!< CPOL values for SPI @def_group SPI_CPOLValues 							*/
	uint32_t BaudRate;						/*!< Baud rate values for SPI @def_group SPI_BaudRates 						*/
	uint32_t SSM_Cmd;						/*!< SSM values for SPI @def_group SPI_SSMValues	 						*/
	uint32_t DFF;							/*!< DFF values for SPI @def_group SPI_DFFValues 							*/
	uint32_t BusConfig;						/*!< BusConfig (duplexity) values for SPI @def_group SPI_BusConfigValues 	*/
	uint32_t FrameFormat;					/*!< LSBFIRST values for SPI @def_group SPI_FFValues 						*/
}SPI_InitTypedef_t;



typedef struct SPI_HandleTypedef_t
{
	SPI_Typedef_t *Instance;
	SPI_InitTypedef_t Init;
	uint8_t *pTxDataAddr;
	uint8_t *pRxDataAddr;
	uint16_t rxDataSize;
	uint16_t txDataSize;
	uint8_t busStateTx;
	uint8_t busStateRx;
	void(*TxISRFunction)(struct SPI_HandleTypedef_t *SPI_Handle);
	void(*RxISRFunction)(struct SPI_HandleTypedef_t *SPI_Handle);
}SPI_HandleTypedef_t;


void SPI_Init(SPI_HandleTypedef_t *SPI_Handle);
void SPI_Peripheral_Cmd(SPI_HandleTypedef_t *SPI_Handle, FunctionalState_t Cmd);
void SPI_TransmitData(SPI_HandleTypedef_t *SPI_Handle, uint8_t *pData, uint16_t sizeOfData);
void SPI_ReceiveData(SPI_HandleTypedef_t *SPI_Handle, uint8_t *pBuffer, uint16_t sizeOfData);
void SPI_TransmitDataINT(SPI_HandleTypedef_t *SPI_Handle, uint8_t *pData, uint16_t sizeOfData);
void SPI_ReceiveDataINT(SPI_HandleTypedef_t *SPI_Handle, uint8_t *pBuffer, uint16_t sizeOfData);
void SPI_InterruptHandler(SPI_HandleTypedef_t *SPI_Handle);
SPI_FlagStatus_t SPI_GetFlagStatus(SPI_HandleTypedef_t *SPI_Handle, uint16_t SPI_Flag);



#endif /* INC_SPI_H_ */

