

#include "stm32f446xx.h"
/*
 * Config SPI
 */
typedef struct
{
	uint8_t SPI_DeviceoMode;
	uint8_t SPI_BusConfig;
	uint8_t SPI_SclkSpeed;
	uint8_t SPI_DFF;
	uint8_t SPI_CPOL;
	uint8_t SPI_CPHA;
	uint8_t SPI_SSA;
}SPI_Config_t;

/*
 * SPI Handle Structure
 *
 * Contains peripheral pointer + configuration + state information
 */
typedef struct
{
    SPI_RegDef_t    *pSPIx;         /*!< Base address of SPIx peripheral */
    SPI_Config_t    SPIConfig;      /*!< SPI configuration settings */
    uint8_t         *pTxBuffer;     /*!< Pointer to TX buffer (for interrupt mode) */
    uint8_t         *pRxBuffer;     /*!< Pointer to RX buffer (for interrupt mode) */
    uint32_t        TxLen;          /*!< TX length */
    uint32_t        RxLen;          /*!< RX length */
    uint8_t         TxState;        /*!< TX state */
    uint8_t         RxState;        /*!< RX state */
} SPI_Handle_t;

/*
 * @SPI_DeviceMode - Master or Slave
 */
#define SPI_DEVICE_MODE_SLAVE       0
#define SPI_DEVICE_MODE_MASTER      1

/*
 * @SPI_BusConfig - Bus configuration options
 */
#define SPI_BUS_CONFIG_FD               1   // Full Duplex
#define SPI_BUS_CONFIG_HD               2   // Half Duplex
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY   3   // Simplex RX Only

/*
 * @SPI_SclkSpeed - Clock speed (prescaler values)
 */
#define SPI_SCLK_SPEED_DIV2         0   // fPCLK / 2
#define SPI_SCLK_SPEED_DIV4         1   // fPCLK / 4
#define SPI_SCLK_SPEED_DIV8         2   // fPCLK / 8
#define SPI_SCLK_SPEED_DIV16        3   // fPCLK / 16
#define SPI_SCLK_SPEED_DIV32        4   // fPCLK / 32
#define SPI_SCLK_SPEED_DIV64        5   // fPCLK / 64
#define SPI_SCLK_SPEED_DIV128       6   // fPCLK / 128
#define SPI_SCLK_SPEED_DIV256       7   // fPCLK / 256


/*
 * Configuration Macros
 */
/*
 * @SPI_DFF - Data frame format
 */
#define SPI_DFF_8BITS       0
#define SPI_DFF_16BITS      1

/*
 * @SPI_CPOL - Clock polarity
 */
#define SPI_CPOL_LOW        0   // Clock idles LOW
#define SPI_CPOL_HIGH       1   // Clock idles HIGH

/*
 * @SPI_CPHA - Clock phase
 */
#define SPI_CPHA_LOW        0   // Sample on first edge
#define SPI_CPHA_HIGH       1   // Sample on second edge

/*
 * @SPI_SSM - Software slave management
 */
#define SPI_SSM_DI          0   // Hardware slave management
#define SPI_SSM_EN          1   // Software slave management

/*
 * SPI application states (for interrupt mode)
 */
#define SPI_READY           0
#define SPI_BUSY_IN_RX      1
#define SPI_BUSY_IN_TX      2

/*
 * SPI Status flags
 */
#define SPI_TXE_FLAG        (1 << SPI_SR_TXE)
#define SPI_RXNE_FLAG       (1 << SPI_SR_RXNE)
#define SPI_BUSY_FLAG       (1 << SPI_SR_BSY)


/*
 * Peripheral Clock Setup
 */
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);

/*
 * Init and De-Init
 */
void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_RegDef_t *pSPIx);

/*
 * Data Send and Receive (Blocking/Polling)
 */
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len);
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len);

/*
 * Data Send and Receive (Interrupt-based)
 */
uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t Len);
uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer, uint32_t Len);



