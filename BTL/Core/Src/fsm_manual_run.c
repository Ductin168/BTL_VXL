/*
 * fsm_manual_run.c
 *
 *  Created on: Dec 6, 2024
 *      Author: DUC TIN
 */


#include "fsm_manual_run.h"
#include <stdio.h>
#include "stm32f1xx_hal.h"

extern UART_HandleTypeDef huart2;
char str[50];

void reset_time(){
    countRed = initRED;
    countYellow = initYELLOW;
    countGreen = initGREEN;
	sprintf(str, "!RESET TIME#\r\n");
	HAL_UART_Transmit(&huart2, (uint8_t*)str, strlen(str), 500);
	sprintf(str, "!TIMERED# : %d\r\n",countRed);
	HAL_UART_Transmit(&huart2, (uint8_t*)str, strlen(str), 500);
	sprintf(str, "!TIMEYELLOW# : %d\r\n",countYellow);
	HAL_UART_Transmit(&huart2, (uint8_t*)str, strlen(str), 500);
	sprintf(str, "!TIMEGREEN# : %d\r\n",countGreen);
	HAL_UART_Transmit(&huart2, (uint8_t*)str, strlen(str), 500);
}

void fsmmanual_run() {
    switch(MODE) {
        case 2:
            if (isButtonLongPressed(0) == 1) {
            	reset_time();
                MODE = 2;
            	display_timerRed();
                break;
            }
            blinkyRed();
            if (count > 0) {
                yellow = countYellow;
                red = countRed;
                green = countGreen;
                status=INIT;
            }
            if (count == 0) {
                status = GREEN_RED;
                timerFlag[0] = 1;
                count = 10;
                currentmode = 2;
                sprintf(str, "!TIMEOUT BACK TO MODE 1!#\r\n");
                HAL_UART_Transmit(&huart2, (uint8_t*)str, strlen(str), 500);
                MODE = 1;
            }
            break;

        case 3:
            if (isButtonLongPressed(0) == 1) {
            	reset_time();
                MODE = 3;
            	display_timerAmber();
                break;
            }
            blinkyAmber();
            if (count1 > 0) {
                yellow = countYellow;
                red = countRed;
                green = countGreen;
                status=INIT;

            }
            if (count1 == 0) {
                status = GREEN_RED;
                count1 = 10;
                currentmode = 2;
                timerFlag[0] = 1;
                sprintf(str, "!TIMEOUT BACK TO MODE 1 !#\r\n");
                HAL_UART_Transmit(&huart2, (uint8_t*)str, strlen(str), 500);
                MODE = 1;
            }
            break;

        case 4:
            if (isButtonLongPressed(0) == 1) {
            	reset_time();
                MODE = 4;
            	display_timerGreen();
                break;
            }
            blinkyGreen();
            if (count2 > 0) {
                yellow = countYellow;
                red = countRed;
                green = countGreen;
                status=INIT;
            }
            if (count2 == 0) {
                status = GREEN_RED;
                timerFlag[0] = 1;
                count2 = 10;
                currentmode = 2;
                sprintf(str, "!TIMEOUT BACK TO MODE 1!#\r\n");
                HAL_UART_Transmit(&huart2, (uint8_t*)str, strlen(str), 500);
                MODE = 1;
            }
            break;
    }
}
