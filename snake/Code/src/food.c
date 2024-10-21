#include <stdlib.h>
#include <stddef.h>
#include <raylib.h>
#include <time.h>
#include <stdio.h>

#include "game.h"
#include "snake.h"
#include "food.h"

Food* CreateFood(int id)
{
    Food* food = calloc(1,sizeof(Food));
    food->id = id; 
    food->placed = false;
    
    if(id==0) food->placed = true;

    int x = GetRandomValue(0, 31);
    int y = GetRandomValue(0, 19);

    food->position = (Vector2){x*32, y*32};
    return food;
}

void UpdateFood(Food* food)
{
    int x = GetRandomValue(0, 31);
    int y = GetRandomValue(0, 19);

    food->position = (Vector2){x*32, y*32};
}

void InitFood(Game* game)
{
    game->food[0] = CreateFood(0);
}

void DrawFood(Game* game)
{
        if(game->food[0] != NULL)
            DrawTexture(game->assets->gameTexture[4], game->food[0]->position.x, game->food[0]->position.y, WHITE);   
}

bool CheckCollisionWithFoodHead(Snake* snake, Food* food)
{
    return (snake->head->position.x == food->position.x && snake->head->position.y == food->position.y);
}

bool CheckCollisionWithFoodTail(Snake* snake, Food* food)
{
    return (snake->tail->position.x == food->position.x && snake->tail->position.y == food->position.y);
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
    return (game->snake->tail->position.x == food->position.x && game->snake->tail->position.y == food->position.y);
}

void CheckAllFood(Game* game)
{
    if(CheckCollisionWithFoodHead(game->snake, game->food[0]))
    {
        AddSegment(game);
        UpdateFood(game->food[0]);
        game->score++;
    }

    if(CheckCollisionWithFoodTail(game->snake, game->food[0]))
    {
        UpdateFood(game->food[0]);
    }

    if(!CheckCollisionWithFoodBody(game, game->food[0]))
    {
        UpdateFood(game->food[0]);
        printf("Change food position\n");
    }
}