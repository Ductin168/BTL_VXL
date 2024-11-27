/*
 * System_FSM.c
 *
 *  Created on: Nov 24, 2024
 *      Author: Dell
 */


#include "System_FSM.h"

// Trạng thái chính
int trafficMode = AUTO_MODE;
//int autoStatus = INIT;
int manualStatus = OFF;
int tuningStatus = OFF;

// Bộ đếm thời gian cho từng hướng
int clock_counter_main = 0;
int clock_counter_side = 0;

// Thời gian mỗi đèn trong chế độ tự động
int timeRed = 5;
int timeAmber = 2;
int timeGreen = 3;


// ======================= CHẾ ĐỘ TỰ ĐỘNG =======================


void switchAutoState(int newState, int mainTime, int sideTime) {
    autoStatus = newState;
    clock_counter_main = mainTime;
    clock_counter_side = sideTime;
    clearRoadLed();
}

void display_i2c(void){
	char buffer[16];
	  snprintf(buffer, sizeof(buffer), "%d", clock_counter_main);
	  lcd_goto_XY(1, 0);
	  lcd_send_string(buffer);
}
void display_i2c1(void){
	char buffer[16];
	snprintf(buffer, sizeof(buffer), "%d", clock_counter_side);
	lcd_goto_XY(2, 0);
	lcd_send_string(buffer);
}
void fsm_traffic_auto_mode(void) {
    switch (autoStatus) {
        case OFF:
            break; // Không làm gì
        case INIT:
            switchAutoState(RED_GREEN, timeRed, timeGreen);
            timerFlag[1]=1;
            break;
        case RED_GREEN:
            turnOnRed1();
            turnOnGreen2();
            if(timerFlag[1]==1){
            if(clock_counter_side>=0){
            display_i2c();
            display_i2c1();
            clock_counter_side--;
            clock_counter_main--;
            }
            settimer1(1, 1000);
         }
            if (clock_counter_side < 0){
                switchAutoState(RED_AMBER, clock_counter_main+1, timeAmber);
                timerFlag[2]=1;
            }
            break;
        case RED_AMBER:
            turnOnRed1();
            turnOnAmber2();
            if(timerFlag[2]==1){
            if(clock_counter_side>=0){
            display_i2c();
            display_i2c1();
            clock_counter_side--;
            clock_counter_main--;
            settimer1(2,1000);
            }
         }
            if (clock_counter_side < 0){
                switchAutoState(GREEN_RED, timeGreen, timeRed);
                timerFlag[3]=1;
            }
            break;
        case GREEN_RED:
            turnOnGreen1();
            turnOnRed2();
            if(timerFlag[3]==1){
            if(clock_counter_side>=0){
            display_i2c();
            display_i2c1();
            clock_counter_side--;
            clock_counter_main--;
            settimer1(3,1000);
            }
         }
            if (clock_counter_main < 0)
                switchAutoState(AMBER_RED, timeAmber, clock_counter_side+1);
            timerFlag[4]=1;
            break;
        case AMBER_RED:
            turnOnAmber1();
            turnOnRed2();
            if(timerFlag[4]==1){
            if(clock_counter_side>=0){
            display_i2c();
            display_i2c1();
            clock_counter_side--;
            clock_counter_main--;
            settimer1(4,1000);
            }
         }
            if (clock_counter_main < 0)
                switchAutoState(RED_GREEN, timeRed, timeGreen);
            timerFlag[1]=1;
            break;
        default:
            break;
    }
}


// ======================= CHẾ ĐỘ TINH CHỈNH =======================
void logNewTime(){
	if (tuningStatus == RED_ADJ) HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "!TIMER RED :%d#\r\n",timeRed),500);
	if (tuningStatus == AMBER_ADJ) HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "!TIMER AMBER :%d#\r\n",timeAmber),500);
	if (tuningStatus == GREEN_ADJ) HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "!TIMER GREEN :%d#\r\n",timeGreen),500);
}
int initialTimeRed = 5;
int initialTimeAmber = 2;
int initialTimeGreen = 3;
void fsm_traffic_tunning_mode(void){
	switch(tuningStatus){
	case OFF:
		// do nothing
	case INIT:
		tuningStatus = RED_ADJ;
		clearRoadLed();
		logNewTime();
		timerFlag[5]=1;

		break;
	case RED_ADJ:
		blinkyRed();
		if (isButtonShortPressed(2)){
            timeRed = (timeRed + 1) % 100;
            logNewTime();
            lcd_clear_display();
        	char buffer[16];
        	snprintf(buffer, sizeof(buffer), "TimeRED:%d", timeRed );
        	lcd_goto_XY(1, 0);
        	lcd_send_string(buffer);
		}
		else if (isButtonLongPressed(2)){
            timeRed = (timeRed - 1 + 100) % 100;
            logNewTime();
            lcd_clear_display();
        	char buffer[16];
        	snprintf(buffer, sizeof(buffer), "TimeRED:%d", timeRed );
        	lcd_goto_XY(1, 0);
        	lcd_send_string(buffer);
		}
		else if (isButtonShortPressed(1)){
			tuningStatus = GREEN_ADJ;
			clearRoadLed();
			logNewTime();
	        lcd_clear_display();
	    	char buffer1[16];
	    	snprintf(buffer1, sizeof(buffer1), "TimeGREEN:%d", timeGreen );
	    	lcd_goto_XY(1, 0);
	    	lcd_send_string(buffer1);

		}
        else if(isButtonShortPressed(0)){
            // Đặt lại tất cả các đèn về thời gian ban đầu khi ấn nút 1
            timeRed = initialTimeRed;
            timeAmber = initialTimeAmber;
            timeGreen = initialTimeGreen;
            logNewTime();  // Gửi thông tin thời gian mới
            tuningStatus = GREEN_ADJ;  // Giữ trạng thái GREEN_ADJ
            clearRoadLed();  // Tắt tất cả đèn
        }
		break;
	case GREEN_ADJ:
		blinkyGreen();
		if(isButtonShortPressed(2)){
            timeGreen = (timeGreen + 1) % 100;
            logNewTime();
	        lcd_clear_display();
	    	char buffer1[16];
	    	snprintf(buffer1, sizeof(buffer1), "TimeGREEN:%d", timeGreen );
	    	lcd_goto_XY(1, 0);
	    	lcd_send_string(buffer1);
		}
		else if(isButtonLongPressed(2)){
            timeGreen = (timeGreen - 1 + 100) % 100;
            logNewTime();
	        lcd_clear_display();
	    	char buffer1[16];
	    	snprintf(buffer1, sizeof(buffer1), "TimeGREEN:%d", timeGreen );
	    	lcd_goto_XY(1, 0);
	    	lcd_send_string(buffer1);
		}
		else if(isButtonShortPressed(1)){
			tuningStatus = AMBER_ADJ;
			clearRoadLed();
			logNewTime();
			timerFlag[7]=1;
		}
        else if(isButtonShortPressed(0)){
            // Đặt lại tất cả các đèn về thời gian ban đầu khi ấn nút 1
            timeRed = initialTimeRed;
            timeAmber = initialTimeAmber;
            timeGreen = initialTimeGreen;
            logNewTime();  // Gửi thông tin thời gian mới
            tuningStatus = GREEN_ADJ;  // Giữ trạng thái GREEN_ADJ
            clearRoadLed();// Tắt tất cả đèn
        }
		break;
	case AMBER_ADJ:
		blinkyAmber();
		if (isButtonShortPressed(2)){
            timeAmber = (timeAmber + 1) % 100;
            logNewTime();
	        lcd_clear_display();
	    	char buffer1[16];
	    	snprintf(buffer1, sizeof(buffer1), "Timeamber:%d", timeGreen );
	    	lcd_goto_XY(1, 0);
	    	lcd_send_string(buffer1);

		}
		else if(isButtonLongPressed(2)){
            timeAmber = (timeAmber - 1 + 100) % 100;
            logNewTime();
	        lcd_clear_display();
	    	char buffer1[16];
	    	snprintf(buffer1, sizeof(buffer1), "Timeamber:%d", timeGreen );
	    	lcd_goto_XY(1, 0);
	    	lcd_send_string(buffer1);

		}
		else if (isButtonShortPressed(1)){
			tuningStatus = RED_ADJ;
			clearRoadLed();
			logNewTime();
			timerFlag[5]=1;
	        lcd_clear_display();
	    	char buffer1[16];
	    	snprintf(buffer1, sizeof(buffer1), "TimeRED:%d", timeGreen );
	    	lcd_goto_XY(1, 0);
	    	lcd_send_string(buffer1);
		}
        else if(isButtonShortPressed(0)){
            // Đặt lại tất cả các đèn về thời gian ban đầu khi ấn nút 1
            timeRed = initialTimeRed;
            timeAmber = initialTimeAmber;
            timeGreen = initialTimeGreen;
            logNewTime();  // Gửi thông tin thời gian mới
            tuningStatus = GREEN_ADJ;  // Giữ trạng thái GREEN_ADJ
            clearRoadLed();  // Tắt tất cả đèn
        }
		break;

	default:
		break;
	}
}
// ======================= CHUYỂN ĐỔI CHẾ ĐỘ =======================
void fsm_switch_mode(void){
	 if (isButtonLongPressed(1)){
		if (trafficMode != TUNING_MODE) {
			trafficMode = TUNING_MODE;
			HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "!SWITCH TO TUNING MODE#\r\n"),500);
			// TODO: prepare for next mode
			tuningStatus = INIT;
			autoStatus = OFF;
			manualStatus = OFF;
		}
		else {
			trafficMode = INIT;
			HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "!SWITCH TO AUTO MODE#\r\n"),500);
		}
	}
}
// ======================= VÒNG LẶP CHÍNH =======================
void fsm_traffic(void){
	switch(trafficMode){
	case INIT:
		if (timeRed != (timeAmber + timeGreen)){
			trafficMode = ERROR_MODE;
			HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "!TIMER ERROR#\r\n"),500);
			autoStatus = OFF;
			manualStatus = OFF;
			tuningStatus = OFF;
		}
		else {
			trafficMode = AUTO_MODE;
			autoStatus = INIT;
			manualStatus = OFF;
			tuningStatus = OFF;
			settimer1(0, 1000);
		}
		turnOffAllLED();
		break;
	case AUTO_MODE:

		fsm_traffic_auto_mode();
		break;
	case TUNING_MODE:
		fsm_traffic_tunning_mode();
		break;
	default:
		break;
	}
}

void clock_counter_traffic_update(void){
//	if((timer_flag[0] == 1) && (trafficMode == AUTO_MODE)){
//		clock_counter_main--;
//		clock_counter_side--;
//		HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "\n!7SEG WAY1:%d#\r\n",clock_counter_main),500);
//		HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "!7SEG WAY2:%d#\r\n",clock_counter_side),500);
//
//		setTimer(timer_duration[0], 0);
//	}
}
