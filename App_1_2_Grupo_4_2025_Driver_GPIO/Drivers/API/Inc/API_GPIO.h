/*
 * API_GPIO.h
 *
 *  Created on: Jul 19, 2025
 *      Author: Luciano J. Roqué
 *************************************************************/

#ifndef API_INC_API_GPIO_H_
#define API_INC_API_GPIO_H_

/* Includes **************************************************/
#include <stdint.h>
#include <stdbool.h>
/* Exported types ********************************************/
 typedef struct {
    GPIO_TypeDef* port;
    uint16_t pin;
  } led_t;

 typedef bool buttonStatus_t;

/* Exported function prototypes ******************************/
void MX_GPIO_Init(void);
void writeLedOn_GPIO(led_t led);
void writeLedOff_GPIO(led_t led);
void toggleLed_GPIO(led_t led);
buttonStatus_t readButton_GPIO(void);

#endif /* API_INC_API_GPIO_H_ */
