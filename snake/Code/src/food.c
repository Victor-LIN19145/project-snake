#include <stdlib.h>
#include <stddef.h>
#include <raylib.h>

#include "game.h"
#include "snake.h"
#include "food.h"
#include "macro.h"

Food* CreateFood(int id)
{
    Food* food = calloc(1,sizeof(Food));
    food->id = id; 
    food->placed = false;
    
    if(id == 0) food->placed = true;

    int x = GetRandomValue(0, 39);
    int y = GetRandomValue(0, 19);

    food->position = (Vector2){x * 32, y * 32};
    return food;
}

void UpdateFood(Food* food)
{
    int x = GetRandomValue(0, 31);
    int y = GetRandomValue(0, 19);

    food->position = (Vector2){x * 32, y * 32};
}

void InitFood(Game* game)
{
    game->food[0] = CreateFood(0);
    game->food[1] = CreateFood(1);
    game->food[2] = CreateFood(2);
}

void DrawFood(Game* game)
{
    if (game->food[0] != NULL)
    {
        DrawTexture(game->assets->gameTexture[7],
            game->food[0]->position.x,
                game->food[0]->position.y,
                    WHITE);

        DrawTexture(game->assets->gameTexture[8],
            game->food[1]->position.x,
                game->food[1]->position.y,
                    WHITE);
        DrawTexture(game->assets->gameTexture[9],
            game->food[2]->position.x,
                game->food[2]->position.y,
                    WHITE);
    }
}

bool CheckCollisionWithFoodHead(Snake* snake, Food* food)
{
    return (snake->head->position.x ==
        food->position.x && snake->head->position.y ==
            food->position.y);
}

bool CheckCollisionWithFoodTail(Snake* snake, Food* food)
{
    return (snake->tail->position.x ==
        food->position.x && snake->tail->position.y
            == food->position.y);
}

bool CheckCollisionWithFoodBody(Game* game, Food* food)
{
    for (Segment* current = game->snake->head->next;
        current != NULL;
            current = current->next)
    {
        if (current->position.x == food->position.x
            && current->position.y == food->position.y) 
                return false;
    }
    return true;
    
    Segment *bodySegment = calloc(1,sizeof(Segment));
    InitSegment(bodySegment,game->snake->tail);
    return (game->snake->tail->position.x ==
        food->position.x && game->snake->tail->position.y
            == food->position.y);
}

void CheckAllFood(Game* game)
{
    for (int i = 0; i < 3; i++)
    {
        if (CheckCollisionWithFoodHead(game->snake, game->food[i]))
        {
            switch (i)
            {
                case 0:
                    AddSegment(game);
                    UpdateFood(game->food[0]);
                    game->score++;
                    break;
                case 1:
                    if (game->score >= 10)
                        game->gameState = GAME_OVER;
                    break;
                case 2:
                    UpdateFood(game->food[2]);
                    game->speed--;
                    break;
                default:
                    break;
            }

            if(CheckCollisionWithFoodTail(game->snake, game->food[i]))
            {
                UpdateFood(game->food[i]);
            }

            if(!CheckCollisionWithFoodBody(game, game->food[i]))
            {
                UpdateFood(game->food[i]);
            }
        } 
    }
}