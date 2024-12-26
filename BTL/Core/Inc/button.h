/*
 * button.h
 *
 *  Created on: Oct 5, 2023
 *      Author: KAI
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"
#include "global.h"
#include "scheduler.h"
#include "i2c-lcd.h"
#include "software_timer.h"
#include "fsm_auto_run.h"
#include "fsm_manual_run.h"
#include "Traffic_Light_FSM.h"
#define NORMAL_STATE SET
#define PRESSED_STATE RESET
#define NUM_BUTTONS 4
extern int button_flag[NUM_BUTTONS];
extern void display_timerRed();
extern void display_timeGreen();
extern void display_timeAmber();
void getKeyInput();
#endif /* INC_BUTTON_H_ */

