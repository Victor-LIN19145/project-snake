#include <stdlib.h>
#include <raylib.h>

#include "snake.h"
#include "game.h"

Snake* InitSnake()
{
    Snake* snake = calloc(1,sizeof(Snake));
    snake->size = 3;
    snake->speed = 0;
    snake->head = NULL;
    snake->tail = NULL;
    snake->moveAllow = true;

    Segment* headSegment = calloc(1,sizeof(Segment));
    Segment* bodySegment = calloc(1,sizeof(Segment));
    Segment* tailSegment = calloc(1,sizeof(Segment));

    InitSegment(headSegment, NULL);
    InitSegment(bodySegment, headSegment);
    InitSegment(tailSegment, bodySegment);

    snake->head = headSegment;
    snake->tail = tailSegment;

    return snake;
}

void InitSegment(Segment* body, Segment* head)
{
    body->prev = head;
    body->next = NULL;
    
    if (body->prev == NULL)
    {
        body->position = (Vector2){128, 128};
        body->direction = (Vector2){32,0};
    }   
    else
    {
        head->next = body;
        body->position = (Vector2){head->position.x - head->direction.x,head->position.y - head->direction.y};
        body->direction =  (Vector2){head->direction.x ,head->direction.y};
    }
}

void DrawSnake(Game* game)
{
    for (Segment* current = game->snake->head
        ; current != NULL
            ; current = current->next)
    {
        
        if (current->prev == NULL)
        {
            DrawTexture(game->assets->gameTexture[0],
                current->position.x, current->position.y,WHITE);
        }
        else if (current->next == NULL)
        {
            DrawTexture(game->assets->gameTexture[2],
                current->position.x, current->position.y,WHITE);
        }
        else
        {
            DrawTexture(game->assets->gameTexture[1],
                current->position.x, current->position.y,WHITE);
        }
    }
}

void UpdateSnake(Snake* snake)
{
    snake->moveAllow = true;
    Segment* current = snake->tail;
    for (; current->prev != NULL; current = current->prev)
    {
        current->position = current->prev->position;
        current->direction = current->prev->direction;
    }

    snake->head->position.x =
        snake->head->position.x + snake->head->direction.x;
    snake->head->position.y =
        snake->head->position.y + snake->head->direction.y;
}

void SnakeMoveArrow(Snake* snake) 
{
    if (IsKeyPressed(KEY_UP) && snake->head->direction.y != 32
        && snake->moveAllow == true)
    {
        snake->moveAllow = false;
        snake->head->direction = (Vector2) {0, -32};
    }

    if (IsKeyPressed(KEY_DOWN) && snake->head->direction.y != -32
        && snake->moveAllow == true)
    {
        snake->moveAllow = false;
        snake->head->direction = (Vector2) {0, 32};
    }

    if(IsKeyPressed(KEY_RIGHT) && snake->head->direction.x != -32
        && snake->moveAllow == true)
    {
        snake->moveAllow = false;
        snake->head->direction = (Vector2){32,0};
    }
    
    if(IsKeyPressed(KEY_LEFT) && snake->head->direction.x != 32
        && snake->moveAllow == true)
    {
        snake->moveAllow = false;
        snake->head->direction = (Vector2){-32,0};
    }
}

void SnakeMoveTouch(Snake* snake) 
{
    if (IsKeyPressed(KEY_W) && snake->head->direction.y != 32
        && snake->moveAllow == true)
    {
        snake->moveAllow = false;
        snake->head->direction = (Vector2) {0, -32};
    }

    if (IsKeyPressed(KEY_S) && snake->head->direction.y != -32
        && snake->moveAllow == true)
    {
        snake->moveAllow = false;
        snake->head->direction = (Vector2) {0, 32};
    }

    if(IsKeyPressed(KEY_D) && snake->head->direction.x != -32
        && snake->moveAllow == true)
    {
        snake->moveAllow = false;
        snake->head->direction = (Vector2){32,0};
    }
    
    if(IsKeyPressed(KEY_A) && snake->head->direction.x != 32
        && snake->moveAllow == true)
    {
        snake->moveAllow = false;
        snake->head->direction = (Vector2){-32,0};
    }
}

bool CheckBodyCollision(Game* game)
{
    for (Segment* current = game->snake->head->next;
        current != NULL;
            current = current->next)
    {
        if (current->position.x == game->snake->head->position.x
            && current->position.y == game->snake->head->position.y) 
                game->gameState = GAME_OVER;
    }
    return true;
}

void AddSegment(Game* game)
{
    Segment *bodySegment = calloc(1,sizeof(Segment));
    InitSegment(bodySegment,game->snake->tail);
    game->snake->tail = bodySegment;
}


void BorderCollision(Game* game)
{
    if (game->snake->head->position.x >= 1280
        || game->snake->head->position.x < 0
            || game->snake->head->position.y >= 640
                || game->snake->head->position.y < 0)
                    game->gameState = GAME_OVER;
}

void SnakeDestroy(Snake** snake)
{
	if (snake == NULL|| *snake == NULL) return;

	Segment* next = (*snake)->head;
	while (next != NULL)
	{
		Segment* segment = next;
		next = segment->next;
		free(segment);
	}

	free(*snake);
	*snake = NULL;
}