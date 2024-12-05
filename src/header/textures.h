#pragma once

#include <SDL/SDL.h>
#include <vector>

#define TEXTURE_H 2000
#define TEXTURE_W 2000
#define SCREEN_H  500
#define SCREEN_W  500
#define POINT_NUMBER 10000 // it'll create as many points as it's written on the texture
#define SPEED 30
#define ZOOM 1.5
#define ARRAY_W 100
#define ARRAY_H 100

// rectangles for the display from the texture to the screen
extern SDL_Rect sourceRect;
extern SDL_Rect destRect;

extern SDL_Texture GameOfLifeTexture;
extern SDL_Renderer* renderer;

void CreateGameOfLifeTexture();
bool isAlive(int x, int y);
void CreateNewGeneration();
void DrawCurrentGeneration();