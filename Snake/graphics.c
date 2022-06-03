#include <stdio.h>
#include <string.h>
#include "graphics.h"

const char * SNAKE[] = {"🐍", "🌳", "🍃"};
const char * APPLE[] = {"🍎", "🍏"};


int drawGrid(int width, int height, int *pSnakeArray, int *pApplePos){

	//used to tell if its the start/end of the snake
	int snakesFound = 0;
	int snakeLength = 0;
	
	while (*(pSnakeArray + snakeLength) != -1 ){ //go through the array until end is found (-1)
		snakeLength++;
	}
	snakeLength = (snakeLength) / 2; //half it because array contains coordinates

	//this prints an x*y grid of dots
	for (int i = 0; i < height; i++){

		char widthString[200] = "";
		
		for (int j = 0; j < width; j++){

			int snake_index = linearXYSearch(snakeLength * 2, pSnakeArray, j, i);
		
			if (snake_index != -1) { //if a snake is found in that space
			
				snakesFound += 1;
				
				if (snake_index == 0) { //first value is the head
					strcat(widthString, SNAKE[0]);
					
				} else if (snake_index == (snakeLength - 1) * 2) { //tail
					strcat(widthString, SNAKE[2]);
					
				} else { //body
					strcat(widthString, SNAKE[1]);				
				}
			
			} else if (*(pApplePos) == j && *(pApplePos + 1) == i) { //if an apple is found in that space
					strcat(widthString, APPLE[0]); //TODO random apple type
			} else {
				strcat(widthString, "..");
			}
		}

		printf("%s\n", widthString);
		
	}

	return 0;
}


int linearXYSearch(int arrayLen, int *pArrayToSearch, int value_x, int value_y){

	for (int i = 0; i < arrayLen; i += 2){
		if (*(pArrayToSearch + i) == value_x && *(pArrayToSearch + i + 1) == value_y){
			return i;
		}
		
	}
	
	return -1;
	
}
