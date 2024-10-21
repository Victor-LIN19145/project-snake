#ifndef __SNAKE__
#define __SNAKE__

#include <stdbool.h>
#include <raylib.h>

typedef struct SGame Game;

typedef struct SSegment 
{
    struct SSegment *next;
    struct SSegment *prev;
    Vector2 position;
    Vector2 direction;

}Segment;

typedef struct SSnake 
{  
    int speed;       
    int size;

    Segment *head;
    Segment *tail; 
    bool moveAllow;
}Snake;

Snake* InitSnake();
void InitSegment(Segment *segment, Segment *snake);
void UpdateSnake(Snake *snake);
void DrawSnake(Game* game);
void SnakeMoveArrow(Snake* snake);
void SnakeMoveTouch(Snake* snake);
bool CheckBodyCollision(Game* game);
void AddSegment(Game* game);
void BorderCollision(Game* game);
void SnakeDestroy(Snake** snake);

#endif 