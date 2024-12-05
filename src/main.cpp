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

    GameOfLifeInit();
    CreateGameOfLifeTexture();
    // main loop
    bool running = true;
    int delay = 100; // delay between each generation

    auto start = std::chrono::high_resolution_clock::now();

    while (running){
        // input handler
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) running = false;
        else if (event.type == SDL_KEYDOWN){
            switch (event.key.keysym.sym){
                case SDLK_RIGHT : if(sourceRect.x + SPEED + sourceRect.w <= TEXTURE_W)  sourceRect.x += SPEED;                                   break;
                case SDLK_LEFT  : if(sourceRect.x - SPEED >= 0)                         sourceRect.x -= SPEED;                                   break;
                case SDLK_UP    : if(sourceRect.y - SPEED >= 0)                         sourceRect.y -= SPEED;                                   break;
                case SDLK_DOWN  : if(sourceRect.y + SPEED + sourceRect.h <= TEXTURE_H)  sourceRect.y += SPEED;                                   break;
                case SDLK_1     :                                                       sourceRect.h /= ZOOM; sourceRect.w /= ZOOM;              break; // zoom
                case SDLK_2     :                                                       sourceRect.h *= ZOOM; sourceRect.w *= ZOOM;              break; // unzoom
                case SDLK_3     :                                                       GameOfLifeInit();                                        break; // reset the seed
                case SDLK_4     :                                                       delay += DELAY; std::cout << "delay: " << delay << "\n"; break;
                case SDLK_5     : if (delay - DELAY >= 0)                               delay -= DELAY; std::cout << "delay: " << delay << "\n"; break;
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        // fix the speed between the generations
        if (elapsed.count() >= delay){
            start = std::chrono::high_resolution_clock::now();
            CreateNewGeneration();
        }
            DrawCurrentGeneration();
            SDL_Delay(5); // little delay not to burn the cpu ;)
    }
    return 0;
}
