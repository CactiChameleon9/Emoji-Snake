#include <stdio.h>
#include <unistd.h>
#include "graphics.h"
#include "main.h"


int main(int arg_size, char **args){
	int width = 25;
	int height = 10;
	
	if (arg_size >= 3) {
		width = *args[1];
		height = *args[2];
	}

	int grid[width][height];

	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			grid[j][i] = 0;
		}
	}

	//start the snake
	grid[10][5] = 3; //head
	grid[11][5] = 2;
	grid[12][5] = 2;
	grid[13][5] = 2; //middle
	grid[14][5] = 2;
	grid[15][5] = 2;
	grid[15][6] = 2;
	grid[15][7] = 1; //tail

	while (1==1){
		output_grid(width, height, grid);
		sleep(1);
	}

}


int output_grid(int width, int height, int grid[width][height]){

	printf("\e[1;1H\e[2J");

	//the snake array will at most be the size of the grid doubled because xy, plus 1 for -1 ending
	int snakeArray[width * height * 2 + 1];

	//this is used to track what position in the array should be used for the body / tail 
	int snakesFound = 0;

	//iterate through the 2d array and populate the 1d aray
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
		
			if (grid[j][i] == 3){
				snakeArray[0] = j;
				snakeArray[1] = i;
			}
				
			if ((grid[j][i] == 2) || (grid[j][i] == 1)){ //TODO tail
				snakesFound += 1;
				snakeArray[0 + (snakesFound * 2)] = j;
				snakeArray[1 + (snakesFound * 2)] = i;
			}
		}
	}

	snakeArray[snakesFound * 2 + 2] = -1; //marker used to tell once the array is done
		
	drawGrid(width, height, snakeArray);
}

