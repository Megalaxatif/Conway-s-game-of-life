#pragma once
#include <iostream>
#include <SDL/SDL.h>

#define TEXTURE_H 700
#define TEXTURE_W 700
#define SCREEN_H  1000
#define SCREEN_W  1000
#define CELL_INIT 70*TEXTURE_H // the number of cells generated for each new seed. this number needs to be adapted accordingly with the texture size 
#define SPEED 20
#define ZOOM 20
#define DELAY 10
#define DELAY_MAX 500  // the maximum delay we can get in the generation, in millisecond
#define ALIVE_CELL 1             // the digit representing an alive cell in the arrays

// rectangles for the display from the texture to the screen
extern SDL_Rect sourceRect;
extern SDL_Rect destRect;

extern SDL_Texture* gameOfLifeTexture;  // main texture
extern SDL_Renderer* renderer;
extern SDL_Window* window;

extern float aliveCellColor_a[4];
extern float deadCellColor_a[4];

extern bool running;        // set on true when the simulation is running
extern bool generating;     // set on true when we create new generation
extern bool step;           // set on true when we generate step by step
extern int delay;           // delay between each generation