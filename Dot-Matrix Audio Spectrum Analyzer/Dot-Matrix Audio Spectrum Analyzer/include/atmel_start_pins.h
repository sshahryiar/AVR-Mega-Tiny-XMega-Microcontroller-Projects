/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */
#ifndef ATMEL_START_PINS_H_INCLUDED
#define ATMEL_START_PINS_H_INCLUDED

#include <port.h>

/**
 * \brief Set TM1640_DIN pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull
 * modes are defined by device used
 *
 * \param[in] pull_mode Pin pull mode
 */
static inline void TM1640_DIN_set_pull_mode(const enum port_pull_mode pull_mode)
{
	PORTB_set_pin_pull_mode(0, pull_mode);
}

/**
 * \brief Set TM1640_DIN data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] direction PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void TM1640_DIN_set_dir(const enum port_dir dir)
{
	PORTB_set_pin_dir(0, dir);
}

/**
 * \brief Set TM1640_DIN level
 *
 * Sets output level on a pin
 *
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void TM1640_DIN_set_level(const bool level)
{
	PORTB_set_pin_level(0, level);
}

/**
 * \brief Toggle output level on TM1640_DIN
 *
 * Toggle the pin level
 */
static inline void TM1640_DIN_toggle_level()
{
	PORTB_toggle_pin_level(0);
}

/**
 * \brief Get level on TM1640_DIN
 *
 * Reads the level on a pin
 */
static inline bool TM1640_DIN_get_level()
{
	return PORTB_get_pin_level(0);
}

/**
 * \brief Set TM1640_CLK pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull
 * modes are defined by device used
 *
 * \param[in] pull_mode Pin pull mode
 */
static inline void TM1640_CLK_set_pull_mode(const enum port_pull_mode pull_mode)
{
	PORTB_set_pin_pull_mode(1, pull_mode);
}

/**
 * \brief Set TM1640_CLK data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] direction PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void TM1640_CLK_set_dir(const enum port_dir dir)
{
	PORTB_set_pin_dir(1, dir);
}

/**
 * \brief Set TM1640_CLK level
 *
 * Sets output level on a pin
 *
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void TM1640_CLK_set_level(const bool level)
{
	PORTB_set_pin_level(1, level);
}

/**
 * \brief Toggle output level on TM1640_CLK
 *
 * Toggle the pin level
 */
static inline void TM1640_CLK_toggle_level()
{
	PORTB_toggle_pin_level(1);
}

/**
 * \brief Get level on TM1640_CLK
 *
 * Reads the level on a pin
 */
static inline bool TM1640_CLK_get_level()
{
	return PORTB_get_pin_level(1);
}

/**
 * \brief Set MSGEQ7_OUT pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull
 * modes are defined by device used
 *
 * \param[in] pull_mode Pin pull mode
 */
static inline void MSGEQ7_OUT_set_pull_mode(const enum port_pull_mode pull_mode)
{
	PORTC_set_pin_pull_mode(0, pull_mode);
}

/**
 * \brief Set MSGEQ7_OUT data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] direction PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void MSGEQ7_OUT_set_dir(const enum port_dir dir)
{
	PORTC_set_pin_dir(0, dir);
}

/**
 * \brief Set MSGEQ7_OUT level
 *
 * Sets output level on a pin
 *
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void MSGEQ7_OUT_set_level(const bool level)
{
	PORTC_set_pin_level(0, level);
}

/**
 * \brief Toggle output level on MSGEQ7_OUT
 *
 * Toggle the pin level
 */
static inline void MSGEQ7_OUT_toggle_level()
{
	PORTC_toggle_pin_level(0);
}

/**
 * \brief Get level on MSGEQ7_OUT
 *
 * Reads the level on a pin
 */
static inline bool MSGEQ7_OUT_get_level()
{
	return PORTC_get_pin_level(0);
}

/**
 * \brief Set MSGEQ7_RST pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull
 * modes are defined by device used
 *
 * \param[in] pull_mode Pin pull mode
 */
static inline void MSGEQ7_RST_set_pull_mode(const enum port_pull_mode pull_mode)
{
	PORTC_set_pin_pull_mode(1, pull_mode);
}

/**
 * \brief Set MSGEQ7_RST data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] direction PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void MSGEQ7_RST_set_dir(const enum port_dir dir)
{
	PORTC_set_pin_dir(1, dir);
}

/**
 * \brief Set MSGEQ7_RST level
 *
 * Sets output level on a pin
 *
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void MSGEQ7_RST_set_level(const bool level)
{
	PORTC_set_pin_level(1, level);
}

/**
 * \brief Toggle output level on MSGEQ7_RST
 *
 * Toggle the pin level
 */
static inline void MSGEQ7_RST_toggle_level()
{
	PORTC_toggle_pin_level(1);
}

/**
 * \brief Get level on MSGEQ7_RST
 *
 * Reads the level on a pin
 */
static inline bool MSGEQ7_RST_get_level()
{
	return PORTC_get_pin_level(1);
}

/**
 * \brief Set MSGEQ7_STB pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull
 * modes are defined by device used
 *
 * \param[in] pull_mode Pin pull mode
 */
static inline void MSGEQ7_STB_set_pull_mode(const enum port_pull_mode pull_mode)
{
	PORTC_set_pin_pull_mode(2, pull_mode);
}

/**
 * \brief Set MSGEQ7_STB data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] direction PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void MSGEQ7_STB_set_dir(const enum port_dir dir)
{
	PORTC_set_pin_dir(2, dir);
}

/**
 * \brief Set MSGEQ7_STB level
 *
 * Sets output level on a pin
 *
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void MSGEQ7_STB_set_level(const bool level)
{
	PORTC_set_pin_level(2, level);
}

/**
 * \brief Toggle output level on MSGEQ7_STB
 *
 * Toggle the pin level
 */
static inline void MSGEQ7_STB_toggle_level()
{
	PORTC_toggle_pin_level(2);
}

/**
 * \brief Get level on MSGEQ7_STB
 *
 * Reads the level on a pin
 */
static inline bool MSGEQ7_STB_get_level()
{
	return PORTC_get_pin_level(2);
}

#endif /* ATMEL_START_PINS_H_INCLUDED */
