/*
 * parameters.h
 *
 *  Created on: 16 oct. 2019
 *      Author: 11arc
 */

#ifndef PARAMETERS_H_
#define PARAMETERS_H_

#define REFRESH_DELAY_MICROSECONDS 70  // Micros spent on each LED
#define GAME_UPDATE_MILLISECONDS 450  // Millis between state update
#define FOOD_BLINK_MILLISECONDS 150  // Millis between state update
#define DS_COLS_PIN 10  // Serial Data
#define DS_ROWS_PIN 11  // Serial Data
#define ST_CP_PIN 12    // Storage Clock
#define SH_CP_PIN 13  // Shift-Register Clock

#define LEFT_PIN 8  // Button
#define RIGHT_PIN 9  // Button

#define SEG7_A 2
#define SEG7_B 3
#define SEG7_C 4
#define SEG7_D 5
#define SEG7_E 6
#define SEG7_F 7
#define SEG7_G 14
#define SEG7_DP 15  // ----

#define DISP_0 19
#define DISP_1 18
#define DISP_2 17

#endif /* PARAMETERS_H_ */
