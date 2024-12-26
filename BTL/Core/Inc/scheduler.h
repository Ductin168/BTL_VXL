/*
 * scheduler.h
 *
 *  Created on: Dec 15, 2024
 *      Author: thuyh
 */

#ifndef INS_SCHEDULER_H_
#define INS_SCHEDULER_H_

#include "main.h"
#include "stdint.h"

void SCH_INIT(void);
void SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD);
void SCH_Update(void);
void SCH_Dispatch_Task(void);
void SCH_Delete_Task(uint32_t taskID);
void SCH_Add_Oneshot_Task(void (*pFunction)(),uint32_t DELAY);
void SCH_Go_To_Sleep(void);
void SCH_Report_Status(void);
#endif /* INS_SCHEDULER_H_ */

