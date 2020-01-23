/*
 * LEDMatrix.cpp
 *
 *  Created on: 8 oct. 2019
 *      Author: 11arc
 */
#include <Arduino.h>
#include "LEDMatrix.h"
#include "parameters.h"


void LEDMatrix::moveSnake(int next_row, int next_col, bool increase){
	if (next_row < 0 or next_row > 7 or next_col <0 or next_col >7)  // boundary check
		return;

	int last_pos[2] = {snake[snake_length -1][0], snake[snake_length -1][1]};

	for (int i=snake_length -1; i>0; i--){  // Rotate array
		snake[i][0] = snake[i-1][0];
		snake[i][1] = snake[i-1][1];
	}

	snake[0][0] = next_row;
	snake[0][1] = next_col;

	if (increase and snake_length < 64){
		snake[snake_length][0] = last_pos[0];
		snake[snake_length][1] = last_pos[1];
		snake_length++;
	}

	return;
}


void LEDMatrix::refreshNext(){
	// Update last_refreshed to next-to-refresh indexes
	if (last_refreshed[1] < 7){
		last_refreshed[1]++;
	} else if (last_refreshed[0] < 7){
		last_refreshed[0]++;
		last_refreshed[1] = 0;
	} else{
		last_refreshed[0] = 0;
		last_refreshed[1] = 0;
	}

	// Get LED state at those indexes
	bool led_state = checkLEDState(last_refreshed[0],last_refreshed[1]);

	// Update registers
	for (int i=0;i<8;i++){
		// In ROWS, HIGH = ON, LOW = OFF
		if (i==last_refreshed[0] and led_state)
			digitalWrite(DS_ROWS_PIN, HIGH);
		else
			digitalWrite(DS_ROWS_PIN, LOW);

		// In COLS, HIGH = OFF, LOW = ON
		if (i==last_refreshed[1] and led_state)
			digitalWrite(DS_COLS_PIN, LOW);
		else
			digitalWrite(DS_COLS_PIN, HIGH);

		digitalWrite(SH_CP_PIN, HIGH);  // Shift-Register clock pulse
		digitalWrite(SH_CP_PIN, LOW);
	}

	digitalWrite(ST_CP_PIN, HIGH);  // Storage Register clock pulse
	digitalWrite(ST_CP_PIN, LOW);

	return;
}


bool LEDMatrix::checkLEDState(int row, int col){
	if (snake_on){
		for (int i=0; i<snake_length; i++){
			if (snake[i][0]==row and snake[i][1]==col){
				return true;
			}
		}
	}

	if (food_on)
		return (food[0] == row and food[1] == col);
	else
		return false;
}

void LEDMatrix::updateState(bool turn_left, bool turn_right){

	if (game_over){  // On game over, only blink snake
		snake_on = not snake_on;
		return;
	}

	bool aux_direction;
	// turn direction
	if (turn_right){
		aux_direction = direction[3];
		for (int i=3; i>0; i--){
			direction[i] = direction[i-1];
		}
		direction[0] = aux_direction;
	} else if(turn_left){
		aux_direction = direction[0];
		for (int i=0; i<3; i++){
			direction[i] = direction[i+1];
		}
		direction[3] = aux_direction;
	}

	// Update position
	int next_pos[2];
	bool increase = false;

	// bottom-right corner = [0,0]
	if (direction[0]){
		next_pos[0] = snake[0][0] +1;
		next_pos[1] = snake[0][1];
	}else if (direction[1]){
		next_pos[0] = snake[0][0];
		next_pos[1] = snake[0][1] -1;
	}else if (direction[2]){
		next_pos[0] = snake[0][0] -1;
		next_pos[1] = snake[0][1];
	}else if (direction[3]){
		next_pos[0] = snake[0][0];
		next_pos[1] = snake[0][1] +1;
	}

	// Not checking for end of snake, since that would not be collision
	if (checkValidSpot(next_pos[0], next_pos[1], 0, snake_length-1)){
		if (next_pos[0]==food[0] and next_pos[1]==food[1]){
			increase = true;
			score++;
			generateFood();
		}
		moveSnake(next_pos[0], next_pos[1], increase);
	} else
		endGame();

	return;
}


void LEDMatrix::endGame(){
	game_over = true;
}


bool LEDMatrix::checkValidSpot(int row, int col, int start, int end){
	if (row <0 or col <0 or row>7 or col>7)  // Board limit check
		return false;

	// Self-collision check
	for (int i=start; i<end; i++){
		if (row == snake[i][0] and col == snake[i][1])
			return false;
	}

	return true;
}

void LEDMatrix::blinkFood(){
	food_on = not food_on;
	return;
}


void LEDMatrix::generateFood(){
	if (snake_length == 64){  // Full board, food set outside indefinitely
		food[0] = 8;
		food[1] = 8;
		return;
	}

	// VERY SLOW, should optimize
	int new_pos = random(64 - snake_length);  // New food at free spot #new_pos
	int free_spot_counter = 0;

	for (int i=0; i<64; i++){
		if (checkValidSpot(i/8, i%8, 0, snake_length)){
			free_spot_counter++;
			if (free_spot_counter == new_pos){
				food[0] = i/8;
				food[1] = i%8;
				break;
			}
		}
	}
}


int LEDMatrix::getScore(){
	return score;
}

bool LEDMatrix::checkGameOver(){
	return game_over;
}
