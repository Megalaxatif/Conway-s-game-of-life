#pragma once
#include <SDL/SDL.h>
#include <ctime>
#include <chrono>

#define TEXTURE_H 100
#define TEXTURE_W 100
#define SCREEN_H  500
#define SCREEN_W  500
#define SPEED 10
#define ZOOM 1.5
#define DELAY 10

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