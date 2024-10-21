#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "snake.h"

// Function to create a new snake segment
Snake* CreateSnake()
{
    Snake* createSnake = calloc(1, sizeof(Snake)); // Allocate 1 memory in Snake struct
    if (createSnake == NULL)
		return NULL;
	
	return createSnake;
}

//Function to change the texture of a snake segment
void ChangeSegmentTexture(SnakeSegment* seg, char* texture)
{
    if (seg == NULL || texture == NULL)
        return;

    Image img = LoadImage(texture);
    ImageResize(&img, SLOT_SIZE, SLOT_SIZE);
    Texture2D newTexture = LoadTextureFromImage(img);
    seg->texture = newTexture;
    UnloadImage(img);
}

//Function to initialize a snake segment
void InitSegment(SnakeSegment* seg, SnakeSegment* next, SnakeSegment* prev)
{
    // seg: segment
    
    if (seg == NULL)
        return;
        
    seg->next = next;
    seg->prev = prev;
    if (seg->next == NULL)
    {
        ChangeSegmentTexture(seg, TAIL_TEXTURE_D);
        seg->dir = prev->dir;
        seg->pos = (Vector2){ prev->pos.x - seg->dir.x, prev->pos.y - seg->dir.y };
    }
    else if (seg->prev == NULL)
    {
        ChangeSegmentTexture(seg, HEAD_TEXTURE_D);
        seg->dir = (Vector2){ 32, 0 };
        seg->pos = (Vector2){ 32, 3 };
    }
    else
    {
        ChangeSegmentTexture(seg, BODY_TEXTURE_D);
        seg->dir = prev->dir;
        seg->pos = (Vector2){ prev->pos.x - seg->dir.x, prev->pos.y - seg->dir.y };
    }
}

// Function to initialize the position and direction vectors for the snake
void InitSnake(Snake *snake)
{
    if (snake == NULL)
        return;

    snake->size = 3;
	snake->head = NULL;
	snake->tail = NULL;

    SnakeSegment *headSegment = calloc(1, sizeof(SnakeSegment));
    SnakeSegment *bodySegment = calloc(1, sizeof(SnakeSegment));
    SnakeSegment *tailSegment = calloc(1, sizeof(SnakeSegment));

    InitSegment(headSegment, bodySegment, NULL);
    InitSegment(bodySegment, tailSegment, headSegment);
    InitSegment(tailSegment, NULL, bodySegment);

    snake->head = headSegment;
    snake->tail = tailSegment;
}

void MoveSnake(Snake* snake)
{   
    if (snake == NULL)
        return;

    if (IsKeyPressed(KEY_RIGHT) && snake->head->dir.x!= -32) // key R and direction is not left
        snake->head->dir = (Vector2){ 32, 0 }; // Move right

    else if (IsKeyPressed(KEY_LEFT) && snake->head->dir.x!= 32) // key L and direction is not right
        snake->head->dir = (Vector2){ -32, 0 }; // Move left

    if (IsKeyPressed(KEY_UP) && snake->head->dir.y!= 32) // key D and direction is not up
        snake->head->dir = (Vector2){ 0, -32 };

    else if (IsKeyPressed(KEY_DOWN) && snake->head->dir.y!= -32)
        snake->head->dir = (Vector2){ 0, 32 };
}

void AddSegment(Snake* snake)
{
    if (snake == NULL)
        return;

    SnakeSegment* createSegment = calloc(1, sizeof(SnakeSegment));
    if (createSegment == NULL)
		return;

    InitSegment(createSegment, NULL, snake->tail);
    if (snake->tail == NULL)
    {
        snake->tail = createSegment;
    }
}

bool CheckCollision(Snake* snake)
{
    if (snake == NULL)
        return false;

    for ( SnakeSegment* current = snake->head; current != NULL; current = current->next)
    {
        if (current != snake->head && (current->pos.x == snake->head->pos.x && current->pos.y == snake->head->pos.y))
            return true;
    }
    return false;
}

void UpdateSnake(Snake* snake)
{
    if (snake == NULL)
        return;

    MoveSnake(snake);

    SnakeSegment* current =snake->tail;
    for (;current->prev != NULL; current = current->prev )
    {
        current->pos = current->prev->pos;
        current->dir = current->prev->dir;
    }
    snake->head->pos.x =snake->head->pos.x+ snake->head->dir.x;
    snake->head->pos.y =snake->head->pos.y+ snake->head->dir.y;

    if (snake->head->pos.x < 0)
        snake->head->pos.x = WIDTH - SLOT_SIZE;

    if (snake->head->pos.x > WIDTH)
        snake->head->pos.x = 0;

    if (snake->head->pos.y < 0)
        snake->head->pos.y = HEIGHT - SLOT_SIZE;

    if (snake->head->pos.y > HEIGHT)
        snake->head->pos.y = 0;

    bool gameOver = CheckCollision(snake);
    printf("%d\n", gameOver);
}


void DrawSnake(Snake* snake)
{
    if (snake == NULL)
        return;

    for ( SnakeSegment* current = snake->head; current != NULL; current = current->next)
    {
        DrawTexture(current->texture, current->pos.x, current->pos.y, WHITE);
    }
}