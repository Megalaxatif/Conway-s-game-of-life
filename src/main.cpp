#include <SDL/SDL.h>
#include <iostream>
#include "header/textures.h"
#undef main

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    
    SDL_Window* window = nullptr;
    SDL_Event event;

    SDL_CreateWindowAndRenderer(SCREEN_W, SCREEN_H, 0, &window, &renderer);
    SDL_RenderSetScale(renderer, 1, 1);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // clear the screen
    SDL_RenderClear(renderer);

    CreateGameOfLifeTexture();
    // main loop
    bool running = true;
    while (running){
        // input handler
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) running = false;
        else if (event.type == SDL_KEYDOWN){
            switch (event.key.keysym.sym){
                case SDLK_RIGHT : if(sourceRect.x + SPEED + sourceRect.w <= TEXTURE_W)  sourceRect.x += SPEED; break;
                case SDLK_LEFT  : if(sourceRect.x - SPEED >= 0)                         sourceRect.x -= SPEED; break;
                case SDLK_UP    : if(sourceRect.y - SPEED >= 0)                         sourceRect.y -= SPEED; break;
                case SDLK_DOWN  : if(sourceRect.y + SPEED + sourceRect.h <= TEXTURE_H)  sourceRect.y += SPEED; break;
                case SDLK_1     :                                                       sourceRect.h /= ZOOM; sourceRect.w /= ZOOM; break; // zoom
                case SDLK_2     :                                                       sourceRect.h *= ZOOM; sourceRect.w *= ZOOM; break; // unzoom
            }
        }
        SDL_SetRenderTarget(renderer, nullptr); // draw onto the screen
        DrawCurrentGeneration();
        CreateNewGeneration();
        SDL_Delay(300); // short delay
    }
    return 0;
}
