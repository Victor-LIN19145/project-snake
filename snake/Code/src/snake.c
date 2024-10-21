#include <stddef.h>
#include <stdlib.h>
#include <raylib.h>

#include <include/snake.h>

// Function to create a new snake segment
Snake* CreateSnake()
{
    Snake* createSnake = calloc(1, sizeof(Snake)); // Allocate 1 memory in Snake struct
    if (createSnake == NULL)
		return NULL;

    createSnake->size = 0;
	createSnake->head = NULL;
	createSnake->tail = NULL;
	
	return createSnake; 
}

//Function to change the texture of a snake segment
void ChangeSegmentTexture(SnakeSegment* segment, char* texture)
{
    if (segment == NULL || texture == NULL)
        return;

    Image img = LoadImage(texture);
    ImageResize(&img, SLOT_SIZE, SLOT_SIZE);
    segment->texture = LoadTextureFromImage(img);
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
        ChangeSegmentTexture(seg, TAIL_TEXTURE);
        seg->dir = prev->dir;
        seg->pos = (Vector2){ prev->pos.x - seg->dir.x,
            prev->pos.y - seg->dir.y };
    }
    else if (seg->prev == NULL)
    {
        ChangeSegmentTexture(seg, HEAD_TEXTURE);
        seg->dir = (Vector2){ 1, 0 };
        seg->pos = (Vector2){ 1, 0 };
    }
    else
    {
        ChangeSegmentTexture(seg, BODY_TEXTURE);
        seg->dir = prev->dir;
        seg->pos = (Vector2){ prev->pos.x - seg->dir.x,
            prev->pos.y - seg->dir.y };
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


    SnakeSegment *headSegment
        = calloc(1, sizeof(SnakeSegment));
    SnakeSegment *bodySegment
        = calloc(1, sizeof(SnakeSegment));
    SnakeSegment *tailSegment
        = calloc(1, sizeof(SnakeSegment));

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

    if (IsKeyPressed(KEY_RIGHT) && snake->head->dir.x!= -1)
        snake->head->dir = (Vector2){ 1, 0 };

    else if (IsKeyPressed(KEY_LEFT) && snake->head->dir.x!= 1)
        snake->head->dir = (Vector2){ -1, 0 };

    if (IsKeyPressed(KEY_UP) && snake->head->dir.y!= 1)
        snake->head->dir = (Vector2){ 0, 1 };

    else if (IsKeyPressed(KEY_DOWN) && snake->head->dir.y!= -1)
        snake->head->dir = (Vector2){ 0, -1 };
}

void AddSegment(Snake* snake)
{
    if (snake == NULL)
        return;

    SnakeSegment* createSegment = calloc(1, sizeof(SnakeSegment));
    if (createSegment == NULL)
		return;

    InitSnake(createSegment);
    snake->head = createSegment;
    snake->tail = createSegment;

}

bool CheckCollision(Snake* snake)
{
    if (snake == NULL)
        return false;

    SnakeSegment* current = snake->head;
    SnakeSegment* next;

    while (current!= NULL)
    

}

void UpdateSnake(Snake* snake)
{
    if (snake == NULL)
        return;
}

void DrawSnake(Snake* snake)
{
    if (snake == NULL)
        return;
}

// Function to destroy the snake and free memory
void DestroySnake(Snake** snake)
{
    if (snake == NULL|| *snake == NULL)
		return;
}

//draw body 
void SnakeDraw(Snake* snake)
{
    if (snake == NULL)
        return;
}
