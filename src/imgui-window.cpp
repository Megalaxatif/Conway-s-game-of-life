#include <imgui-windows.h>
#include <game-of-life.h>

void StartImGuiWindowCreation(){
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}
void EndImGuiWindowCreation(){
    ImGui::Render();
}

void CreateImGuiWindow1(){
    ImGui::Begin("Generation Settings");
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
    ImGui::End();
}
void CreateImGuiWindow2(){
    ImGui::Begin("Cell Color Settings");
    ImGui::SetWindowSize(ImVec2(300, 300));

    ImGui::ColorPicker4("Cell color", cellColor_a);

    ImGui::End();
}
