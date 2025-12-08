/*
 * API_debounce.h
 *
 *  Created on: Oct 10, 2025
 *      Author: Martin
 */

#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_

#include <stdint.h>
#include <stdbool.h>

// -----------------------------------------------------------------------------
//  Definiciones y Tipos de Datos
// -----------------------------------------------------------------------------

/**
 * @brief Estados de la Máquina de Estados Finitos (MEF) para el anti-rebote.
 */
typedef enum {
    BUTTON_UP,      // Botón liberado, estado estable.
    BUTTON_FALLING, // Transición de liberado a presionado (rebote en curso).
    BUTTON_DOWN,    // Botón presionado, estado estable.
    BUTTON_RISING   // Transición de presionado a liberado (rebote en curso).
} debounceState_t;

// -----------------------------------------------------------------------------
//  Funciones de la Interfaz del Driver (API Pública)
// -----------------------------------------------------------------------------

/**
 * @brief Inicializa la MEF de anti-rebote.
 *
 * Configura el estado inicial y los parámetros internos del driver.
 */
void debounceFSM_init();

/**
 * @brief Actualiza el estado de la MEF de anti-rebote.
 *
 * Esta función debe ser llamada periódicamente (ej. cada 1ms) desde el bucle principal.
 * Resuelve la lógica de transición, lee la entrada y actualiza las salidas.
 */
void debounceFSM_update();

/**
 * @brief Obtiene el estado lógico actual del pulsador (luego del anti-rebote).
 *
 * @return true si el botón está confirmado como PRESIONADO, false si está LIBERADO.
 */
bool debounceFSM_isPressed();

// -----------------------------------------------------------------------------
//  Funciones Externas (Hook/Callback) que deben ser implementadas por el usuario
// -----------------------------------------------------------------------------

/**
 * @brief Hook: Se llama una vez que se confirma la presión del botón (luego de 40ms).
 *
 * El usuario debe implementar esta función en su `main.c` o en un archivo de configuración
 * de la aplicación para definir la acción deseada (ej. invertir LED1).
 */
void buttonPressed();

/**
 * @brief Hook: Se llama una vez que se confirma la liberación del botón (luego de 40ms).
 *
 * El usuario debe implementar esta función para definir la acción deseada (ej. invertir LED3).
 */
void buttonReleased();

/**
 * @brief Hook: Lee el estado CRUDO del pin del pulsador.
 *
 * El usuario debe implementar esta función para retornar el estado directo
 * del pin de entrada (true si presionado, false si liberado).
 */
bool readKey();

/**
 * @brief Hook: Obtiene el tiempo actual en milisegundos (para el retardo no bloqueante).
 *
 * El usuario debe implementar esta función para retornar un contador de milisegundos.
 * (Ej. En STM32: `return HAL_GetTick();`).
 */
uint32_t getCurrentMs();

#endif /* API_INC_API_DEBOUNCE_H_ */
