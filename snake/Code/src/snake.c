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


    SnakeSegment *headSegment = calloc(1, sizeof(SnakeSegment));
    SnakeSegment *bodySegment = calloc(1, sizeof(SnakeSegment));
    SnakeSegment *tailSegment = calloc(1, sizeof(SnakeSegment));

    InitSegment(headSegment, bodySegment, NULL);
    InitSegment(bodySegment, tailSegment, headSegment);
    InitSegment(tailSegment, NULL, bodySegment);

    snake->head = headSegment;
    snake->tail = tailSegment;

}

// Function to destroy the snake and free memory
void DestroySnake(Snake** snake)
{
    if (snake == NULL|| *snake == NULL)
		return;
}

void MoveSnake(Snake* snake)
{
    if (snake == NULL)
        return;
}

//draw body 
void SnakeDraw(Snake* snake)
{
    if (snake == NULL)
        return;
}
