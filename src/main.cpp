#include <game-of-life.h>
#include <input.h>
#include <init.h>
#include <global.h>
#include <imgui-windows.h>

#undef main

int main(int argc, char* argv[]) {
    // SDL and ImGui
    if(InitSDL() == -1) return -1;
    if(InitImGui() == -1) return -1;

    // Game of life
    GameOfLifeInit();
    CreateGameOfLifeTexture();

    auto start = std::chrono::high_resolution_clock::now();
    
    // main loop
    while (running){
        InputHandler();                 // input handler

        if (generating){                // automatic generation
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            // fix the speed between the generations
            if (elapsed.count() >= delay){
                start = std::chrono::high_resolution_clock::now();
                CreateNewGenArray();    // create the array
                CreateNewGenTexture();  // create the texture based on the data in the array
            }
        }
        else if (step){                 // step generation
            CreateNewGenArray();        // create the array
            CreateNewGenTexture();      // create the texture based on the data in the array
            step = false;
        }

        StartImGuiWindowCreation();     // start creating the windows

        CreateImGuiWindow1();           // generation settings management window
        CreateImGuiWindow2();           // cell color  management window

        EndImGuiWindowCreation();       // We can't create additional windows after this

        DisplayNewGenTextureAndImGui(); // final draw call that displays the texture along with ImGui

        SDL_Delay(5);                   // little delay not to burn the cpu ;)
    }
    DestroyImGui();
    DestroySDL();
    return 0;
}
