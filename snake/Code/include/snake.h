#ifndef __SNAKE__
#define __SNAKE__

#include <raylib.h>

#define SLOT_SIZE 64

#define HEAD_TEXTURE "./Assets/snake_head.png"
#define BODY_TEXTURE "./Assets/snake_body.png"
#define TAIL_TEXTURE "./Assets/snake_tail.png"

typedef struct SSnakeSegment
{
    Texture2D texture;
    Vector2 pos; // position
    Vector2 dir; // direction
    struct SSnakeSegment* next;
    struct SSnakeSegment* prev;
} SnakeSegment;

typedef struct SSnake
{
    unsigned int size;
    struct SSnakeSegment* head;
    struct SSnakeSegment* tail;
	void (*destroy)(void*);
}Snake;

Snake* CreateSnake();

void ChangeSegmentTexture(SnakeSegment* segment, char* texture);

void InitSegment(SnakeSegment* segment, SnakeSegment* next, SnakeSegment* prev);

void InitSnake(Snake* snake);

void DestroySnake(Snake** snake);

void MoveSnake(Snake* snake);

#endif