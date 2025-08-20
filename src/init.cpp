#include <init.h>
#include <global.h>

int InitImGui(){
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer); // initialise ImGui
    ImGui_ImplSDLRenderer2_Init(renderer);
    return 0;
}

int InitSDL(){
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL init error" << std::endl;
        return -1;
    }
    window = SDL_CreateWindow(
        "GUI lib",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_W,
        SCREEN_H,
        SDL_WINDOW_SHOWN
    );

    if(!window){
        std::cerr << "Window initialisation error" << std::endl;
        return -1;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(!renderer){
        std::cerr << "renderer initialisation error" << std::endl;
        return -1;
    }

    SDL_RendererInfo info;
    SDL_GetRendererInfo(renderer, &info);
    printf("Renderer name: %s\n", info.name);

    return 0;
}

void DestroyImGui(){
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void DestroySDL(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}