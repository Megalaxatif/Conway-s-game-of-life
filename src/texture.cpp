#include <SDL/SDL.h>
#include "header/textures.h"

void red_texture(SDL_Renderer* renderer){

    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1000, 1000); // creation of the texture
    SDL_SetRenderTarget(renderer, texture);             // now we draw on the texture
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);   // we set the color on red
    SDL_RenderClear(renderer);                          // we clear the texture with red so that it's completely red

    SDL_SetRenderTarget(renderer, nullptr);             // now we draw directly on the window as before
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);// we copy the texture to our screen
    SDL_RenderPresent(renderer);                        // display the final result
    
    SDL_Delay(5000);                                    // we wait 5 seconds
    SDL_DestroyTexture(texture);                        // destroy the texture because we don't need it anymore
}