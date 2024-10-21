#ifndef __SNAKE__
#define __SNAKE__

#include <raylib.h>

#define SLOT_SIZE 32

#define WIDTH 1280
#define HEIGHT 960

#define HEAD_TEXTURE_D "./Assets/snake_head_default.png"
#define BODY_TEXTURE_D "./Assets/snake_body_default.png"
#define TAIL_TEXTURE_D "./Assets/snake_tail_default.png"

#define HEAD_TEXTURE "./Assets/snake_head_minecraft.png"
#define BODY_TEXTURE "./Assets/snake_body_minecraft.png"
#define TAIL_TEXTURE "./Assets/snake_tail_minecraft.png"

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

void ChangeSegmentTexture(SnakeSegment* seg, char* texture);

void InitSegment(SnakeSegment* seg, SnakeSegment* next, SnakeSegment* prev);

void InitSnake(Snake* snake);

void MoveSnake(Snake* snake);

void AddSegment(Snake* snake);

bool CheckCollision(Snake* snake);

void UpdateSnake(Snake* snake);

void DrawSnake(Snake* snake);

#endif