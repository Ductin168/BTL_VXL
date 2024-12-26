#include "button.h"
#include <stdio.h>
#include "stm32f1xx_hal.h"  // Ensure this header is included
extern UART_HandleTypeDef huart2;
int KeyReg0[NUM_BUTTONS] = {NORMAL_STATE};
int KeyReg1[NUM_BUTTONS] = {NORMAL_STATE};
int KeyReg2[NUM_BUTTONS] = {NORMAL_STATE};
int KeyReg3[NUM_BUTTONS] = {NORMAL_STATE};

int TimeOutForKeyPress[NUM_BUTTONS] = {1000};
int button_pressed[NUM_BUTTONS] = {0};
int button_long_pressed[NUM_BUTTONS] = {0};
int button_flag[NUM_BUTTONS] = {0};

int isButtonPressed(int button_index){
    if(button_flag[button_index] == 1 && TimeOutForKeyPress[button_index]!= 0 ){
        button_flag[button_index] = 0;
        return 1;
    }
    return 0;
}

int isButtonLongPressed(int button_index){
    if(button_long_pressed[button_index] == 1){
        button_long_pressed[button_index] = 0;
        return 1;
    }
    return 0;
}

void display_timerRed() {
    lcd_clear_display();
//    HAL_Delay(1);
    clearRoadLed();
    char buffer[16];
    snprintf(buffer, sizeof(buffer), "meRED:%d", countRed);
    lcd_goto_XY(1, 0);
    lcd_send_string(buffer);
}

void display_timerGreen() {
    lcd_clear_display();
//    HAL_Delay(1);
    clearRoadLed();
    char buffer[16];
    snprintf(buffer, sizeof(buffer), "meGREEN:%d", countGreen);
    lcd_goto_XY(1, 0);
    lcd_send_string(buffer);
}

void display_timerAmber() {
    lcd_clear_display();
//    HAL_Delay(1);
    clearRoadLed();
    char buffer[16];
    snprintf(buffer, sizeof(buffer), "meYELLOW:%d", countYellow);
    lcd_goto_XY(1, 0);
    lcd_send_string(buffer);
}

char str1[50];
void subKeyProcess(int button_index) {
    switch (button_index) {
        case 0:
//        	if(MODE==1){
//        		currentmode=2 ;
//        	}
//            display7SEG_mode(currentmode);
            MODE = currentmode;
            if(MODE==2){
            	count=10;
            	sprintf(str1, "!MODE 2 : TIMERED#\r\n");
            	HAL_UART_Transmit(&huart2, (uint8_t*)str1, strlen(str1), 500);
            	sprintf(str1, "!TIMERED# : %d\r\n",countRed);
            	HAL_UART_Transmit(&huart2, (uint8_t*)str1, strlen(str1), 500);
                display_timerRed();
                blinkyRed();
            }
            if(MODE==3){
            	count1=10;
            	sprintf(str1, "!MODE 3 : TIMEYELLOW#\r\n");
            	HAL_UART_Transmit(&huart2, (uint8_t*)str1, strlen(str1), 500);
            	sprintf(str1, "!TIMEYELLOW# : %d\r\n",countYellow);
            	HAL_UART_Transmit(&huart2, (uint8_t*)str1, strlen(str1), 500);
                display_timerAmber();
            	blinkyAmber();
            }
            if(MODE==4){
            	count2=10;
            	sprintf(str1, "!MODE 4 : TIMEGREEN#\r\n");
            	HAL_UART_Transmit(&huart2, (uint8_t*)str1, strlen(str1), 500);
            	sprintf(str1, "!TIMEGREEN# : %d\r\n",countGreen);
            	HAL_UART_Transmit(&huart2, (uint8_t*)str1, strlen(str1), 500);
                display_timerGreen();
                blinkyGreen();
            }
            currentmode++;
            if(currentmode > 4) currentmode =2;
            status=INIT;
            break;
        case 1:
        	if(MODE!=1){
        	if( MODE==2){
        			count=10;
                    countRed++;
                    countGreen++;
                    if(countRed>99) countRed=1;
                    if(countGreen>99) countGreen=1;
                    display_timerRed();
                	sprintf(str1, "!TIMERED# : %d\r\n",countRed);
                	HAL_UART_Transmit(&huart2, (uint8_t*)str1, strlen(str1), 500);
                    blinkyRed();
        	}
        	if( MODE==3){
        		count1=10;
                    countYellow++;
                    countRed++;
                    status=GREEN_RED;
                    if(countRed>99) countRed=1;
                    if(countYellow>99) countYellow=1;
                    display_timerAmber();
                	sprintf(str1, "!TIMEYELLOW# : %d\r\n",countYellow);
                	HAL_UART_Transmit(&huart2, (uint8_t*)str1, strlen(str1), 500);
                	blinkyAmber();
        	}
        	if( MODE==4){
        		count2=10;
                    countRed++;
                    countGreen++;
                    if(countRed>99) countRed=1;
                    if(countGreen>99) countGreen=1;
                    display_timerGreen();
                	sprintf(str1, "!TIMEGREEN# : %d\r\n",countGreen);
                	HAL_UART_Transmit(&huart2, (uint8_t*)str1, strlen(str1), 500);
                    blinkyGreen();
        	}
        	}
            break;
        case 3:
        	if(MODE !=1 ){
        	if( MODE==2){
        		count=10;
        		if(countGreen>0){
                    countRed--;
                    countGreen--;
        		}
        		if(countGreen == 0){
                    countRed--;
                    countYellow--;
        		}
        		if(countRed<0) countRed=0;
                display_timerRed();
            	sprintf(str1, "!TIMERED# : %d\r\n",countRed);
            	HAL_UART_Transmit(&huart2, (uint8_t*)str1, strlen(str1), 500);
                blinkyRed();
        	}
        	else if( MODE==3){
        		count1=10;
        		if(countYellow>0){
                    countRed--;
                    countYellow--;
        		}
        		if(countYellow<0) {
        			countYellow=0;
        		}
                display_timerAmber();
            	sprintf(str1, "!TIMEYELLOW# : %d\r\n",countYellow);
            	HAL_UART_Transmit(&huart2, (uint8_t*)str1, strlen(str1), 500);
            	blinkyAmber();
        	}
        	else if( MODE==4){
        		count2=10;
        		if(countGreen>0){
                    countRed--;
                    countGreen--;
        		}
        		if(countGreen<0) countGreen=0;
                display_timerGreen();
            	sprintf(str1, "!TIMEGREEN# : %d\r\n",countGreen);
            	HAL_UART_Transmit(&huart2, (uint8_t*)str1, strlen(str1), 500);
                blinkyGreen();
        	}
        	}
            break;
        case 2:
        	if(MODE!=1){
            status=INIT;
            MODE = 1;
            red=countRed;
            green=countGreen;
            yellow=countYellow;
//            display7SEG_mode(MODE);
            currentmode = 2;
        	}
        	break;
    }
    button_flag[button_index] = 1;
}
void getKeyInput() {
    KeyReg2[0] = KeyReg1[0];
    KeyReg1[0] = KeyReg0[0];
    KeyReg2[1] = KeyReg1[1];
    KeyReg1[1] = KeyReg0[1];
    KeyReg2[2] = KeyReg1[2];
    KeyReg1[2] = KeyReg0[2];
    KeyReg2[3] = KeyReg1[3];
    KeyReg1[3] = KeyReg0[3];

    KeyReg0[0] = HAL_GPIO_ReadPin(BUTTON1_GPIO_Port, BUTTON1_Pin);
    KeyReg0[1] = HAL_GPIO_ReadPin(BUTTON2_GPIO_Port, BUTTON2_Pin);
    KeyReg0[2] = HAL_GPIO_ReadPin(BUTTON3_GPIO_Port, BUTTON3_Pin);
    KeyReg0[3] = HAL_GPIO_ReadPin(BUTTON4_GPIO_Port, BUTTON4_Pin);

    for (int i = 0; i < NUM_BUTTONS; i++) {
        if ((KeyReg1[i] == KeyReg0[i]) && (KeyReg1[i] == KeyReg2[i])) {
            if (KeyReg2[i] != KeyReg3[i]) {
                KeyReg3[i] = KeyReg2[i];

                if (KeyReg3[i] == PRESSED_STATE) {
                    TimeOutForKeyPress[i] = 1000; // Đặt lại thời gian chờ cho nhấn lâu
                    button_pressed[i] = 1; // Đánh dấu là đã nhấn
                } else {
                    if (button_pressed[i] && TimeOutForKeyPress[i] > 0) {
                        // Phát hiện nhấn ngắn
                        subKeyProcess(i);
                        button_pressed[i] = 0; // Đặt lại trạng thái nhấn
                    }
                }
            } else {
                if (KeyReg3[i] == PRESSED_STATE) {
                    TimeOutForKeyPress[i]--;
                    if (TimeOutForKeyPress[i] == 0) {
                        // Phát hiện nhấn lâu
                        button_long_pressed[i] = 1;
                        button_flag[i] = 0; // Đảm bảo không đặt cờ nhấn ngắn
                        button_pressed[i] = 0; // Đặt lại trạng thái nhấn
                    }
                }
            }
        }
    }
}
