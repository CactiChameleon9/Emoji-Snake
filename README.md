# Emoji Snake
A terminal app for the well know game snake! Its programmed in C and uses emojis for the snake and apples

This is my first ever C project, made to help me learn C!!! (success?)


## Info
The program takes 2 optional inputs, width and height:
- `./main 40 15` runs snake with a 40 by 15 grid
- The default is 25 by 10

This program should build and run on linux, I have no intention of testing or supporting other operating systems at this time

## Building
```
git clone https://github.com/CactiChameleon9/Emoji-Snake
cd Emoji-Snake
gcc main.c graphics.c -o main -lpthread
#run with ./main
```
