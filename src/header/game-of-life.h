#pragma once
#include <SDL/SDL.h>
#include <ctime>
#include <chrono>
#include <iostream>

#define TEXTURE_H 500
#define TEXTURE_W 500
#define SCREEN_H  1000
#define SCREEN_W  1000
#define CELL_INIT 25000 // the number of cells generated for each new seed. this number needs to be adapted accordingly with the texture size 
#define SPEED 20
#define ZOOM 20
#define DELAY 10
#define A 1             // the digit representing an alive cell in the arrays

// rectangles for the display from the texture to the screen
extern SDL_Rect sourceRect;
extern SDL_Rect destRect;

extern SDL_Texture* GameOfLifeTexture;
extern SDL_Renderer* renderer;

void CreateGameOfLifeTexture();
bool isAlive(int x, int y);
void CreateNewGeneration();
void DrawCurrentGeneration();
void GameOfLifeInit();
void DrawCell(int x, int y);
void DrawCurrentArray();