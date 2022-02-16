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
#include "UI/ViewMenu.h";


int main(void)
{
    GameLoop loop;
    GameState* game = GameState::GetInstance();

    //Snake snake({ 100, 100 }, { +1, 0 }, 10, 5);
    
    //Button testbutton(game->images.at("button"), "testin!", { 200.0,200.0 }, 5);

    //Vector2 apple = RandomPos(loop.screenWidth, loop.screenHeight);
    //bool gameOver = false;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        /*
        // Controls
        //----------------------------------------------------------------------------------
        if (IsKeyDown(KEY_RIGHT)) snake.ChangeDirection({ +1,0 });
        if (IsKeyDown(KEY_LEFT)) snake.ChangeDirection({ -1,0 });
        if (IsKeyDown(KEY_UP)) snake.ChangeDirection({ 0,-1 });
        if (IsKeyDown(KEY_DOWN)) snake.ChangeDirection({ 0,+1 });

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mousePoint = GetMousePosition();
            if (testbutton.TryPress(mousePoint)) {
                snake.dead = !snake.dead;
            }
        }
        //----------------------------------------------------------------------------------
        */

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