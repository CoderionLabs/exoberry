/*
 * @brief SPI bus master example using the ROM API in polling mode
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2014
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include "board.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/* SPI master handle and memory for ROM API */
static SPI_HANDLE_T *spiHandleMaster;

/* Use a buffer size larger than the expected return value of
   spi_get_mem_size() for the static SPI handle type */
static uint32_t spiMasterHandleMEM[0x20];

static uint16_t xferArray[] = {0x1111, 0x2222, 0x3333, 0x4444};
static uint16_t rx_buff[sizeof(xferArray) / sizeof(uint16_t)];

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/* Initializes pin muxing for SPI interface - note that SystemInit() may
   already setup your pin muxing at system startup */
static void Init_SPI_PinMux(void)
{
#if (defined(BOARD_NXP_LPCXPRESSO_1549))

	/* Enable the clock to the Switch Matrix */
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_SWM);
	/*
	 * Initialize SPI0 pins connect
	 * SCK0: PINASSIGN3[15:8]: Select P0.0
	 * MOSI0: PINASSIGN3[23:16]: Select P0.16
	 * MISO0: PINASSIGN3[31:24] : Select P0.10
	 * SSEL0: PINASSIGN4[7:0]: Select P0.9
	 */
	Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 0, (IOCON_MODE_INACT | IOCON_DIGMODE_EN));
	Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 16, (IOCON_MODE_INACT | IOCON_DIGMODE_EN));
	Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 10, (IOCON_MODE_INACT | IOCON_DIGMODE_EN));
	Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 9, (IOCON_MODE_INACT | IOCON_DIGMODE_EN));

	Chip_SWM_MovablePinAssign(SWM_SPI0_SCK_IO, 0);	/* P0.0 */
	Chip_SWM_MovablePinAssign(SWM_SPI0_MOSI_IO, 16);/* P0.16 */
	Chip_SWM_MovablePinAssign(SWM_SPI0_MISO_IO, 10);/* P0.10 */
	Chip_SWM_MovablePinAssign(SWM_SPI0_SSELSN_0_IO, 9);	/* P0.9 */

	/* Disable the clock to the Switch Matrix to save power */
	Chip_Clock_DisablePeriphClock(SYSCTL_CLOCK_SWM);
#else
	/* Configure your own SPI pin muxing here if needed */
#warning "No SPI pin muxing defined"
#endif
}

/* Turn on LED to indicate an error */
static void errorSPI(void)
{
	Board_LED_Set(0, true);
	while (1) {}
}

/* Setup SPI handle and parameters */
static void setupSpiMaster()
{
	SPI_CONFIG_T spiConfigRec;

	/* Enable SPI clock and reset SPI peripheral - the boot ROM does not
	   do this */
	Chip_SPI_Init(LPC_SPI0);

	/* Perform a sanity check on the storage allocation */
	if (LPC_SPID_API->spi_get_mem_size() > sizeof(spiMasterHandleMEM)) {
		/* Example only: this should never happen and probably isn't needed for
		   most SPI code. */
		errorSPI();
	}

	/* Setup the SPI0 handle */
	spiHandleMaster = LPC_SPID_API->spi_setup(LPC_SPI0_BASE, (uint8_t *) &spiMasterHandleMEM);
	if (spiHandleMaster == NULL) {
		errorSPI();
	}
	/* Setup SPI0 configuration record */
	spiConfigRec.delay = 0x2222;
	/* SysClock divider is set to maximum */
	spiConfigRec.divider = 0xFFFF;
	/* Loopback mode, master mode and SPI block enabled */
	spiConfigRec.config = 0x85;
	spiConfigRec.error_en = 0;

	/* Init SPI0 */
	LPC_SPID_API->spi_init(spiHandleMaster, &spiConfigRec);
}

/* Master SPI transmit in polling mode */
static void WriteSpiMssg(uint16_t *xferPtr, uint32_t xferSize)
{
	SPI_PARAM_T paramRec;
	uint8_t i;

	/* Setup transfer record */
	paramRec.tx_buffer = xferPtr;	/* SPI TX buffer */
	paramRec.size = xferSize;		/* total number of SPI transfers */
	paramRec.rx_buffer = rx_buff;	/* SPI RX buffer */
	paramRec.fsize_sel = 0x0F0E0000;/* Set Tx Control for 16 bit transfer, SSEL0 asserted */
	paramRec.eof_flag = 1;	/* End of Frame enabled */
	paramRec.tx_rx_flag = 2;		/* transmit and receive */
	paramRec.driver_mode = 0;		/* polling mode */
	paramRec.dma_cfg = NULL;		/* DMA configuration */
	paramRec.cb = NULL;					/* SPI completion callback */
	paramRec.dma_cb = NULL;			/* DMA completion callback */

	/* Transfer message as SPI master via polling */
	if (LPC_SPID_API->spi_master_transfer(spiHandleMaster, &paramRec) == LPC_OK) {
		/* If transmit successful then verify received data */
		for (i = 0; i < sizeof(xferArray) / sizeof(uint16_t); i++) {
			if (rx_buff[i] != xferArray[i]) {
				errorSPI();
			}
		}
	}
	else {
		/* Signal SPI error */
		errorSPI();
	}
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/**
 * @brief	Main routine for SPI example
 * @return	Function should not exit
 */
int main(void)
{
	/* Generic Initialization */
	SystemCoreClockUpdate();
	Board_Init();

	/* Clear activity LED */
	Board_LED_Set(0, false);

	/* Setup SPI pin muxing */
	Init_SPI_PinMux();

	/* Allocate SPI handle, setup rate, and initialize clocking */
	setupSpiMaster();

	/* Loop forever */
	while (1) {
		/* Write simple message over SPI */
		WriteSpiMssg(xferArray, sizeof(xferArray) / sizeof(uint16_t));

		/* Toggle LED to show activity. */
		Board_LED_Toggle(0);
	}

	/* Code never reaches here. Only used to satisfy standard main() */
	return 0;
}
