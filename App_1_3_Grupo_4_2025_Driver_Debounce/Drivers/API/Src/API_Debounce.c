/*
 * API_Debounce.c
 *
 *  Created on: Oct 9, 2025
 *      Author: Luciano J. Roqué
 *  Function of driver: Implementación de antirrebote por software usando una máquina de estados finita y retardos no bloqueantes.
 */

/* Includes *****************************************************************/
#include "main.h"
#include "API_Debounce.h"
#include "API_Delay.h"
#include "API_GPIO.h"   // Para usar la función de lectura del botón y manejar LEDs

/* Defines *****************************************************************/
#define DEBOUNCE_TIME_MS 40
#define LED1  (led_t){LD1_GPIO_Port, LD1_Pin}
#define LED3  (led_t){LD3_GPIO_Port, LD3_Pin}

/* Private typedef ********************************************************/
typedef enum {
    BUTTON_UP,
    BUTTON_FALLING,
    BUTTON_DOWN,
    BUTTON_RISING
} debounceState_t;

/* Private variables *************************************************************/
static debounceState_t state;   // Estado actual de la FSM
static delay_t debounceDelay;   // Retardo para el antirrebote
static bool_t buttonPressedFlag = false; // Flanco descendente detectado

/* Private function prototypes **************************************************/
static void buttonPressed(void);
static void buttonReleased(void);

/* Exported functions ******************************************************/

/**
  * @brief  Inicializa la máquina de estados del sistema antirrebote.
  * @param  None
  * @retval None
  */
void debounceFSM_init(void) {
    state = BUTTON_UP;
    delayInit(&debounceDelay, DEBOUNCE_TIME_MS);
    buttonPressedFlag = false;
}

/**
  * @brief  Actualiza la máquina de estados del sistema antirrebote.
  * @param  None
  * @retval None
  */
void debounceFSM_update(void) {
    switch (state) {
    case BUTTON_UP:
        if (readButton_GPIO() == false) {
            state = BUTTON_FALLING;
            delayInit(&debounceDelay, DEBOUNCE_TIME_MS);
        }
        break;

    case BUTTON_FALLING:
        if (delayRead(&debounceDelay)) {
            if (readButton_GPIO() == false) {
                state = BUTTON_DOWN;
                buttonPressed();
            } else {
                state = BUTTON_UP;
            }
        }
        break;

    case BUTTON_DOWN:
        if (readButton_GPIO() == true) {
            state = BUTTON_RISING;
            delayInit(&debounceDelay, DEBOUNCE_TIME_MS);
        }
        break;

    case BUTTON_RISING:
        if (delayRead(&debounceDelay)) {
            if (readButton_GPIO() == true) {
                state = BUTTON_UP;
                buttonReleased();
            } else {
                state = BUTTON_DOWN;
            }
        }
        break;

    default:
    	Error_Handler();
        break;
    }
}

/**
  * @brief  Devuelve el estado del botón. El valor se reinicia automáticamente al ser leído.
  * @param  None
  * @retval bool_t true si se presionó el botón, false en caso contrario.
  */
bool_t readKey(void) {
    if (buttonPressedFlag) {
        buttonPressedFlag = false;
        return true;
    }
    return false;
}

/* Private functions ******************************************************/
/**
  * @brief  Acción ejecutada al detectar una pulsación confirmada. Levanta el flag de pulsación.
  * @param  None
  * @retval None
  */
static void buttonPressed(void) {
    toggleLed_GPIO(LED1);
    buttonPressedFlag = true;
}

/**
  * @brief  Acción ejecutada al detectar una liberación del botón confirmada.
  * @param  None
  * @retval None
  */
static void buttonReleased(void) {
    toggleLed_GPIO(LED3);
}
