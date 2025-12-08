/*
 * API_Delay.c
 *
 *  Created on: Sep 5, 2025
 *      Author: Luciano J. Roqué
 *  Function of driver:
 *  Implementación de las funciones declaradas en API_Delay.h.
 *  Se manejan retardos no bloqueantes utilizando HAL_GetTick().
 ****************************************************************************/

/* Includes */
#include "main.h"
#include "API_Delay.h"

/* Function definitions */
/**
 * @brief Inicializa una estructura de delay con un tiempo específico.
 * @param delay Puntero a la estructura delay_t que se desea inicializar.
 * @param duration Tiempo de duración del retardo en milisegundos.
 * @retval Ninguno
 */
void delayInit(delay_t *delay, tick_t duration) {
    delay->duration = duration;
    delay->running = false;
}
/**
 * @brief Verifica si el retardo ha finalizado.
 * @param delay Puntero a la estructura delay_t que contiene el estado del retardo.
 * @retval true  Si ya transcurrió el tiempo del retardo.
 * @retval false Si el retardo sigue en curso.
 */
bool_t delayRead(delay_t *delay) {
    if (!delay->running) {
        delay->startTime = HAL_GetTick();
        delay->running = true;
        return false;
    } else {
        if ((HAL_GetTick() - delay->startTime) >= delay->duration) {
            delay->running = false;
            return true;
        } else {
            return false;
        }
    }
}
/**
 * @brief Modifica la duración del retardo.
 * @param delay Puntero a la estructura delay_t que se desea modificar.
 * @param duration Nuevo tiempo de duración del retardo en milisegundos.
 * @retval Ninguno
 */
void delayWrite(delay_t *delay, tick_t duration) {
    delay->duration = duration;
}
