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
 * \brief Set OLED_CS pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull
 * modes are defined by device used
 *
 * \param[in] pull_mode Pin pull mode
 */
static inline void OLED_CS_set_pull_mode(const enum port_pull_mode pull_mode)
{
	PORTB_set_pin_pull_mode(0, pull_mode);
}

/**
 * \brief Set OLED_CS data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] direction PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void OLED_CS_set_dir(const enum port_dir dir)
{
	PORTB_set_pin_dir(0, dir);
}

/**
 * \brief Set OLED_CS level
 *
 * Sets output level on a pin
 *
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void OLED_CS_set_level(const bool level)
{
	PORTB_set_pin_level(0, level);
}

/**
 * \brief Toggle output level on OLED_CS
 *
 * Toggle the pin level
 */
static inline void OLED_CS_toggle_level()
{
	PORTB_toggle_pin_level(0);
}

/**
 * \brief Get level on OLED_CS
 *
 * Reads the level on a pin
 */
static inline bool OLED_CS_get_level()
{
	return PORTB_get_pin_level(0);
}

/**
 * \brief Set OLED_RST pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull
 * modes are defined by device used
 *
 * \param[in] pull_mode Pin pull mode
 */
static inline void OLED_RST_set_pull_mode(const enum port_pull_mode pull_mode)
{
	PORTB_set_pin_pull_mode(1, pull_mode);
}

/**
 * \brief Set OLED_RST data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] direction PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void OLED_RST_set_dir(const enum port_dir dir)
{
	PORTB_set_pin_dir(1, dir);
}

/**
 * \brief Set OLED_RST level
 *
 * Sets output level on a pin
 *
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void OLED_RST_set_level(const bool level)
{
	PORTB_set_pin_level(1, level);
}

/**
 * \brief Toggle output level on OLED_RST
 *
 * Toggle the pin level
 */
static inline void OLED_RST_toggle_level()
{
	PORTB_toggle_pin_level(1);
}

/**
 * \brief Get level on OLED_RST
 *
 * Reads the level on a pin
 */
static inline bool OLED_RST_get_level()
{
	return PORTB_get_pin_level(1);
}

/**
 * \brief Set OLED_DC pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull
 * modes are defined by device used
 *
 * \param[in] pull_mode Pin pull mode
 */
static inline void OLED_DC_set_pull_mode(const enum port_pull_mode pull_mode)
{
	PORTB_set_pin_pull_mode(2, pull_mode);
}

/**
 * \brief Set OLED_DC data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] direction PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void OLED_DC_set_dir(const enum port_dir dir)
{
	PORTB_set_pin_dir(2, dir);
}

/**
 * \brief Set OLED_DC level
 *
 * Sets output level on a pin
 *
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void OLED_DC_set_level(const bool level)
{
	PORTB_set_pin_level(2, level);
}

/**
 * \brief Toggle output level on OLED_DC
 *
 * Toggle the pin level
 */
static inline void OLED_DC_toggle_level()
{
	PORTB_toggle_pin_level(2);
}

/**
 * \brief Get level on OLED_DC
 *
 * Reads the level on a pin
 */
static inline bool OLED_DC_get_level()
{
	return PORTB_get_pin_level(2);
}

/**
 * \brief Set OLED_SDA pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull
 * modes are defined by device used
 *
 * \param[in] pull_mode Pin pull mode
 */
static inline void OLED_SDA_set_pull_mode(const enum port_pull_mode pull_mode)
{
	PORTB_set_pin_pull_mode(3, pull_mode);
}

/**
 * \brief Set OLED_SDA data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] direction PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void OLED_SDA_set_dir(const enum port_dir dir)
{
	PORTB_set_pin_dir(3, dir);
}

/**
 * \brief Set OLED_SDA level
 *
 * Sets output level on a pin
 *
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void OLED_SDA_set_level(const bool level)
{
	PORTB_set_pin_level(3, level);
}

/**
 * \brief Toggle output level on OLED_SDA
 *
 * Toggle the pin level
 */
static inline void OLED_SDA_toggle_level()
{
	PORTB_toggle_pin_level(3);
}

/**
 * \brief Get level on OLED_SDA
 *
 * Reads the level on a pin
 */
static inline bool OLED_SDA_get_level()
{
	return PORTB_get_pin_level(3);
}

/**
 * \brief Set PB4 pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull
 * modes are defined by device used
 *
 * \param[in] pull_mode Pin pull mode
 */
static inline void PB4_set_pull_mode(const enum port_pull_mode pull_mode)
{
	PORTB_set_pin_pull_mode(4, pull_mode);
}

/**
 * \brief Set PB4 data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] direction PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void PB4_set_dir(const enum port_dir dir)
{
	PORTB_set_pin_dir(4, dir);
}

/**
 * \brief Set PB4 level
 *
 * Sets output level on a pin
 *
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void PB4_set_level(const bool level)
{
	PORTB_set_pin_level(4, level);
}

/**
 * \brief Toggle output level on PB4
 *
 * Toggle the pin level
 */
static inline void PB4_toggle_level()
{
	PORTB_toggle_pin_level(4);
}

/**
 * \brief Get level on PB4
 *
 * Reads the level on a pin
 */
static inline bool PB4_get_level()
{
	return PORTB_get_pin_level(4);
}

/**
 * \brief Set OLED_SCL pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull
 * modes are defined by device used
 *
 * \param[in] pull_mode Pin pull mode
 */
static inline void OLED_SCL_set_pull_mode(const enum port_pull_mode pull_mode)
{
	PORTB_set_pin_pull_mode(5, pull_mode);
}

/**
 * \brief Set OLED_SCL data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] direction PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void OLED_SCL_set_dir(const enum port_dir dir)
{
	PORTB_set_pin_dir(5, dir);
}

/**
 * \brief Set OLED_SCL level
 *
 * Sets output level on a pin
 *
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void OLED_SCL_set_level(const bool level)
{
	PORTB_set_pin_level(5, level);
}

/**
 * \brief Toggle output level on OLED_SCL
 *
 * Toggle the pin level
 */
static inline void OLED_SCL_toggle_level()
{
	PORTB_toggle_pin_level(5);
}

/**
 * \brief Get level on OLED_SCL
 *
 * Reads the level on a pin
 */
static inline bool OLED_SCL_get_level()
{
	return PORTB_get_pin_level(5);
}

/**
 * \brief Set PB6 pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull
 * modes are defined by device used
 *
 * \param[in] pull_mode Pin pull mode
 */
static inline void PB6_set_pull_mode(const enum port_pull_mode pull_mode)
{
	PORTB_set_pin_pull_mode(6, pull_mode);
}

/**
 * \brief Set PB6 data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] direction PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void PB6_set_dir(const enum port_dir dir)
{
	PORTB_set_pin_dir(6, dir);
}

/**
 * \brief Set PB6 level
 *
 * Sets output level on a pin
 *
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void PB6_set_level(const bool level)
{
	PORTB_set_pin_level(6, level);
}

/**
 * \brief Toggle output level on PB6
 *
 * Toggle the pin level
 */
static inline void PB6_toggle_level()
{
	PORTB_toggle_pin_level(6);
}

/**
 * \brief Get level on PB6
 *
 * Reads the level on a pin
 */
static inline bool PB6_get_level()
{
	return PORTB_get_pin_level(6);
}

/**
 * \brief Set PB7 pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull
 * modes are defined by device used
 *
 * \param[in] pull_mode Pin pull mode
 */
static inline void PB7_set_pull_mode(const enum port_pull_mode pull_mode)
{
	PORTB_set_pin_pull_mode(7, pull_mode);
}

/**
 * \brief Set PB7 data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] direction PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void PB7_set_dir(const enum port_dir dir)
{
	PORTB_set_pin_dir(7, dir);
}

/**
 * \brief Set PB7 level
 *
 * Sets output level on a pin
 *
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void PB7_set_level(const bool level)
{
	PORTB_set_pin_level(7, level);
}

/**
 * \brief Toggle output level on PB7
 *
 * Toggle the pin level
 */
static inline void PB7_toggle_level()
{
	PORTB_toggle_pin_level(7);
}

/**
 * \brief Get level on PB7
 *
 * Reads the level on a pin
 */
static inline bool PB7_get_level()
{
	return PORTB_get_pin_level(7);
}

/**
 * \brief Set MAX17043_SDA pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull
 * modes are defined by device used
 *
 * \param[in] pull_mode Pin pull mode
 */
static inline void MAX17043_SDA_set_pull_mode(const enum port_pull_mode pull_mode)
{
	PORTC_set_pin_pull_mode(4, pull_mode);
}

/**
 * \brief Set MAX17043_SDA data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] direction PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void MAX17043_SDA_set_dir(const enum port_dir dir)
{
	PORTC_set_pin_dir(4, dir);
}

/**
 * \brief Set MAX17043_SDA level
 *
 * Sets output level on a pin
 *
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void MAX17043_SDA_set_level(const bool level)
{
	PORTC_set_pin_level(4, level);
}

/**
 * \brief Toggle output level on MAX17043_SDA
 *
 * Toggle the pin level
 */
static inline void MAX17043_SDA_toggle_level()
{
	PORTC_toggle_pin_level(4);
}

/**
 * \brief Get level on MAX17043_SDA
 *
 * Reads the level on a pin
 */
static inline bool MAX17043_SDA_get_level()
{
	return PORTC_get_pin_level(4);
}

/**
 * \brief Set MAX17043_SCL pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull
 * modes are defined by device used
 *
 * \param[in] pull_mode Pin pull mode
 */
static inline void MAX17043_SCL_set_pull_mode(const enum port_pull_mode pull_mode)
{
	PORTC_set_pin_pull_mode(5, pull_mode);
}

/**
 * \brief Set MAX17043_SCL data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] direction PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void MAX17043_SCL_set_dir(const enum port_dir dir)
{
	PORTC_set_pin_dir(5, dir);
}

/**
 * \brief Set MAX17043_SCL level
 *
 * Sets output level on a pin
 *
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void MAX17043_SCL_set_level(const bool level)
{
	PORTC_set_pin_level(5, level);
}

/**
 * \brief Toggle output level on MAX17043_SCL
 *
 * Toggle the pin level
 */
static inline void MAX17043_SCL_toggle_level()
{
	PORTC_toggle_pin_level(5);
}

/**
 * \brief Get level on MAX17043_SCL
 *
 * Reads the level on a pin
 */
static inline bool MAX17043_SCL_get_level()
{
	return PORTC_get_pin_level(5);
}

#endif /* ATMEL_START_PINS_H_INCLUDED */
