#include <global.h>

SDL_Renderer* renderer = nullptr;
SDL_Window* window = nullptr;

bool running = true;
bool generating = true;
int delay = 100; // delay between each generation
bool step = false;

float aliveCellColor_a[4] = { 0.85f, 0.85f, 0.85f, 1.0f };
float deadCellColor_a[4] = { 0.12f, 0.12f, 0.12f, 1.0f };

SDL_Texture* gameOfLifeTexture = nullptr;
SDL_Rect sourceRect {0, 0, TEXTURE_W, TEXTURE_H};
SDL_Rect destRect {10, 10, SCREEN_W -20, SCREEN_H -20};
