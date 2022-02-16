#include "GameLoop.h"

#include "Managers/GameState.h"
#include <iostream>
#include <time.h>


GameLoop::GameLoop()
{
    InitWindow(GameState::screenWidth, GameState::screenHeight, "Raylib RTS");

    SetTargetFPS(60);               // Set our game to run at X frames-per-second

    srand(time(NULL));				// init random
}

void GameLoop::DrawBegin()
{
	BeginDrawing();
	ClearBackground(BEIGE);
}

void GameLoop::DrawEnd()
{
	EndDrawing();
}

GameLoop::~GameLoop()
{
	CloseWindow();        // Close window and OpenGL context

}