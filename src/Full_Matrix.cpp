#include <Arduino.h>
#include "parameters.h"
#include "LEDMatrix.h"



void switchDisplay();
void writeToDisplay(int num);



LEDMatrix led_matrix;
int active_display = 0;
int score = 0;

unsigned long last_refresh_micros = 0;
unsigned long last_move_millis = 0;
unsigned long last_blink_millis = 0;

byte digit_display[11][7] ={
		{1 , 1 , 1 , 1 , 1 , 1 , 0},
		{0 , 1 , 1 , 0 , 0 , 0 , 0},
		{1 , 1 , 0 , 1 , 1 , 0 , 1},
		{1 , 1 , 1 , 1 , 0 , 0 , 1},
		{0 , 1 , 1 , 0 , 0 , 1 , 1},
		{1 , 0 , 1 , 1 , 0 , 1 , 1},
		{1 , 0 , 1 , 1 , 1 , 1 , 1},
		{1 , 1 , 1 , 0 , 0 , 0 , 0},
		{1 , 1 , 1 , 1 , 1 , 1 , 1},
		{1 , 1 , 1 , 0 , 0 , 1 , 1},
		{0 , 0 , 0 , 0 , 0 , 0 , 1}  // "-"
};


void setup() {
	//  All outputs initialized to low and configured
	digitalWrite(DS_COLS_PIN, LOW);
	digitalWrite(DS_ROWS_PIN, LOW);
	digitalWrite(ST_CP_PIN, LOW);
	digitalWrite(SH_CP_PIN, LOW);

	pinMode(DS_COLS_PIN, OUTPUT);
	pinMode(DS_ROWS_PIN, OUTPUT);
	pinMode(ST_CP_PIN, OUTPUT);
	pinMode(SH_CP_PIN, OUTPUT);
	pinMode(LEFT_PIN, INPUT);
	pinMode(RIGHT_PIN, INPUT);

	pinMode(SEG7_A, OUTPUT);
	pinMode(SEG7_B, OUTPUT);
	pinMode(SEG7_C, OUTPUT);
	pinMode(SEG7_D, OUTPUT);
	pinMode(SEG7_E, OUTPUT);
	pinMode(SEG7_F, OUTPUT);
	pinMode(SEG7_G, OUTPUT);
//	pinMode(SEG7_DP, OUTPUT);
	pinMode(DISP_0, OUTPUT);
	pinMode(DISP_1, OUTPUT);
	pinMode(DISP_2, OUTPUT);


	digitalWrite(SEG7_A, 1);
	digitalWrite(SEG7_B, 1);
	digitalWrite(SEG7_C, 1);
	digitalWrite(SEG7_D, 1);
	digitalWrite(SEG7_E, 1);
	digitalWrite(SEG7_F, 1);
	digitalWrite(DISP_0, 1);
	digitalWrite(DISP_1, 1);
	digitalWrite(DISP_2, 0);
//	digitalWrite(SEG7_DP, 1);

}

void loop() {
	// LED Matrix Refresh (NO OVERFLOW PROTECTION)
	if (micros() >= REFRESH_DELAY_MICROSECONDS + last_refresh_micros){
		last_refresh_micros = micros();
		led_matrix.refreshNext();
		switchDisplay();
	}

	// Game updates (NO OVERFLOW PROTECTION)
	if (millis() >= GAME_UPDATE_MILLISECONDS + last_move_millis){
		last_move_millis = millis();
		led_matrix.updateState(digitalRead(LEFT_PIN)==HIGH, digitalRead(RIGHT_PIN)==HIGH);
		score = led_matrix.getScore();
//		writeToDisplay(score%10);
	}

	// Food blink (NO OVERFLOW PROTECTION)
	if (millis() >= FOOD_BLINK_MILLISECONDS + last_blink_millis){
		last_blink_millis = millis();
		led_matrix.blinkFood();
	}

}


void switchDisplay(){
	if (active_display == 0){
		active_display = 1;
		digitalWrite(DISP_0, 1);
		writeToDisplay((score%100)/10);
		digitalWrite(DISP_1, 0);
	} else if (active_display == 1){
		active_display = 2;
		digitalWrite(DISP_1, 1);
		writeToDisplay(score%10);
		digitalWrite(DISP_2, 0);
	} else{
		active_display = 0;
		digitalWrite(DISP_2, 1);
		writeToDisplay(score/100);
		digitalWrite(DISP_0, 0);
	}
}

void writeToDisplay(int num){

	digitalWrite(SEG7_A, digit_display[num][0]);
	digitalWrite(SEG7_B, digit_display[num][1]);
	digitalWrite(SEG7_C, digit_display[num][2]);
	digitalWrite(SEG7_D, digit_display[num][3]);
	digitalWrite(SEG7_E, digit_display[num][4]);
	digitalWrite(SEG7_F, digit_display[num][5]);
	digitalWrite(SEG7_G, digit_display[num][6]);
}
