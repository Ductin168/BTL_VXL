/*
 * fsmautomatic.c
 *
 *  Created on: Sep 23, 2024
 *      Author: DUC TIN
 */
#include "fsm_auto_run.h"
#include <stdio.h>
#include "stm32f1xx_hal.h"

extern UART_HandleTypeDef huart2;
char str[50];
void automatic_run() {
	if(MODE == 1){
    switch (status) {
        case INIT:
        	sprintf(str, "\r!MODE 1 : AUTO RUN#\r\n");
        	HAL_UART_Transmit(&huart2, (uint8_t*)str, strlen(str), 500);
            status = GREEN_RED;
            currentmode == 2;
            clearRoadLed();
            timerFlag[0] = 1;
            break;

        case GREEN_RED:
            if ( isButtonPressed(1) == 1 && MODE==1) {
                red = countRed - countGreen;
                green = countGreen;
                yellow=countYellow;
                status = YELLOW_RED;
            	sprintf(str, "\r!SWITCH LED#\r\n");
            	HAL_UART_Transmit(&huart2, (uint8_t*)str, strlen(str), 500);
                timerFlag[1] = 1;
                timerFlag[0] = 0;
                break;
            } else if (timerFlag[0] == 1) {
                if (green >= 0) {
                    turnOnGreen1();
                    turnOnRed2();
                	lcd_clear_display();
                	HAL_Delay(10);
                	char buffer[16];
                	snprintf(buffer, sizeof(buffer), "GREEN: %d", green);
                	lcd_goto_XY(1, 0);
                	lcd_send_string(buffer);
                	char buffer1[16];
                	snprintf(buffer1, sizeof(buffer1), "RED: %d", red);
                	lcd_goto_XY(2, 0);
                	lcd_send_string(buffer1);
                	sprintf(str, "\r!GREEN# : %d\r\n",green);
                	HAL_UART_Transmit(&huart2, (uint8_t*)str, strlen(str), 500);
                	sprintf(str, "\r!RED# : %d\r\n",red);
                	HAL_UART_Transmit(&huart2, (uint8_t*)str, strlen(str), 500);
                	green--;
                	red--;
                }
                settimer1(0, 1000);
            }
            if (green < 0) {
                red++;
                status = YELLOW_RED;
                green = countGreen;
                timerFlag[1] = 1;
                break;
            }
            break;

        case YELLOW_RED:
        	if( isButtonPressed(1)==1&& MODE==1){
        		red=countRed;
        		green=countGreen;
        		yellow=countYellow;
                status = RED_GREEN;
            	sprintf(str, "\r!SWITCH LED#\r\n");
            	HAL_UART_Transmit(&huart2, (uint8_t*)str, strlen(str), 500);
                timerFlag[2] = 1;
                timerFlag[1] = 0;
                break;
        	}else if (timerFlag[1] == 1) {
                if (yellow >= 0) {
                    turnOnAmber1();
                    turnOnRed2();
                    	lcd_clear_display();
                    	HAL_Delay(10);
                    	char buffer[16];
                    	snprintf(buffer, sizeof(buffer), "YELLOW: %d", yellow);
                    	lcd_goto_XY(1, 0);
                    	lcd_send_string(buffer);
                    	char buffer1[16];
                    	snprintf(buffer1, sizeof(buffer1), "RED: %d", red);
                    	lcd_goto_XY(2, 0);
                    	lcd_send_string(buffer1);
                    	sprintf(str, "\r!YELLOW# : %d\r\n",yellow);
                    	HAL_UART_Transmit(&huart2, (uint8_t*)str, strlen(str), 500);
                    	sprintf(str, "\r!RED# : %d\r\n",red);
                    	HAL_UART_Transmit(&huart2, (uint8_t*)str, strlen(str), 500);
                    	yellow--;
                    	red--;

                }
                settimer1(1, 1000);
                break;
            }
            if (yellow < 0) {
                yellow = countYellow;
                red=countRed;
                status = RED_GREEN;
                timerFlag[2] = 1;
            }
            break;

        case RED_GREEN:
        	if( isButtonPressed(1)==1&& MODE==1){
        		red=countRed-countGreen;
        		green=countGreen;
        		yellow=countYellow;
                status = RED_YELLOW;
            	sprintf(str, "\r!SWITCH LED#\r\n");
            	HAL_UART_Transmit(&huart2, (uint8_t*)str, strlen(str), 500);
                timerFlag[3] = 1;
                timerFlag[2] = 0;
                break;
        	}
        	else if (timerFlag[2] == 1) {
                if (green >= 0) {
                    turnOnRed1();
                    turnOnGreen2();
                	lcd_clear_display();
                	HAL_Delay(10);
                	char buffer[16];
                	snprintf(buffer, sizeof(buffer), "RED: %d", red);
                	lcd_goto_XY(1, 0);
                	lcd_send_string(buffer);
                	char buffer1[16];
                	snprintf(buffer1, sizeof(buffer1), "GREEN: %d", green);
                	lcd_goto_XY(2, 0);
                	lcd_send_string(buffer1);
                	sprintf(str, "\r!RED# : %d\r\n",red);
                	HAL_UART_Transmit(&huart2, (uint8_t*)str, strlen(str), 500);
                	sprintf(str, "\r!GREEN# : %d\r\n",green);
                	HAL_UART_Transmit(&huart2, (uint8_t*)str, strlen(str), 500);
                	red--;
                	green--;
                }
                settimer1(2, 1000);
                break;
            }
            if (green < 0) {
            	red++;
                green = countGreen;
                status = RED_YELLOW;
                timerFlag[3] = 1;
            }
            break;

        case RED_YELLOW:

        	if( isButtonPressed(1)==1 && MODE==1){
        		red=countRed;
        		green=countGreen;
                status = GREEN_RED;
            	sprintf(str, "\r!SWITCH LED#\r\n");
            	HAL_UART_Transmit(&huart2, (uint8_t*)str, strlen(str), 500);
                timerFlag[0] = 1;
                timerFlag[3] = 0;
                break;
        	}
        	else if (timerFlag[3] == 1) {
                if (yellow >= 0) {
                    turnOnRed1();
                    turnOnAmber2();
                	lcd_clear_display();
                	HAL_Delay(10);
                	char buffer[16];
                	snprintf(buffer, sizeof(buffer), "RED: %d", red);
                	lcd_goto_XY(1, 0);
                	lcd_send_string(buffer);
                	char buffer1[16];
                	snprintf(buffer1, sizeof(buffer1), "YELLOW: %d", yellow);
                	lcd_goto_XY(2, 0);
                	lcd_send_string(buffer1);
                	sprintf(str, "\r!RED# : %d\r\n",red);
                	HAL_UART_Transmit(&huart2, (uint8_t*)str, strlen(str), 500);
                	sprintf(str, "\r!YELLOW# : %d\r\n",yellow);
                	HAL_UART_Transmit(&huart2, (uint8_t*)str, strlen(str), 500);
                    yellow--;
                    red--;
                }
                settimer1(3, 1000);
                break;
            }
            if (yellow < 0) {
                yellow = countYellow;
                red = countRed;
                status = GREEN_RED;
                timerFlag[0] = 1;
            }
            break;
    }
	}
}


