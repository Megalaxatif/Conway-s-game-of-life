#pragma once
#include <SDL/SDL.h>
#include <ctime>
#include <chrono>
#include <iostream>

#define TEXTURE_H 100
#define TEXTURE_W 100
#define SCREEN_H  500
#define SCREEN_W  500
#define SPEED 10
#define ZOOM 5
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