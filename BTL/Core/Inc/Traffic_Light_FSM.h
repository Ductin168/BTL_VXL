/*
 * Trafic_Light_FSM.h
 *
 *  Created on: Nov 24, 2024
 *      Author: Dell
 */

#ifndef INC_TRAFFIC_LIGHT_FSM_H_
#define INC_TRAFFIC_LIGHT_FSM_H_

#include "global.h"

void turnOffAllLED(void);

void turnOnAllLED(void);

void clearRoadLed(void);

//AUTO / MANUAL MODE:
//turn on the led with index:	0: way 1
//								1: way 2
void turnOnRed(int index);
void turnOnAmber(int index);
void turnOnGreen(int index);

//TUNING MODE:
//Blink the suitable led
void blinkyRed(void);
void blinkyAmber(void);
void blinkyGreen(void);

/*
 * @brief: set the pedestrian led
 *
 * @param:	0	-	RED
 * 			1	-	GREEN
 * @retval: None
 */
void setPedestrianLed(int index);
void unsetPedestrianLed(int index);

#endif /* INC_TRAFFIC_LIGHT_FSM_H_ */
