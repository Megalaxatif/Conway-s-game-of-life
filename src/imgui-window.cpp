#include <imgui-windows.h>
#include <game-of-life.h>

void StartImGuiWindowCreation(){
    SDL_SetRenderTarget(renderer, nullptr); // make sure we draw on the screen for the imGui interface otherwise there will be an error
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}
void EndImGuiWindowCreation(){
    ImGui::Render();
}

void CreateImGuiWindow1(){
    ImGui::Begin("Generation Settings");
    ImGui::SetWindowSize(ImVec2(225, 160));
    ImGui::Text("Generation delay slider");
    ImGui::SliderInt("##slider1", &delay, 0, DELAY_MAX);
    ImGui::Dummy(ImVec2(0.0f, 5.0f));

    if(ImGui::Button("pause button", ImVec2(100, 30))){
        generating = !generating;
    }
    ImGui::SameLine();
    
    if(ImGui::Button("reset button", ImVec2(100, 30))){
        GameOfLifeInit();   // reset the seed
    }
    if(ImGui::Button("clear button", ImVec2(100, 30))){
        ClearCurrentGenerationArray();   // reset the seed
    }
    ImGui::End();
}

void CreateImGuiWindow2(){
    ImGui::Begin("Cell Color Settings");
    ImGui::SetWindowSize(ImVec2(300, 300));

    ImGui::ColorPicker4("Cell color", aliveCellColor_a);

    ImGui::End();
}
