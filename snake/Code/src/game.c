#include <stdlib.h>
#include <raylib.h>
#include <time.h>
#include <stdbool.h>
#include <stdio.h>

#include "game.h"
#include "snake.h"
#include "food.h"



Game* InitGame()
{
    Game* game = calloc(1,sizeof(Game));

    game->score = 0;
    game->speed = 6;
    game->run = true;
    game->pause = false;
    LoadImages(game);
    game->snake = InitSnake();
    InitFood(game);

    game->gameState = GAME_MENU;
    game->gameSelection = 0;

    return game;
}

void LoadImages(Game* game)
{
    Images* assets = calloc(1,sizeof(Images));

    assets->gameImage[0] = LoadImage("Assets/snake_head.png");
    assets->gameImage[1] = LoadImage("Assets/snake_body.png");
    assets->gameImage[2] = LoadImage("Assets/snake_tail.png");
    assets->gameImage[3] = LoadImage("Assets/grid_tile.png");
    assets->gameImage[4] = LoadImage("Assets/apple.png");
    assets->gameImage[5] = LoadImage("Assets/gray_front.png");

    for(int i=0; i<6; i++)
    {
        ImageResize(&assets->gameImage[i], 32, 32);
        assets->gameTexture[i] = LoadTextureFromImage(assets->gameImage[i]);
    }

    game->assets = assets;
}

void DrawGameGrid(Game* game)
{
    for (int i = 0; i < 40; i++)
       for(int y = 0; y < 20; y++)
            DrawTexture(game->assets->gameTexture[3], i * 32, y * 32, WHITE);
    
    for (int i = 0; i < 40; i++)
       for(int y = 20; y < 30; y++)
            DrawTexture(game->assets->gameTexture[5], i * 32, y * 32, WHITE);
}

void GameMenu(Game* game)
{
    if (game->gameState == GAME_SCREEN)
    {
        if (IsKeyPressed('P')) game->pause = !game->pause;

        if (game->snake->speed > game->speed && !game->pause) {
            UpdateSnake(game->snake);
            game->snake->speed = 0;
        }
        SnakeMove(game->snake);
        game->snake->speed++;
        CheckAllFood(game);

        game->run = CheckBodyCollision(game);
        BorderCollision(game);

        if (!game->run)
            game->gameState = GAME_OVER;
    }
    if (game->gameState == GAME_SETTING)
    {
        if (IsKeyPressed(KEY_T))
            game->gameState = GAME_MENU;
    }
    if (game->gameState == GAME_EXIT)
    {
        if (IsKeyPressed(KEY_ENTER))
            game->run = false;
    }
    if (game->gameState == GAME_OVER)
    {
        if (IsKeyPressed(KEY_R))
        {
            game->snake = InitSnake();
            InitFood(game);
            game->score = 0;
            game->run = true;
            game->gameState = GAME_SCREEN;
        }
        if (IsKeyPressed(KEY_ENTER))
            game->gameState = GAME_MENU;
    }
}

void GameUpdate(Game* game)
{
    if (game->gameState == GAME_MENU)
    {
        if (IsKeyPressed(KEY_DOWN)) game->gameSelection++;
        if (IsKeyPressed(KEY_UP)) game->gameSelection--;
        if (game->gameSelection > 2) game->gameSelection = 0;
        if (game->gameSelection < 0) game->gameSelection = 2;
        
        if (IsKeyPressed(KEY_ENTER))
        {
            if (game->gameSelection == 0)
            {
                game->snake = InitSnake();
                InitFood(game);
                game->score = 0;
                game->run = true;
                game->gameState = GAME_SCREEN;
            }
            else if (game->gameSelection == 1)
                game->gameState = GAME_SETTING;
            else if (game->gameSelection == 2)
                game->gameState = GAME_EXIT;
        }
    }
    GameMenu(game);
}

void DrawGame(Game* game)
{
    if (game->gameState == GAME_MENU)
    {
        DrawText("Start",
            GAME_WIDTH / 2 - MeasureText("Start", 60) / 2,
                120, 60, (game->gameSelection == 0) ? RED : BLACK);
        DrawText("Settings",
            GAME_WIDTH / 2 - MeasureText("Settings", 60) / 2,
                240, 60, (game->gameSelection == 1) ? RED : BLACK);
        DrawText("Exit",
            GAME_WIDTH / 2 - MeasureText("Exit", 60) / 2,
                360, 60, (game->gameSelection == 2) ? RED : BLACK);
    }
    
    if (game->gameState == GAME_SCREEN)
    {
        DrawGameGrid(game);
        DrawSnake(game);
        DrawFood(game);
        DrawText(TextFormat("Score : %d", game->score, 32) , 64, 672, 32, WHITE);
        DrawTexture(game->assets->gameTexture[4], 256, 672, WHITE);
    }

    if (game->gameState == GAME_SETTING)
    {
        DrawText("Press 'T' to return menu",
            GAME_WIDTH / 2 - MeasureText("Press 'T' to return menu", 60) / 2,
                GAME_HEIGHT / 2, 60, (game->gameSelection == 0) ? RED : BLACK);
    }
}
void UnLoad(Game* game)
{
    for (int i = 0; i< 5; i++)
    {
        UnloadImage(game->assets->gameImage[i]);
        UnloadTexture(game->assets->gameTexture[i]);
    }
    free(game->assets);
    SnakeDestroy(&game->snake);
    free(game->food[0]);
    free(game);
}