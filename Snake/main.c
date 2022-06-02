#include <stdio.h> //printf
#include <unistd.h> //sleep and read
#include <termios.h> //RAW mode
#include <pthread.h> //seperate input thread
#include "graphics.h"
#include "main.h"


char direction = 'l';


int main(int arg_size, char **args){

	//default values
	int width = 25;
	int height = 10;

	//if there are enough arguments (0 is the executable name)
	if (arg_size >= 3) {
		width = *args[1];
		height = *args[2];
	}

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
	snakeArray[8] = width/2 + 3;
	snakeArray[9] = height/2;
	snakeArray[10] = -1;


	enableRawMode();

	pthread_t input;
	pthread_create(&input, NULL, inputThread, NULL);

	while (1==1){

		*snakeArray = moveSnake(snakeArray, direction);
	
		printf("\e[1;1H\e[2J");
		drawGrid(width, height, snakeArray);

	    struct timespec remaining, request = {0, 200000000};
		nanosleep(&request, &remaining);
	}
}


int moveSnake(int *pSnakeArray, char direction){

	int arrayLen = 0;
	
	while (*(pSnakeArray + arrayLen) != -1 ){ //go through the array until end is found (-1)
		arrayLen++;
	}

	int xDirection = 0;
	int yDirection = 0;
	
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
	//set the last value to -1
	*(pSnakeArray + arrayLen) = -1;

	//change the first value
	*(pSnakeArray + 0) = *(pSnakeArray + 2) + xDirection;
	*(pSnakeArray + 1) = *(pSnakeArray + 3) + yDirection;

	
	return *pSnakeArray;
	
}


void *inputThread(){
	printf("hi");
	while (1==1) {
		char c;
		read(STDIN_FILENO, &c, 1);

		if (c == '\x1b') {
		
			char seq[3];
			
			read(STDIN_FILENO, &seq[0], 1);
			read(STDIN_FILENO, &seq[1], 1);

			printf("%d ", seq[0]);
			printf("%d ", seq[1]);
			
			if (seq[0] == 91) {
				switch (seq[1]) {
					case 65: direction = 'u'; break;
					case 66: direction = 'd'; break;
					case 67: direction = 'r'; break;
					case 68: direction = 'l'; break;
				}
			}
		}
	}
}


int enableRawMode() {
	struct termios raw;
	
	tcgetattr(STDIN_FILENO, &raw);
	
	raw.c_lflag &= ~(ECHO | ICANON);
	
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
