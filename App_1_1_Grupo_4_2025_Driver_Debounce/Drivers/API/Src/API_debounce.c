/*
 * API_debounce.c
 *
 *  Created on: Oct 10, 2025
 *      Author: Martin
 */

#include "API_debounce.h"

// -----------------------------------------------------------------------------
//  Definiciones Privadas
// -----------------------------------------------------------------------------

// Tiempo de anti-rebote: 40 ms
#define DEBOUNCE_TIME_MS 40

// -----------------------------------------------------------------------------
//  Variables Estáticas del Driver
// -----------------------------------------------------------------------------

// Estado actual de la MEF. (static para encapsulamiento)
static debounceState_t currentState;

// Tiempo de inicio del retardo no bloqueante.
static uint32_t startTimeMs;

// Estado lógico del pulsador (true si está confirmado como presionado).
static bool isPressed = false;

// -----------------------------------------------------------------------------
//  Funciones Estáticas Auxiliares (Internas al Driver)
// -----------------------------------------------------------------------------

/**
 * @brief Verifica si el tiempo de anti-rebote ha expirado (40 ms).
 *
 * Implementa el retardo no bloqueante.
 * @return true si el tiempo ha transcurrido, false en caso contrario.
 */
static bool checkDebounceTime() {
    // El desbordamiento se maneja automáticamente en aritmética de enteros sin signo
    // (siempre que el período no sea mayor a la mitad del rango de la variable).
    return (getCurrentMs() - startTimeMs >= DEBOUNCE_TIME_MS);
}

// -----------------------------------------------------------------------------
//  Implementación de las Funciones de la API Pública
// -----------------------------------------------------------------------------

/**
 * @brief Inicializa la MEF de anti-rebote.
 */
void debounceFSM_init() {
    // 1. Carga el estado inicial de la MEF.
    currentState = BUTTON_UP;

    // 2. Carga el tiempo de inicio para el delay.
    startTimeMs = 0;

    // 3. Carga el estado de la variable de lectura del pulsador en no activo.
    isPressed = false;
}

/**
 * @brief Actualiza el estado de la MEF de anti-rebote.
 */
void debounceFSM_update() {
    // 1. Leer las entradas (estado crudo del pin)
    bool currentInput = readKey();

    // 2. Resolver la lógica de transición de estados y actualizar las salidas.
    switch (currentState) {
        case BUTTON_UP:
            // Estado estable: Botón Liberado
            if (currentInput == true) {
                // Se detecta presión (posible rebote)
                currentState = BUTTON_FALLING;
                startTimeMs = getCurrentMs(); // Cargar el tiempo de inicio
            }
            break;

        case BUTTON_FALLING:
            // Rebote en curso: Esperando 40 ms para confirmar presión
            if (currentInput == false) {
                // Se libera antes de los 40 ms (falso positivo/rebote)
                currentState = BUTTON_UP;
            } else if (checkDebounceTime()) {
                // Botón presionado por 40 ms (Confirmado)
                currentState = BUTTON_DOWN;
                isPressed = true;
                // 3. Actualizar salidas (Función de Acción)
                buttonPressed(); // Ejecuta la acción del usuario para la pulsación (ej. invertir LED1)
            }
            break;

        case BUTTON_DOWN:
            // Estado estable: Botón Presionado
            if (currentInput == false) {
                // Se detecta liberación (posible rebote)
                currentState = BUTTON_RISING;
                startTimeMs = getCurrentMs(); // Cargar el tiempo de inicio
            }
            break;

        case BUTTON_RISING:
            // Rebote en curso: Esperando 40 ms para confirmar liberación
            if (currentInput == true) {
                // Se vuelve a presionar antes de los 40 ms (falso positivo/rebote)
                currentState = BUTTON_DOWN;
            } else if (checkDebounceTime()) {
                // Botón liberado por 40 ms (Confirmado)
                currentState = BUTTON_UP;
                isPressed = false;
                // 3. Actualizar salidas (Función de Acción)
                buttonReleased(); // Ejecuta la acción del usuario para la liberación (ej. invertir LED3)
            }
            break;

        default:
            // Estado no válido: Reiniciar MEF
            debounceFSM_init();
            break;
    }
}
