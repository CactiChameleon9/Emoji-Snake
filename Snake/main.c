#include <stdio.h>
#include <unistd.h>
#include "graphics.h"
#include "main.h"


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

	
	while (1==1){
		*snakeArray = moveSnake(snakeArray, 'r');
	
		printf("\e[1;1H\e[2J");
		drawGrid(width, height, snakeArray);
		
		sleep(1);
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
