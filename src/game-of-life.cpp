#include "header/textures.h"

SDL_Renderer* renderer = nullptr;
SDL_Texture* GameOfLifeTexture;
SDL_Rect sourceRect {0, 0, 100, 100};
SDL_Rect destRect {10, 10, SCREEN_W -20, SCREEN_H -20};

short int current_array[ARRAY_W][ARRAY_H] = { 0 };

void CreateGameOfLifeTexture(){
    GameOfLifeTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, TEXTURE_W, TEXTURE_H);
}

bool isAlive(int x, int y){
    int alive_cells = 0;
    //look around the current cell and make sure that we don't try to access data beyond the borders of the array
    if (x-1>=0)         if (current_array[y][x-1] == 1) alive_cells ++;         // left
    if (x+1 <= ARRAY_W) if (current_array[y][x+1] == 1) alive_cells ++;         // right
    if (y-1 >=0)        if (current_array[y-1][x] == 1) alive_cells ++;         // top
    if (y+1 <= ARRAY_H) if (current_array[y+1][x] == 1) alive_cells ++;         // bottom

    if (alive_cells == 2 || alive_cells == 3) return true;  // the checked cell is alive
    return false;                                           // the checked cell is dead, either by underpopulation or by overpopulation
}
void CreateNewGeneration(){
    short int new_array[ARRAY_W][ARRAY_H] = { 0 };
    // look inside the current array for every living cell and copy paste them into new_array
    for(int y=0; y < ARRAY_H; y++){
        for(int x=0; x < ARRAY_W; x++){
            if (isAlive(x,y)) {
                new_array[y][x] = 1;
            }
        }
    }
    // copy new_array in current_array
    for(int y=0; y < ARRAY_H; y++){
        for(int x=0; x < ARRAY_W; x++){
            current_array[y][x] = new_array[y][x];
        }
    }
}
void DrawCurrentGeneration(){
    SDL_SetRenderTarget(renderer, GameOfLifeTexture); // we draw on GameOfLife texture
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    for(int y=0; y < ARRAY_H; y++){
        for(int x=0; x < ARRAY_W; x++){
            if (current_array[y][x] == 1){
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }
    SDL_SetRenderTarget(renderer, nullptr);
    SDL_RenderCopy(renderer, GameOfLifeTexture, &sourceRect, &destRect);
    SDL_RenderPresent(renderer);
}