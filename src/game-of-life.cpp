#include <global.h>
#include <game-of-life.h>
#include <imgui_impl_sdlrenderer2.h> // backend
#include <random>

short int currentGeneration_a[TEXTURE_W][TEXTURE_H] = { 0 };

void GameOfLifeInit(){
    srand(time(nullptr));
    ClearCurrentGenerationArray();
    for (int i = 0; i < CELL_INIT; i++){
        currentGeneration_a[rand() % TEXTURE_H][rand() % TEXTURE_W]= ALIVE_CELL;  // then we draw a bunch of random cell to create a new seed
    }
}

void ClearCurrentGenerationArray(){
    for (int y=0; y < TEXTURE_H; y++){
        for(int x=0; x < TEXTURE_W; x++){
            currentGeneration_a[y][x] = 0;                                        // first we reset the current array
        }
    }
    CreateNewGenTexture(); // update the texture so that we can see the change
}

void DrawCell(int x, int y){
    SDL_SetRenderTarget(renderer, gameOfLifeTexture);
    if (currentGeneration_a[y][x] == ALIVE_CELL) { // if the cell was alive, it dies
        currentGeneration_a[y][x] = 0;
        SDL_SetRenderDrawColor(renderer, deadCellColor_a[0]*255, deadCellColor_a[0]*255, deadCellColor_a[0]*255, 255);
        SDL_RenderDrawPoint(renderer, x, y); // draw a point on the texture so that we can see the change
    }
    else {                                        // otherwise the cell was dead so it becomes alive
         currentGeneration_a[y][x] = ALIVE_CELL;
         SDL_SetRenderDrawColor(renderer, int(aliveCellColor_a[0]*255), int(aliveCellColor_a[1]*255), int(aliveCellColor_a[2]*255), int(aliveCellColor_a[3]*255));   // we draw the cells with the color defined in cellColor_a
         SDL_RenderDrawPoint(renderer, x, y); // draw a point on the texture so that we can see the change
    }
}

void CreateGameOfLifeTexture(){
    gameOfLifeTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, TEXTURE_W, TEXTURE_H);
}

bool isAlive(int x, int y){
    int alive_cells = 0;

    if (x-1 >=0)                                { if (currentGeneration_a[y][x-1]   == ALIVE_CELL) alive_cells ++; } // left
    if (x+1 <= TEXTURE_W)                       { if (currentGeneration_a[y][x+1]   == ALIVE_CELL) alive_cells ++; } // right
    if (y-1 >=0)                                { if (currentGeneration_a[y-1][x]   == ALIVE_CELL) alive_cells ++; } // top
    if (y+1 <= TEXTURE_H)                       { if (currentGeneration_a[y+1][x]   == ALIVE_CELL) alive_cells ++; } // bottom
    if (y-1 >=0 && x-1 >=0)                     { if (currentGeneration_a[y-1][x-1] == ALIVE_CELL) alive_cells ++; } // top left
    if (y+1 <= TEXTURE_H && x+1 <= TEXTURE_W)   { if (currentGeneration_a[y+1][x+1] == ALIVE_CELL) alive_cells ++; } // bottom right
    if (y-1 >=0 && x+1 <= TEXTURE_W)            { if (currentGeneration_a[y-1][x+1] == ALIVE_CELL) alive_cells ++; } // top right
    if (y+1 <= TEXTURE_H && x-1>=0)             { if (currentGeneration_a[y+1][x-1] == ALIVE_CELL) alive_cells ++; } // bottom left

    if (currentGeneration_a[y][x] == 0){
        if (alive_cells == 3) return true;
        return false;
    }
    else if (currentGeneration_a[y][x] == ALIVE_CELL){
        if (alive_cells == 2 || alive_cells == 3) return true;
        return false;
    }
    return false; // error, the number tested neither represent a living cell or a dead one
}

void CreateNewGenArray(){
    int new_array[TEXTURE_W][TEXTURE_H] = { 0 };
    // look inside the current array for every living cell and copy paste them into new_array
    for (int y=0; y < TEXTURE_H; y++){
        for (int x=0; x < TEXTURE_W; x++){
            if (isAlive(x,y)) new_array[y][x] = ALIVE_CELL;
        }
    }
    // copy new_array in current_a
    for (int y=0; y < TEXTURE_H; y++){
        for (int x=0; x < TEXTURE_W; x++){
            currentGeneration_a[y][x] = new_array[y][x];
        }
    }
}

void CreateNewGenTexture(){
    SDL_SetRenderTarget(renderer, gameOfLifeTexture);       // we draw on GameOfLifeTexture
    SDL_SetRenderDrawColor(renderer, deadCellColor_a[0]*255, deadCellColor_a[0]*255, deadCellColor_a[0]*255, 255);   // we clear the screen with the dead cell color
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, int(aliveCellColor_a[0]*255), int(aliveCellColor_a[1]*255), int(aliveCellColor_a[2]*255), int(aliveCellColor_a[3]*255));   // we draw the cells with the color defined in cellColor_a
    for (int y=0; y < TEXTURE_H; y++){
        for (int x=0; x < TEXTURE_W; x++){
            if (currentGeneration_a[y][x] == ALIVE_CELL) SDL_RenderDrawPoint(renderer, x, y);
        }
    }
}

void DrawNewGenArray(){
    for (int y=0; y < TEXTURE_H; y++){
        for (int x=0; x < TEXTURE_W; x++){
           printf("%i", currentGeneration_a [y][x]);
        }
        printf("\n");
    }
    printf("\n");
}

void DisplayNewGenTextureAndImGui(){
    // texture
    SDL_SetRenderTarget(renderer, nullptr); // we draw on the screen
    SDL_RenderCopy(renderer, gameOfLifeTexture, &sourceRect, &destRect);
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);      // display imgui
    SDL_RenderPresent(renderer);
}