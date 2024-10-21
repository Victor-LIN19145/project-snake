#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>

#include "snake.h"
#include "game.h"
#include "food.h"

/*
1	32
2	64
3	96
4	128
5	160
6	192
7	224
8	256
9	288
10	320
11	352
12	384
13	416
14	448
15	480
16	512
17	544
18	576
19	608
20	640
21	672
22	704
23	736
24	768
25	800
26	832
27	864
28	896
29	928
30	960
*/

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

