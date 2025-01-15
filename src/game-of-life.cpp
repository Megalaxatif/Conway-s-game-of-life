#include <global.h>
#include <game-of-life.h>
#include <imgui_impl_sdlrenderer2.h> // backend
#include <random>

SDL_Texture* gameOfLifeTexture = nullptr;
SDL_Rect sourceRect {0, 0, TEXTURE_W, TEXTURE_H};
SDL_Rect destRect {10, 10, SCREEN_W -20, SCREEN_H -20};

short int currentGen_a[TEXTURE_W][TEXTURE_H] = { 0 };
float cellColor_a[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

void GameOfLifeInit(){
    srand(time(nullptr));
    for(int y=0; y < TEXTURE_H; y++){
        for(int x=0; x < TEXTURE_W; x++){
            currentGen_a[y][x] = 0;                                        // first we reset the current array
        }
    }
    for (int i = 0; i < CELL_INIT; i++){
        currentGen_a[rand() % TEXTURE_H][rand() % TEXTURE_W]= ALIVE_CELL;  // then we draw a bunch of random cell to create a new seed
    }
}

void DrawCell(int x, int y){
    if(currentGen_a[y][x] == ALIVE_CELL) currentGen_a[y][x] = 0;
    else currentGen_a[y][x] = ALIVE_CELL;
}

void CreateGameOfLifeTexture(){
    gameOfLifeTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, TEXTURE_W, TEXTURE_H);
}

bool isAlive(int x, int y){
    int alive_cells = 0;

    if (x-1 >=0)                                { if (currentGen_a[y][x-1]   == ALIVE_CELL) alive_cells ++; } // left
    if (x+1 <= TEXTURE_W)                       { if (currentGen_a[y][x+1]   == ALIVE_CELL) alive_cells ++; } // right
    if (y-1 >=0)                                { if (currentGen_a[y-1][x]   == ALIVE_CELL) alive_cells ++; } // top
    if (y+1 <= TEXTURE_H)                       { if (currentGen_a[y+1][x]   == ALIVE_CELL) alive_cells ++; } // bottom
    if (y-1 >=0 && x-1 >=0)                     { if (currentGen_a[y-1][x-1] == ALIVE_CELL) alive_cells ++; } // top left
    if (y+1 <= TEXTURE_H && x+1 <= TEXTURE_W)   { if (currentGen_a[y+1][x+1] == ALIVE_CELL) alive_cells ++; } // bottom right
    if (y-1 >=0 && x+1 <= TEXTURE_W)            { if (currentGen_a[y-1][x+1] == ALIVE_CELL) alive_cells ++; } // top right
    if (y+1 <= TEXTURE_H && x-1>=0)             { if (currentGen_a[y+1][x-1] == ALIVE_CELL) alive_cells ++; } // bottom left

    if (currentGen_a[y][x] == 0){
        if (alive_cells == 3) return true;
        return false;
    }
    else if (currentGen_a[y][x] == ALIVE_CELL){
        if(alive_cells == 2 || alive_cells == 3) return true;
        return false;
    }
    return false; // error, the number tested neither represent a living cell or a dead one
}

void CreateNewGenArray(){
    int new_array[TEXTURE_W][TEXTURE_H] = { 0 };
    // look inside the current array for every living cell and copy paste them into new_array
    for(int y=0; y < TEXTURE_H; y++){
        for(int x=0; x < TEXTURE_W; x++){
            if (isAlive(x,y)) new_array[y][x] = ALIVE_CELL;
        }
    }
    // copy new_array in current_a
    for(int y=0; y < TEXTURE_H; y++){
        for(int x=0; x < TEXTURE_W; x++){
            currentGen_a[y][x] = new_array[y][x];
        }
    }
}

void CreateNewGenTexture(){
    SDL_SetRenderTarget(renderer, gameOfLifeTexture);       // we draw on GameOfLifeTexture
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);   // we clear the screen in white
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, int(cellColor_a[0]*255), int(cellColor_a[1]*255), int(cellColor_a[2]*255), int(cellColor_a[3]*255));   // we draw the cells with the color defined in cellColor_a
    for(int y=0; y < TEXTURE_H; y++){
        for(int x=0; x < TEXTURE_W; x++){
            if (currentGen_a[y][x] == ALIVE_CELL) SDL_RenderDrawPoint(renderer, x, y);
        }
    }
    SDL_SetRenderTarget(renderer, nullptr); // for the imGui interface
}

void DrawNewGenArray(){
    for(int y=0; y < TEXTURE_H; y++){
        for(int x=0; x < TEXTURE_W; x++){
           printf("%i", currentGen_a [y][x]);
        }
        printf("\n");
    }
    printf("\n");
}

void DisplayNewGenTextureAndImGui(){
    // texture
    SDL_SetRenderTarget(renderer, nullptr);
    SDL_RenderCopy(renderer, gameOfLifeTexture, &sourceRect, &destRect);

    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);      // display imgui

    SDL_RenderPresent(renderer);
}