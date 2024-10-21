#ifndef __GAME__
#define __GAME__

#include <raylib.h>

#include "snake.h"

#define X_CASES 1280
#define Y_CASES 960
#define SLOT_SIZE 32

#define GRID_TEXTURE "./Assets/grid_tile.png"
#define APPLE_TEXTURE "./Assets/apple.png"

typedef struct SPlayer
{
    //
}Player;

typedef struct SApple
{
    Vector2 pos;
}Apple;

typedef struct SGame
{
    Player* player;
    Apple* apple;

    //GameScreen gameScreen;
    int score;
    bool isGameOver;
    bool isPaused;

    Texture2D gridTexture;
}Game;

Game* CreateGame();

Game* CreatePlayer();

Game* CreateApple();

void InitGame(Game* game);

void UpdateGame(Game* game);

void AppleUpdate(Game* game);

void DrawGameGrid(Texture2D gridTexture);

void DrawGame(Game* game);

void DrawApple(Apple* apple);

#endif