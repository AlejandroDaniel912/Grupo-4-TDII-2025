/**********************************************************************************
 * API_Delay.h
 *
 *  Created on: Sep 5, 2025
 *      Author: Luciano J. Roqué
 *  Function of driver: Manejo de retardos no bloqueantes usando HAL_GetTick().
 *
 ************************************************************************************/

#ifndef API_INC_API_DELAY_H_
#define API_INC_API_DELAY_H_

/* Includes ***********************************************************************/
#include <stdint.h>
#include <stdbool.h>

/* Exported types *******************************************************************/
typedef uint32_t tick_t;
typedef bool bool_t;

typedef struct {
    tick_t startTime;
    tick_t duration;
    bool_t running;
} delay_t;

/* Exported functions prototypes *****************************************************/
void delayInit(delay_t *delay, tick_t duration);
bool_t delayRead(delay_t *delay);
void delayWrite(delay_t *delay, tick_t duration);

#endif /* API_INC_API_DELAY_H_ */
