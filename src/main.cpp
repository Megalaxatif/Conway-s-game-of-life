#include <SDL/SDL.h>
#include <iostream>
#include <game-of-life.h>
#include <input.h>
#undef main

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = nullptr;

    SDL_CreateWindowAndRenderer(SCREEN_W, SCREEN_H, 0, &window, &renderer);
    SDL_RenderSetScale(renderer, 1, 1);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // clear the screen
    SDL_RenderClear(renderer);

    GameOfLifeInit();
    CreateGameOfLifeTexture();

    // main loop
    auto start = std::chrono::high_resolution_clock::now();

    while (running){
        InputHandler(); // input handler

        if (generating){
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            // fix the speed between the generations
            if (elapsed.count() >= delay){
                start = std::chrono::high_resolution_clock::now();
                CreateNewGeneration();
                //DrawCurrentArray();
            }
        }
            DrawCurrentGeneration();
            SDL_Delay(5); // little delay not to burn the cpu ;)
    }
    return 0;
}
