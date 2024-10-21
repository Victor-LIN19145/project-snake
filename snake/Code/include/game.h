#ifndef __GAME__
#define __GAME__

#include <stdbool.h>
#include <raylib.h>

typedef struct SSnake Snake;
typedef struct SFood Food;

typedef struct SImages
{
    Image gameImage[10];
    Texture2D gameTexture[10];
}Images;

typedef enum GameScreen
{
    GAME_MENU,
    GAME_SETTING,
    GAME_EXIT,
    GAME_OVER,

    GAME_SCREEN

} GameState;

typedef struct SGame {    
    Snake *snake;
    Images *assets;
    int speed;
    int score;
    Food* food[10];
    bool run;
    bool pause;

    GameState gameState;
    int gameSelection;
}Game;

Game* InitGame();
void LoadImages(Game* game);
void DrawGameGrid(Game* game);
void GameMenuScreen(Game* game);
void GameMenuSettings(Game* game);
void GameMenuExit(Game* game);
void GameMenuOver(Game* game);
void GameMenu(Game* game);
void GameSelectMenu(Game* game);
void GameUpdate(Game* game);
void DrawGameMenu(Game* game);
void DrawGameSetting(Game* game);
void DrawGameOver(Game* game);
void DrawGame(Game* game);
void UnLoad(Game* game);
#endif  