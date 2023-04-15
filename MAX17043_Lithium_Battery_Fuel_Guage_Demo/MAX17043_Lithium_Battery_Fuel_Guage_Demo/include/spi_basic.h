/**
 * \file spi_basic.h
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

#ifndef SPI_BASIC_H_INCLUDED
#define SPI_BASIC_H_INCLUDED

#include <compiler.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Function pointer to callback function called by SPI IRQ.
    NULL=default value: No callback function is to be used.
*/
typedef void (*spi_transfer_done_cb_t)(void);

/** Specify whether the SPI transfer is to be uni- or bidirectional.
    A bidirectional transfer (=SPI_EXCHANGE) causes the received data
    to overwrite the buffer with the data to transmit.
*/
typedef enum spi_transfer_type {
	SPI_EXCHANGE, ///< SPI transfer is bidirectional
	SPI_READ,     ///< SPI transfer reads, writes only 0s
	SPI_WRITE     ///< SPI transfer writes, discards read data
} spi_transfer_type_t;

/** Status of the SPI hardware and SPI bus.*/
typedef enum spi_transfer_status {
	SPI_FREE, ///< SPI hardware is not open, bus is free.
	SPI_IDLE, ///< SPI hardware has been opened, no transfer ongoing.
	SPI_BUSY, ///< SPI hardware has been opened, transfer ongoing.
	SPI_DONE  ///< SPI hardware has been opened, transfer complete.
} spi_transfer_status_t;

/** Enumeration of the different configurations supported by the driver.
    A configuration is specified as parameter to SPI_open(),
    and is used by the function to set SPI parameters as specified by the
    configuration. A user may specify a configuration, e.g. SLAVE_A, used when
    communication over SPI with SLAVE_A, and another configuration, SLAVE_B,
    used when communication with SLAVE_B. The configurations may use different
    SPI configuration such as polarity or SCK frequency.
*/
typedef enum {
	SPI_DEFAULT, ///< Default SPI configuration set up in START
} SPI_configuration_name;

void SPI_init(void);

void SPI_enable();

void SPI_disable();

bool SPI_open(SPI_configuration_name configuration);

void SPI_close(void);

uint8_t SPI_exchange_byte(uint8_t data);

void SPI_exchange_block(void *block, uint8_t size);

void SPI_write_block(void *block, uint8_t size);

void SPI_read_block(void *block, uint8_t size);

#ifdef __cplusplus
}
#endif

#endif /* SPI_BASIC_H_INCLUDED */
