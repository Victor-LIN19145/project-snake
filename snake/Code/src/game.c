#include <stdlib.h>
#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>

#include "game.h"
#include "snake.h"
#include "food.h"
#include "macro.h"

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
    assets->gameImage[4] = LoadImage("Assets/gray_front.png");
    assets->gameImage[5] = LoadImage("Assets/red_front.png");
    assets->gameImage[6] = LoadImage("Assets/white_front.png");
    assets->gameImage[7] = LoadImage("Assets/apple.png");
    assets->gameImage[8] = LoadImage("Assets/tnt_active.png");
    assets->gameImage[9] = LoadImage("Assets/speed.png");
    
    for(int i=0; i<10; i++)
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
            DrawTexture(game->assets->gameTexture[4], i * 32, y * 32, WHITE);
}
void GameMenuScreen(Game* game)
{
    if (game->gameState == GAME_SCREEN)
    {
        if (IsKeyPressed('P'))
        game->pause = !game->pause;

        if (game->snake->speed > game->speed && !game->pause)
        {
            UpdateSnake(game->snake);
            game->snake->speed = 0;
        }
        SnakeMoveArrow(game->snake);
        SnakeMoveTouch(game->snake);
        game->snake->speed++;
        CheckAllFood(game);

        game->run = CheckBodyCollision(game);
        BorderCollision(game);

        if (!game->run)
            game->gameState = GAME_OVER;
    }
}

void GameMenuSettings(Game* game)
{
    if (game->gameState == GAME_SETTING)
    {
        if (IsKeyPressed(KEY_T))
            game->gameState = GAME_MENU;

        if (IsKeyPressed(KEY_DOWN)) game->gameSelection++;
        if (IsKeyPressed(KEY_UP)) game->gameSelection--;
        if (game->gameSelection > 3) game->gameSelection = 0;
        if (game->gameSelection < 0) game->gameSelection = 3;
        
        if (IsKeyPressed(KEY_ENTER))
        {
            if (game->gameSelection == 0)
                printf("800 x 450\n");
            else if (game->gameSelection == 1)
                printf("1280 x 960\n");
            else if (game->gameSelection == 2)
                printf("1920 x 1080\n");
            else if (game->gameSelection == 3)
                printf("2560 x 1600\n");
        }
    }
}
void GameMenuExit(Game* game)
{
    if (game->gameState == GAME_EXIT)
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            UnLoad(game);
            game->run = false;
        }
    }
}
void GameMenuOver(Game* game)
{
    if (game->gameState == GAME_OVER)
    {
        if (IsKeyPressed(KEY_R))
        {
            game->snake = InitSnake();
            InitFood(game);
            game->score = 0;
            game->speed = 6;
            game->run = true;
            game->gameState = GAME_SCREEN;
        }
        if (IsKeyPressed(KEY_ENTER))
            game->gameState = GAME_MENU;
    }
}
void GameMenu(Game* game)
{
    GameMenuScreen(game);
    GameMenuSettings(game);
    GameMenuExit(game);
    GameMenuOver(game);
}

void GameSelectMenu(Game* game)
{
    if (IsKeyPressed(KEY_ENTER))
        {
            if (game->gameSelection == 0)
            {
                game->snake = InitSnake();
                InitFood(game);
                game->score = 0;
                game->speed = 6;
                game->run = true;
                game->gameState = GAME_SCREEN;
            }
            else if (game->gameSelection == 1)
                game->gameState = GAME_SETTING;
            else if (game->gameSelection == 2)
                game->gameState = GAME_EXIT;
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
        
        GameSelectMenu(game);
    }
    GameMenu(game);
}

void DrawGameMenu(Game* game)
{
    if (game->gameState == GAME_MENU)
    {
        for (int i = 0; i < 40; i++)
            for(int y = 0; y < 30; y++)
                DrawTexture(game->assets->gameTexture[6], i * 32, y * 32, WHITE);
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
}

void DrawGameScreen(Game* game)
{
    if (game->gameState == GAME_SCREEN)
    {
    DrawGameGrid(game);
    DrawSnake(game);
    DrawFood(game);
    DrawText(TextFormat("Score : %d", game->score), 64, 672, 32, WHITE);

    Color pauseColor = (game->pause) ? GREEN : RED;
    DrawText("GAME PAUSED", 64, 736, 32, pauseColor);

    Color tntColor = (game->score >= 10) ? GREEN : RED;
    DrawText("TNT", 64, 800, 32, tntColor);

    DrawTexture(game->assets->gameTexture[7], 256, 672, WHITE);
    }
}
void DrawGameSetting(Game* game)
{
    if (game->gameState == GAME_SETTING)
    {
        for (int i = 0; i < 40; i++)
            for(int y = 0; y < 30; y++)
                DrawTexture(game->assets->gameTexture[6], i * 32, y * 32, WHITE);
        DrawText("Press 'T' to return menu", 10, 928, 32, BLACK);

        DrawText("800 x 450",
            GAME_WIDTH / 2 - MeasureText("800 x 450", 60) / 2,
                120, 60, (game->gameSelection == 0) ? RED : BLACK);
        DrawText("1280 x 960",
            GAME_WIDTH / 2 - MeasureText("1280 x 960", 60) / 2,
                240, 60, (game->gameSelection == 1) ? RED : BLACK);
        DrawText("1920 x 1080",
            GAME_WIDTH / 2 - MeasureText("1920 x 1080", 60) / 2,
                360, 60, (game->gameSelection == 2) ? RED : BLACK);
        DrawText("2560 x 1600",
            GAME_WIDTH / 2 - MeasureText("2560 x 1600", 60) / 2,
                480, 60, (game->gameSelection == 3) ? RED : BLACK);
    }
}
void DrawGameOver(Game* game)
{
    if (game->gameState == GAME_OVER)
    {
        for (int i = 0; i < 40; i++)
            for(int y = 0; y < 30; y++)
                DrawTexture(game->assets->gameTexture[5], i * 32, y * 32, WHITE);

        DrawText("Press 'R' to restart game", 10, 896, 32, BLACK);
        DrawText("Press 'ENTER' to return menu", 10, 928, 32, BLACK);
    }
}
void DrawGame(Game* game)
{
    DrawGameScreen(game);
    DrawGameMenu(game);
    DrawGameSetting(game);
    DrawGameOver(game);
}

void UnLoad(Game* game)
{
    for (int i = 0; i< 10; i++)
    {
        UnloadImage(game->assets->gameImage[i]);
        UnloadTexture(game->assets->gameTexture[i]);
    }
    free(game->assets);
    SnakeDestroy(&game->snake);
    free(game->food[0]);
    free(game->food[1]);
    free(game->food[2]);
    free(game);
}