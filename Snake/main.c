#include "graphics.h"


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
	grid[10][5] = 2;
	grid[11][5] = 1;
	grid[12][5] = 1;
	grid[13][5] = 1;
	grid[14][5] = 1;
	grid[15][5] = 1;
	grid[15][6] = 1;
	grid[15][7] = 1;

	int snakeArray[200];
	

	int snakesFound = 0;
	
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
		
			if (grid[j][i] == 2){
				snakeArray[0] = j;
				snakeArray[1] = i;
			}
				
			if (grid[j][i] == 1){
				snakesFound += 1;
				snakeArray[0 + (snakesFound * 2)] = j;
				snakeArray[1 + (snakesFound * 2)] = i;
			}
		}
	}

	snakeArray[snakesFound * 2 + 2] = -1;
		
	drawGrid(width, height, snakeArray);
}
