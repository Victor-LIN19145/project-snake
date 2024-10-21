#ifndef __FOOD__
#define __FOOD__

typedef struct SGame Game;

typedef struct SFood 
{
    Vector2 position;
    int id;
    bool placed;
}Food;

Food* CreateFood(int id);
bool IsFoodOnSnake(Snake *snake, Food *food);
void UpdateFood(Food* food);
void InitFood(Game* game);
void DrawFood(Game* game);
bool CheckCollisionWithFoodHead(Snake* snake, Food* food);
bool CheckCollisionWithFoodTail(Snake* snake, Food* food);
bool CheckCollisionWithFoodBody(Game* game, Food* food);
void CheckAllFood(Game* game);
#endif