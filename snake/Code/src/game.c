#include <stddef.h>

#include "snake.h"
#include "game.h"

/*
Game* CreateGame()
{
    //
}
void DrawGrid(Game* game)
{
    for (int i = 0; i < 64; i++)
    {
        DrawRectangle(i * SLOT_SIZE, i * SLOT_SIZE, SLOT_SIZE, SLOT_SIZE, (i % 2 == 0) ? LIGHTGRAY : DARKGRAY);
    }
}

void UpdateGame(Game* game)
{
    if (IsKeyPressed('P'))
        game->paused = !game->paused;
}
*/

void DrawApple(Apple* apple)
{
    GetRandomValue(1280, 960);

}