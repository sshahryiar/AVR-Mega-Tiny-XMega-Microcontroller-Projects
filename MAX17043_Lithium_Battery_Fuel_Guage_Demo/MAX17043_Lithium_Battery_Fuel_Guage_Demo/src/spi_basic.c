/**
 * \file
 *
 * \brief SPI basic driver.
 *
 (c) 2020 Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms,you may use this software and
    any derivatives exclusively with Microchip products.It is your responsibility
    to comply with third party license terms applicable to your use of third party
    software (including open source software) that may accompany Microchip software.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 */

/**
 * \defgroup doc_driver_spi_basic SPI Basic
 * \ingroup doc_driver_spi
 *
 * \section doc_driver_spi_basic_rev Revision History
 * - v0.0.0.1 Initial Commit
 *
 *@{
 */
#include <spi_basic.h>
#include <atmel_start_pins.h>

typedef struct {
	uint8_t SPCRvalue;
} SPI_configuration_t;

typedef struct SPI_descriptor_s {
	spi_transfer_status_t status;
} SPI_descriptor_t;

SPI_configuration_t SPI_configurations[] = {
    {

        .SPCRvalue = 1 << SPE                    /* SPI module enable: enabled */
                     | 0 << DORD                 /* Data order: disabled */
                     | 1 << MSTR                 /* Master/Slave select: enabled */
                     | 0 << CPOL                 /* Clock polarity: disabled */
                     | 0 << CPHA                 /* Clock phase: disabled */
                     | 0 << SPIE                 /* SPI interrupt enable: disabled */
                     | (0 << SPR1) | (0 << SPR0) /* SPI Clock rate selection: fosc/16 */
                     | (0 << SPR1) | (1 << SPR0) /*  */

        ,
    },
};

static SPI_descriptor_t SPI_desc;

/**
 * \brief Initialize SPI interface
 * If module is configured to disabled state, the clock to the SPI is disabled
 * if this is supported by the device's clock system.
 *
 * \return Initialization status.
 * \retval 0 the SPI init was successful
 * \retval 1 the SPI init was not successful
 */
void SPI_init()
{

	/* Enable SPI */
	PRR &= ~(1 << PRSPI);

	SPCR = 1 << SPE                     /* SPI module enable: enabled */
	       | 0 << DORD                  /* Data order: disabled */
	       | 1 << MSTR                  /* Master/Slave select: enabled */
	       | 0 << CPOL                  /* Clock polarity: disabled */
	       | 0 << CPHA                  /* Clock phase: disabled */
	       | 0 << SPIE                  /* SPI interrupt enable: disabled */
	       | (0 << SPR1) | (0 << SPR0)  /* SPI Clock rate selection: fosc/16 */
	       | (0 << SPR1) | (1 << SPR0); /*  */

	// SPSR = (0 << SPI2X); /* Disable double SPI speed */

	SPI_desc.status = SPI_FREE;
}

/**
 * \brief Enable SPI
 * 1. If supported by the clock system, enables the clock to the SPI
 * 2. Enables the SPI module by setting the enable-bit in the SPI control register
 *
 * \return Nothing
 */
void SPI_enable()
{
	SPCR |= (1 << SPE);
}

/**
 * \brief Disable SPI
 * 1. Disables the SPI module by clearing the enable-bit in the SPI control register
 * 2. If supported by the clock system, disables the clock to the SPI
 *
 * \return Nothing
 */
void SPI_disable()
{
	SPCR &= ~(1 << SPE);
}

/**
 * \brief Open the SPI SPI for communication
 *
 * \param[in] configuration The configuration to use in the transfer
 *
 * \return Initialization status.
 * \retval false The SPI open was successful
 * \retval true  The SPI open was successful
 */
bool SPI_open(SPI_configuration_name configuration)
{
	if (SPI_desc.status == SPI_FREE) {
		SPI_desc.status = SPI_IDLE;
		SPCR            = SPI_configurations[configuration].SPCRvalue;
		return true;
	} else {
		return false;
	}
}

/**
 * \brief Close the SPI SPI for communication
 *
 * \return Nothing
 */
void SPI_close(void)
{
	SPI_desc.status = SPI_FREE;
}

/**
 * \brief Exchange one byte over SPI SPI. Blocks until done.
 *
 * \param[in] data The byte to transfer
 *
 * \return Received data byte.
 */
uint8_t SPI_exchange_byte(uint8_t data)
{
	// Blocking wait for SPI free makes the function work
	// seamlessly also with IRQ drivers.
	while (SPI_desc.status == SPI_BUSY)
		;
	SPDR = data;
	while (!(SPSR & (1 << SPIF)))
		;
	return SPDR;
}

/**
 * \brief Exchange a buffer over SPI SPI. Blocks if using polled driver.
 *
 * \param[inout] block The buffer to transfer. Received data is returned here.
 * \param[in] size The size of buffer to transfer
 *
 * \return Nothing.
 */
void SPI_exchange_block(void *block, uint8_t size)
{
	uint8_t *b = (uint8_t *)block;
	while (size--) {
		SPDR = *b;
		while (!(SPSR & (1 << SPIF)))
			;
		*b = SPDR;
		b++;
	}
}

/**
 * \brief Write a buffer over SPI SPI. Blocks if using polled driver.
 *
 * \param[in] block The buffer to transfer
 * \param[in] size The size of buffer to transfer
 *
 * \return Nothing.
 */
void SPI_write_block(void *block, uint8_t size)
{
	uint8_t *b = (uint8_t *)block;
	while (size--) {
		SPDR = *b;
		while (!(SPSR & (1 << SPIF)))
			;
		b++;
	}
}

/**
 * \brief Read a buffer over SPI SPI. Blocks if using polled driver.
 *
 * Zeros are transmitted out of the SPI.
 *
 * \param[out] block Received data is written here.
 * \param[in] size The size of buffer to transfer
 *
 * \return Nothing.
 */
void SPI_read_block(void *block, uint8_t size)
{
	uint8_t *b = (uint8_t *)block;
	while (size--) {
		SPDR = 0;
		while (!(SPSR & (1 << SPIF)))
			;
		*b = SPDR;
		b++;
	}
}
