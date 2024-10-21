#ifndef __GAME__
#define __GAME__

#include <raylib.h>

#include "snake.h"

#define GRID_TEXTURE "./Assets/apple.png"
#define APPLE_TEXTURE "./Assets/grid_tile.png"

typedef struct SGame
{
    //
}Game;

typedef struct SApple
{
    Vector2 pos;
    Texture2D texture;
}Apple;


//Game* CreateGame();

//void InitGame(Game* game);

//void UpdateGame(Game* game);

//void DrawGrid(Game* game);

void DrawApple(Apple* apple);

#endif