#ifndef MAIN_H_INCLUDED   /* Include guard */
#define MAIN_H_INCLUDED

int output_grid(int width, int height, int grid[width][height]);

int moveSnake(int *pSnakeArray, char direction);

int enableRawMode();

void *inputThread();

#endif // MAIN_H_INCLUDED
