/*
 * API_Debounce.h
 *
 *  Created on: Oct 9, 2025
 *      Author: Luciano J. Roqué
 *  Function of driver: Implementación de antirrebote por software usando una máquina de estados finita y retardos no bloqueantes.
 */

#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_

/* Includes ***********************************************************************/
#include <stdint.h>
#include <stdbool.h>

/* Exported types *******************************************************************/
typedef bool bool_t;

/* Exported functions prototypes *****************************************************/
void debounceFSM_init(void);
void debounceFSM_update(void);
bool_t readKey(void);

#endif /* API_INC_API_DEBOUNCE_H_ */
