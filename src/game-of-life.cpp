#include "header/textures.h"
#include <random>

SDL_Renderer* renderer = nullptr;
SDL_Texture* GameOfLifeTexture = nullptr;
SDL_Rect sourceRect {0, 0, TEXTURE_W, TEXTURE_H};
SDL_Rect destRect {10, 10, SCREEN_W -20, SCREEN_H -20};

short int current_array[TEXTURE_W][TEXTURE_H] = { 0 };

void GameOfLifeInit(){
    srand(time(nullptr));
    for (int i = 0; i < 15000; i++){
        current_array[rand() % TEXTURE_H][rand() % TEXTURE_W]= 2;
    }
}
void CreateGameOfLifeTexture(){
    GameOfLifeTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, TEXTURE_W, TEXTURE_H);
}

//look around given cell in current_array and make sure that we don't try to access data beyond the borders of that array
bool isAlive(int x, int y){
    int alive_cells = 0;

    if (x-1 >=0)                                { if (current_array[y][x-1]   == 2) alive_cells ++; } // left
    if (x+1 <= TEXTURE_W)                       { if (current_array[y][x+1]   == 2) alive_cells ++; } // right
    if (y-1 >=0)                                { if (current_array[y-1][x]   == 2) alive_cells ++; } // top
    if (y+1 <= TEXTURE_H)                       { if (current_array[y+1][x]   == 2) alive_cells ++; } // bottom
    if (y-1 >=0 && x-1 >=0)                     { if (current_array[y-1][x-1] == 2) alive_cells ++; } // top left
    if (y+1 <= TEXTURE_H && x+1 <= TEXTURE_W)   { if (current_array[y+1][x+1] == 2) alive_cells ++; } // bottom right
    if (y-1 >=0 && x+1 <= TEXTURE_W)            { if (current_array[y-1][x+1] == 2) alive_cells ++; } // top right
    if (y+1 <= TEXTURE_H && x-1>=0)             { if (current_array[y+1][x-1] == 2) alive_cells ++; } // bottom left

    if (current_array[y][x] == 0){
        if (alive_cells == 3) return true;
        return false;
    }
    else if (current_array[y][x] == 2){
        if(alive_cells == 2 || alive_cells == 3) return true;
        return false;
    }
    return false; // error, the number tested neither represent a living cell or a dead one
}
// Creates an array representing the configuration of each cells in the new generation
void CreateNewGeneration(){
    int new_array[TEXTURE_W][TEXTURE_H] = { 0 };
    // look inside the current array for every living cell and copy paste them into new_array
    for(int y=0; y < TEXTURE_H; y++){
        for(int x=0; x < TEXTURE_W; x++){
            if (isAlive(x,y)) new_array[y][x] = 2;
        }
    }
    // copy new_array in current_array
    for(int y=0; y < TEXTURE_H; y++){
        for(int x=0; x < TEXTURE_W; x++){
            current_array[y][x] = new_array[y][x];
        }
    }
}
// draw one pixel on the texture for each
void DrawCurrentGeneration(){
    SDL_SetRenderTarget(renderer, GameOfLifeTexture); // we draw on GameOfLife texture
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // we clear the screen in white
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // we draw the cells in black
    for(int y=0; y < TEXTURE_H; y++){
        for(int x=0; x < TEXTURE_W; x++){
            if (current_array[y][x] == 2) SDL_RenderDrawPoint(renderer, x, y);
        }
    }
    // draw the generation on the window
    SDL_SetRenderTarget(renderer, nullptr);
    SDL_RenderCopy(renderer, GameOfLifeTexture, &sourceRect, &destRect);
    SDL_RenderPresent(renderer);
}