#include <stddef.h>
#include <stdlib.h>

#include "snake.h"
#include "game.h"

Game* CreateGame()
{
    Game* createGame = calloc(1, sizeof(Game));

    createGame->gridTexture = LoadTexture(GRID_TEXTURE);

    return createGame;
}

Game* CreatePlayer()
{
    Game* createPlayer = calloc(1, sizeof(Game));

    return createPlayer;
}

Game* CreateApple(Game* game)
{
    Game* createApple = calloc(1, sizeof(Apple));

    int x = GetRandomValue(0, X_CASES);
    int y = GetRandomValue(0, Y_CASES);

    game->apple->pos = (Vector2){ x * SLOT_SIZE, y * SLOT_SIZE };
    game->score++;

    return createApple;
}

void AppleUpdate(Game* game)
{
    Apple* createApple = calloc(1, sizeof(Apple));
    if (createApple == NULL)
        return;
    
    int x = GetRandomValue(0, X_CASES);
    int y = GetRandomValue(0, Y_CASES);

    game->apple->pos = (Vector2){ x * SLOT_SIZE, y * SLOT_SIZE };
    game->score++;
}

void DrawApple(Game* game)
{
    DrawTexture(game->gridTexture, 0, 0, WHITE);
}

void InitGame(Game* game)
{
    game->gridTexture = LoadTexture(GRID_TEXTURE);
    game->isPaused = false;
    game->score = 0;
    //game->apple = CreateApple();
    InitApple(game->apple);
}

void DrawGameGrid(Texture2D gridTexture)
{
    for (int i = 0; i < X_CASES; i += SLOT_SIZE)
    {
        for (int j = 0; j < Y_CASES; j += SLOT_SIZE)
        {
            DrawTexture(gridTexture, i, j, WHITE);
        }
    }
}

/*
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