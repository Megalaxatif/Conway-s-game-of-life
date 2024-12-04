#include <SDL/SDL.h>
#include <iostream>
#include "header/textures.h"

#undef main

int main(int argc, char* argv[]) {

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Init(SDL_INIT_VIDEO);

    bool running = true;
    SDL_Event event;
    SDL_Rect rectangle{10, 10, 255, 255};

    SDL_CreateWindowAndRenderer(640*2, 480*2, 0, &window, &renderer);
    SDL_RenderSetScale(renderer,1, 1);


    // main loop
    while (running){
        // input handler
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) running = false;
        else if (event.type == SDL_KEYDOWN){
            switch (event.key.keysym.sym){
                case SDLK_RIGHT:
                    std::cout << "right" << "\n";
                    rectangle.x +=10;
                break;
                case SDLK_LEFT:
                    std::cout << "left" << "\n";
                    rectangle.x -=10;
                break;
                case SDLK_UP:
                    std::cout << "up" << "\n";
                    red_texture(renderer); // if we press the up key we display a red texture on the screen for 5 seconds
                break;
            }
        }
        else if (event.type==SDL_MOUSEMOTION){
            SDL_GetMouseState(&rectangle.x, &rectangle.y); 
        }
        // clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // display the rectangle
        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
        SDL_RenderFillRect(renderer, &rectangle);
        SDL_RenderPresent(renderer);  // display function
    }
    return 0;
}
