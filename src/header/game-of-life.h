#pragma once
#include <ctime>
#include <chrono>
#include <iostream>
#include <global.h>

void CreateGameOfLifeTexture();         // create gameOfLiveTexture
bool isAlive(int x, int y);             // look around given cell in currentGen_a and make sure that we don't try to access data beyond the borders of that array
void CreateNewGenArray();               // creates an array representing the configuration of each cells in the new generation
void CreateNewGenTexture();             // draw one pixel on the texture on the position of each cell in currentGen_a
void DisplayNewGenTextureAndImGui();    // display GameOfLifeTexture and the ImGui windows
void ClearCurrentGenerationArray();     // set all the cells in the array as dead cells
void GameOfLifeInit();                  // initialise the game by reseting currentGen_a and drawing random points on it
void DrawCell(int x, int y);            // allows the user to draw or erase cells in currentGen_a
void DrawNewGenArray();                 // display currentGen_a for debuging purpose
