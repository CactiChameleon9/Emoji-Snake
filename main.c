#include <stdio.h> //printf
#include <unistd.h> //sleep and read
#include <termios.h> //RAW mode
#include <pthread.h> //seperate input thread
#include <stdlib.h> //uniform random
#include "graphics.h"
#include "main.h"


char direction = 'l';


int main(int arg_size, char **args){

	//default values
	int width = 25;
	int height = 10;

	//if there are enough arguments (0 is the executable name)
	if (arg_size >= 3) {
		int tmpW = strtol(args[1], NULL, 10);
		int tmpH = strtol(args[2], NULL, 10);

		//grid cannot be smaller than 5*2
		if (tmpW >= 5) {width = tmpW;}
		if (tmpH >= 2) {height = tmpH;}
	}

	srandom(time(NULL)); //randomise the random seed

	//make the snakeArray (1d because it holds the order) and add default snake
	int snakeArray[width * height * 2 + 1];
	snakeArray[0] = width/2 - 1;
	snakeArray[1] = height/2;
	snakeArray[2] = width/2 + 0;
	snakeArray[3] = height/2;
	snakeArray[4] = width/2 + 1;
	snakeArray[5] = height/2;
	snakeArray[6] = width/2 + 2;
	snakeArray[7] = height/2;
	snakeArray[10] = -999;

	//define the apple position and randomise its position
	int applePos[2] = {0, 0};
	*applePos = moveApple(applePos, snakeArray, width, height);

	enableRawMode();

	//seperate input thread so movement and input can have seperate timings
	pthread_t input;
	pthread_create(&input, NULL, inputThread, NULL);

	int alive = 1;

	//main loop 	TODO: exit without ^C
	while (alive == 1){
		//recalc the snakeArray before moving
		*snakeArray = moveSnake(snakeArray, direction);

		//check for apple collisions and move it if it has, returns 1 if collided
		if (checkAppleCollision(applePos, snakeArray) == 1){
			//TODO points
			*snakeArray = increaseSnakeLength(snakeArray, 1);
			*applePos = moveApple(applePos, snakeArray, width, height);
		}

		//checks if the snake has crashed, returns 1 if they do
		if (checkSnakeCrash(snakeArray, width, height) == 1){
			alive = 0; //game over
		}
	
		printf("\e[1;1H\e[2J"); //clears terminal before redraw

		drawGrid(width, height, snakeArray, applePos);

		//sleep for 0.2 seconds before moving (nanosleep because sleep only supports ints)
	    struct timespec remaining, request = {0, 200000000};
		nanosleep(&request, &remaining);
	}
}


int moveSnake(int *pSnakeArray, char direction){

	int arrayLen = 0;
	
	while (*(pSnakeArray + arrayLen) != -999 ){ //go through the array until end is found (-999)
		arrayLen++;
	}

	int xDirection = 0;
	int yDirection = 0;

	//generate the direction vectors to add to the current head coordinate
	switch(direction){
		case 'u':
			xDirection = 0;
			yDirection = -1;
			break;
		
		case 'd':
			xDirection = 0;
			yDirection = 1;
			break;
		
		case 'l':
			xDirection = -1;
			yDirection = 0;
			break;
		
		case 'r':
			xDirection = 1;
			yDirection = 0;
			break;
	}

		/*
		14 = 12
		13 = 11
		...
		03 = 01
		02 = 00
		*/

	//move each value back 2 (cutting of the last 2 off)
	for (int i = arrayLen; i > 1; i--){
		*(pSnakeArray + i) = *(pSnakeArray + i - 2);
	}
	//set the last value to -999
	*(pSnakeArray + arrayLen) = -999;

	//change the first value
	*(pSnakeArray + 0) = *(pSnakeArray + 2) + xDirection;
	*(pSnakeArray + 1) = *(pSnakeArray + 3) + yDirection;

	
	return *pSnakeArray;
	
}


int increaseSnakeLength(int *pSnakeArray, int amount){
	for (int i = 0; i < amount; i++){
	
		int arrayLen = 0;
		while (*(pSnakeArray + arrayLen) != -999 ){ //go through the array until end is found (-999)
			arrayLen++;
		}

		//find the direction of travel of the tail by comparing the last 2 of x and y
		int xDirection = *(pSnakeArray + arrayLen - 2) - *(pSnakeArray + arrayLen - 4);
		int yDirection = *(pSnakeArray + arrayLen - 1) - *(pSnakeArray + arrayLen - 3);

		//add new values to the end of the array / back of snake
		*(pSnakeArray + arrayLen + 0) = *(pSnakeArray + arrayLen - 2) + xDirection;
		*(pSnakeArray + arrayLen + 1) = *(pSnakeArray + arrayLen - 1) + yDirection;

		//set the ending -999
		*(pSnakeArray + arrayLen + 2) = -999;

	}

	return *pSnakeArray;
}



int checkAppleCollision(int *pApplePos, int *pSnakeArray){

	int arrayLen = 0;
	while (*(pSnakeArray + arrayLen) != -999 ){ //go through the array until end is found (-999)
		arrayLen++;
	}

	int appleCollided = 0;
	for (int i = 0; i < arrayLen; i += 2){
		if (*(pSnakeArray + i) == *pApplePos && *(pSnakeArray + i + 1) == *(pApplePos + 1)){
			appleCollided = 1;
		}
	}
	
	return appleCollided;
}


int moveApple(int *pApplePos, int *pSnakeArray, int width, int height){

	int arrayLen = 0;
	while (*(pSnakeArray + arrayLen) != -999 ){ //go through the array until end is found (-999)
		arrayLen++;
	}

	//reroll apple position until not in snake
	int unoccupiedPos = 0;
	
	while (unoccupiedPos != 1){
	
		//if a collision is detected, randomise the apple position (not a very good random, ik)
		*(pApplePos + 0) = random() % width;
		*(pApplePos + 1) = random() % height;

		//check to see if the apple isn't in the snake, repeat loop if it is
		for (int i = 0; i < arrayLen; i += 2){
			if (*(pSnakeArray + i) != *(pApplePos + 0) && *(pSnakeArray + i + 1) != *(pApplePos + 1)){
				unoccupiedPos = 1;
			}
			
		}
	}

	return *pApplePos;

}

int checkSnakeCrash(int *pSnakeArray, int width, int height){
	int arrayLen = 0;
	
	while (*(pSnakeArray + arrayLen) != -999 ){ //go through the array until end is found (-999)
		arrayLen++;
	}

	//check for collisions
	for (int i = 2; i < arrayLen; i += 2){

	//check if the head collides with any of the body
		if (*(pSnakeArray + 0) == *(pSnakeArray + i + 0) &&
			*(pSnakeArray + 1) == *(pSnakeArray + i + 1)) {
			return 1; //collision
		}
	}

	//check if head out of bounds
	if (*(pSnakeArray + 0) >= width || *(pSnakeArray + 1) >= height ||
		*(pSnakeArray + 0) <= -1 || *(pSnakeArray + 1) <= -1){
		return 1; //collision
	}

	return 0;

	
}



void *inputThread(){
	while (1){
		//take an input a character and set it to c
		char c;
		read(STDIN_FILENO, &c, 1);

		//verify the input is beginning of a special character
		if (c != '\x1b') { return NULL; }

		//save the next 2 parts of the arrow
		char seq[2];
		
		read(STDIN_FILENO, &seq[0], 1);
		read(STDIN_FILENO, &seq[1], 1);
		
		//verify the input is actually an arrow key
		if (seq[0] != 91) { return NULL; }

		//change the direction depending on which arrow key is used (preventing opposite direction)
		switch (seq[1]) {
			case 65:
				if (direction == 'd') { break; }
				direction = 'u';
				break;
			case 66:
				if (direction == 'u') { break; }
				direction = 'd';
				break;
			case 67:
				if (direction == 'l') { break; }
				direction = 'r';
				break;
			case 68:
				if (direction == 'r') { break; }
				direction = 'l';
				break;
		}
	}
}

//https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html#turn-off-echoing

//raw mode == more control over the terminal input
// allows me to get each character as they are entered in (ICANON)
// and also hides the inputted characters (ECHO)
int enableRawMode() {
	struct termios raw;
	
	tcgetattr(STDIN_FILENO, &raw);
	
	raw.c_lflag &= ~(ECHO | ICANON);
	
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
