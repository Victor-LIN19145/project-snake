#ifndef __GAME__
#define __GAME__

#include <stdbool.h>
#include <raylib.h>

#define GAME_WIDTH 1280
#define GAME_HEIGHT 960

typedef struct SSnake Snake;
typedef struct SFood Food;

typedef struct SImages {
    Image gameImage[7];
    Texture2D gameTexture[7];
}Images;

typedef enum GameScreen
{
    GAME_MENU,
    GAME_SCREEN,
    GAME_SETTING,
    GAME_EXIT,
    GAME_OVER
} GameState;

typedef struct SGame {    
    Snake *snake;
    Images *assets;
    int speed;
    int score;
    Food* food[4];
    bool run;
    bool pause;

    GameState gameState;
    int gameSelection;
}Game;

Game* InitGame();
void LoadImages(Game* game);
void DrawGameGrid(Game* game);
void GameMenu(Game* game);
void GameUpdate(Game* game);
void DrawGame(Game* game);
void UnLoad(Game* game);
#endif  