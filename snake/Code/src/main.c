#include <raylib.h>
#include <stdlib.h>

#include "snake.h"
#include "game.h"
#include "food.h"
#include "macro.h"

int main(void)
{
    InitWindow(GAME_WIDTH, GAME_HEIGHT, "Snake Game Victor LIN");

    Game* game = InitGame();
    SetTargetFPS(60);
    while (!WindowShouldClose() && game->run == true)
    {  
        GameUpdate(game);

        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawGame(game);
        EndDrawing();
    }
    UnLoad(game);
    CloseWindow();
    return 0;
}