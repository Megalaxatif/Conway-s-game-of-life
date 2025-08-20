#include <global.h>
#include <input.h>
#include <imgui_impl_sdl2.h>         // backend

SDL_Event event;
int MouseX, MouseY, newMouseX, newMouseY; // mouse coordinates
bool leftButtonDown  = false; // the left button is initially not pressed
bool isMouseDragging = false;// set on true is the mouse is moving

void InputHandler(){
    SDL_PollEvent(&event);
    ImGui_ImplSDL2_ProcessEvent(&event); // send the event to imgui (really important)
    if (event.type == SDL_QUIT) running = false;

    else if (event.type == SDL_KEYDOWN){
        switch (event.key.keysym.sym){
            case SDLK_RIGHT     : if(sourceRect.x + SPEED + sourceRect.w <= TEXTURE_W)  sourceRect.x += SPEED;                                   break;
            case SDLK_LEFT      : if(sourceRect.x - SPEED >= 0)                         sourceRect.x -= SPEED;                                   break;
            case SDLK_UP        : if(sourceRect.y - SPEED >= 0)                         sourceRect.y -= SPEED;                                   break;
            case SDLK_DOWN      : if(sourceRect.y + SPEED + sourceRect.h <= TEXTURE_H)  sourceRect.y += SPEED;                                   break;
            case SDLK_r         :                                                       GameOfLifeInit();                                        break; // reset the seed
            case SDLK_KP_PLUS   : if (delay + DELAY <= DELAY_MAX)                       delay += DELAY; std::cout << "delay: " << delay << "\n"; break; // slow down the generation
            case SDLK_KP_MINUS  : if (delay - DELAY >= 0)                               delay -= DELAY; std::cout << "delay: " << delay << "\n"; break; // accelerate the generation
            case SDLK_RETURN    :                                                       generating = !generating;                                break; // pause the game or unpause it 
        }
    }
    else if (event.type == SDL_MOUSEBUTTONUP){
        if (event.button.button == SDL_BUTTON_LEFT) {         
            leftButtonDown = false;             // left button released

            if(!isMouseDragging){               // we don't draw a cell unless the mouse isn't dragging
                float cursorX = float(event.button.x)/SCREEN_W * sourceRect.w + sourceRect.x;
                float cursorY = float(event.button.y)/SCREEN_H * sourceRect.h + sourceRect.y;
                DrawCell(cursorX, cursorY);     // draw a cell
            }
            isMouseDragging = false;            // the mouse isn't dragging anymore because we released the left button
        }
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN){
        if (event.button.button == SDL_BUTTON_LEFT) {
            SDL_GetMouseState(&MouseX, &MouseY);                        // retrieve the position of the mouse
            leftButtonDown = true;
        }
    }
    else if (event.type == SDL_MOUSEMOTION && leftButtonDown) {
        isMouseDragging = true;                                         // the mouse is now dragging because we press the left button while we are moving it
        SDL_GetMouseState(&newMouseX, &newMouseY);                      // retrieve the position of the mouse
        printf("Position de la souris: x=%d, y=%d\n", newMouseX, newMouseY);
        int deltaMouseX = newMouseX - MouseX;
        int deltaMouseY = newMouseY - MouseY;

        if (sourceRect.x + deltaMouseX + sourceRect.w <= TEXTURE_W && sourceRect.x + deltaMouseX > 0) sourceRect.x += deltaMouseX /10;            // move the source rect on the x axis
        if (sourceRect.y + deltaMouseY + sourceRect.h <= TEXTURE_H && sourceRect.y + deltaMouseY > 0) sourceRect.y += deltaMouseY /10;            // move the source rect on the y axis
    }
    else if (event.type == SDL_MOUSEWHEEL) {
        if(event.wheel.y > 0 && sourceRect.h > ZOOM && sourceRect.w > ZOOM) {                   // zoom in
            sourceRect.h -= ZOOM;
            sourceRect.w -= ZOOM;
        } 
        else if (event.wheel.y < 0 && sourceRect.h < TEXTURE_H && sourceRect.w < TEXTURE_W) {   // zoom out
            if (sourceRect.h + sourceRect.y + ZOOM > TEXTURE_H) {                               // the sourceRect is exceeding the height of the Texture
                sourceRect.y -= ZOOM;
            }
            if (sourceRect.w + sourceRect.x + ZOOM > TEXTURE_W){                                // the sourceRect is exceeding the width of the Texture
                sourceRect.x -= ZOOM;
            }
            sourceRect.h += ZOOM;
            sourceRect.w += ZOOM;
        }
    }
}