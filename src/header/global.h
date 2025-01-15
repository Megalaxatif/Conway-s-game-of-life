#pragma once
#include <iostream>
#include <SDL/SDL.h>

#define TEXTURE_H 500
#define TEXTURE_W 500
#define SCREEN_H  1000
#define SCREEN_W  1000
#define CELL_INIT 25000 // the number of cells generated for each new seed. this number needs to be adapted accordingly with the texture size 
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

extern float cellColor_a[4];

extern bool running;
extern bool generating;
extern int delay;           //delay between each generation