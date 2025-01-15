#pragma once
#include <SDL/SDL.h>
#include <imgui.h>
#include <imgui_impl_sdl2.h>         // backend
#include <imgui_impl_sdlrenderer2.h> // backend

int InitImGui();
int InitSDL();
void DestroyImGui();
void DestroySDL();