/*
 * fsm_auto_run.h
 *
 *  Created on: Dec 6, 2024
 *      Author: DUC TIN
 */

#ifndef INC_FSM_AUTO_RUN_H_
#define INC_FSM_AUTO_RUN_H_

#include "main.h"
#include "global.h"
#include "scheduler.h"
#include "i2c-lcd.h"
#include "software_timer.h"
#include "button.h"
#include "fsm_manual_run.h"
#include "Traffic_Light_FSM.h"

void init_automatic();
void automatic_run();

#endif /* INC_FSM_AUTO_RUN_H_ */
