#include "raylib.h"
#include "raymath.h"
#include "helpers/draw.h"
#include "ui/Button.h"
#include <list>
#include <iostream>
#include <time.h>
#include <filesystem>
#include "Managers/GameLoop.h"
#include "Managers/GameState.h"
#include "UI/ViewMenu.h"


int main(void)
{
    GameLoop loop;
    GameState* game = GameState::GetInstance();

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // logic
        game->Update();

        // draw
        loop.DrawBegin();
        game->Draw();
        loop.DrawEnd();
    }

    delete game;

    return 0;
}