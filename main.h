#ifndef MAIN_H_INCLUDED   /* Include guard */
#define MAIN_H_INCLUDED

int output_grid(int width, int height, int grid[width][height]);

int moveSnake(int *pSnakeArray, char direction);

int increaseSnakeLength(int *pSnakeArray, int amount);

int checkAppleCollision(int *pApplePos, int *pSnakeArray);

int moveApple(int *pApplePos, int *pSnakeArray, int width, int height);

int checkSnakeCrash(int *pSnakeArray, int width, int height);

void *inputThread();

void enableRawMode();

#endif // MAIN_H_INCLUDED
