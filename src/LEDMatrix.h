/*
 * Matrix.h
 *
 *  Created on: 8 oct. 2019
 *      Author: Andrés G
 */

#ifndef LEDMATRIX_H_
#define LEDMATRIX_H_

class LEDMatrix
{
private:
	int last_refreshed[2] = {0,0};  // (row#, col#) (for LED handling)
	bool snake_on = true;  // Blinking snake on game over

	int food[2] = {2,2};
	bool food_on = true;
	int snake_length = 5;
	int snake[64][2] = {{5,5},{5,6},{4,6},{3,6},{2,6},};  // One for each grid position
	bool direction[4] = {false, true, false, false};  // UP, RIGHT, DOWN, LEFT
	bool game_over = false;
	int score = 0;

	void moveSnake(int, int, bool);
	void endGame();
	bool checkLEDState(int, int);
	bool checkValidSpot(int, int, int, int);
	void generateFood();

public:
	void refreshNext();
	void updateState(bool, bool);
	void blinkFood();
	int getScore();
	bool checkGameOver();

};

#endif /* LEDMATRIX_H_ */
