/**
 * Copyright (c) 2014 - 2017, Nordic Semiconductor ASA
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
#ifndef BOARDS_H
#define BOARDS_H

#include "nrf_gpio.h"
#include "h176.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Function for returning the state of an LED.
 *
 * @param led_idx LED index (starting from 0), as defined in the board-specific header.
 *
 * @return True if the LED is turned on.
 */
bool bsp_board_led_state_get(uint32_t led_idx);

/**
 * Function for turning on an LED.
 *
 * @param led_idx LED index (starting from 0), as defined in the board-specific header.
 */
void bsp_board_led_on(uint32_t led_idx);

/**
 * Function for turning off an LED.
 *
 * @param led_idx LED index (starting from 0), as defined in the board-specific header.
 */
void bsp_board_led_off(uint32_t led_idx);

/**
 * Function for inverting the state of an LED.
 *
 * @param led_idx LED index (starting from 0), as defined in the board-specific header.
 */
void bsp_board_led_invert(uint32_t led_idx);
/**
 * Function for turning off all LEDs.
 */
void bsp_board_leds_off(void);

/**
 * Function for turning on all LEDs.
 */
void bsp_board_leds_on(void);

/**
 * Function for initializing LEDs.
 */
void bsp_board_leds_init(void);

/**
 * Function for converting pin number to LED index.
 *
 * @param pin_number Pin number.
 *
 * @return LED index of the given pin or 0xFFFFFFFF if invalid pin provided.
 */
uint32_t bsp_board_pin_to_led_idx(uint32_t pin_number);

/**
 * Function for converting LED index to pin number.
 *
 * @param led_idx LED index.
 *
 * @return Pin number.
 */
uint32_t bsp_board_led_idx_to_pin(uint32_t led_idx);

/**
 * Function for returning the state of a button.
 *
 * @param button_idx Button index (starting from 0), as defined in the board-specific header.
 *
 * @return True if the button is pressed.
 */
bool bsp_board_button_state_get(uint32_t button_idx);

/**
 * Function for initializing buttons.
 */
void bsp_board_buttons_init(void);

/**
 * Function for converting pin number to button index.
 *
 * @param pin_number Pin number.
 *
 * @return Button index of the given pin or 0xFFFFFFFF if invalid pin provided.
 */
uint32_t bsp_board_pin_to_button_idx(uint32_t pin_number);


/**
 * Function for converting button index to pin number.
 *
 * @param button_idx Button index.
 *
 * @return Pin number.
 */
uint32_t bsp_board_button_idx_to_pin(uint32_t button_idx);

#define BSP_BOARD_LED_0 0
#define BSP_BOARD_LED_1 1

#ifdef BSP_LED_0
#define BSP_LED_0_MASK (1<<BSP_LED_0)
#else
#define BSP_LED_0_MASK 0
#endif
#ifdef BSP_LED_1
#define BSP_LED_1_MASK (1<<BSP_LED_1)
#else
#define BSP_LED_1_MASK 0
#endif


#define LEDS_MASK      (BSP_LED_0_MASK | BSP_LED_1_MASK )

#define BSP_BOARD_BUTTON_0 0
#define BSP_BOARD_BUTTON_1 1
#

#ifdef BSP_BUTTON_0
#define BSP_BUTTON_0_MASK (1<<BSP_BUTTON_0)
#else
#define BSP_BUTTON_0_MASK 0
#endif
#ifdef BSP_BUTTON_1
#define BSP_BUTTON_1_MASK (1<<BSP_BUTTON_1)
#else
#define BSP_BUTTON_1_MASK 0
#endif

#define BUTTONS_MASK   (BSP_BUTTON_0_MASK | BSP_BUTTON_1_MASK )


#define LEDS_OFF(leds_mask) do {  ASSERT(sizeof(leds_mask) == 4);                     \
                        NRF_GPIO->OUTSET = (leds_mask) & (LEDS_MASK & LEDS_INV_MASK); \
                        NRF_GPIO->OUTCLR = (leds_mask) & (LEDS_MASK & ~LEDS_INV_MASK); } while (0)

#define LEDS_ON(leds_mask) do {  ASSERT(sizeof(leds_mask) == 4);                     \
                       NRF_GPIO->OUTCLR = (leds_mask) & (LEDS_MASK & LEDS_INV_MASK); \
                       NRF_GPIO->OUTSET = (leds_mask) & (LEDS_MASK & ~LEDS_INV_MASK); } while (0)

#define LED_IS_ON(leds_mask) ((leds_mask) & (NRF_GPIO->OUT ^ LEDS_INV_MASK) )

#define LEDS_INVERT(leds_mask) do { uint32_t gpio_state = NRF_GPIO->OUT;      \
                              ASSERT(sizeof(leds_mask) == 4);                 \
                              NRF_GPIO->OUTSET = ((leds_mask) & ~gpio_state); \
                              NRF_GPIO->OUTCLR = ((leds_mask) & gpio_state); } while (0)

#define LEDS_CONFIGURE(leds_mask) do { uint32_t pin;                  \
                                  ASSERT(sizeof(leds_mask) == 4);     \
                                  for (pin = 0; pin < 32; pin++)      \
                                      if ( (leds_mask) & (1 << pin) ) \
                                          nrf_gpio_cfg_output(pin); } while (0)

#ifdef __cplusplus
}
#endif

#endif
