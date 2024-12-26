/*
 * global.h
 *
 *  Created on: Sep 23, 2024
 *      Author: DUC TIN
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"
#include "global.h"
#include "scheduler.h"
#include "i2c-lcd.h"
#include "software_timer.h"
#include "button.h"
#include "fsm_auto_run.h"
#include "fsm_manual_run.h"
#include "Traffic_Light_FSM.h"

#define INIT 1
#define GREEN_RED 2
#define YELLOW_RED 3
#define RED_GREEN 4
#define RED_YELLOW 5

#define MAN_GREEN_RED 10
#define MAN_YELLOW_RED 11
#define MAN_RED_GREEN 12
#define MAN_RED_YELLOW 13

extern int currentmode;
extern int MODE;
extern int status;
extern int countRed;
extern int countGreen;
extern int countYellow;
extern int red,yellow,green;
extern int count, count1,count2;
extern int initRED;
extern int initYELLOW;
extern int initGREEN;

#endif /* INC_GLOBAL_H_ */
