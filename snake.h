#ifndef SNAKE_H
#define SNAKE_H

enum Direction
{
	Up,
	Down,
	Left,
	Right
};

void SN_Move(Direction direction);

void SN_MovePlus(Direction direction);

//碰撞检测
void SN_Impact();

//吸附周围的三个位置的食物
void SN_sorpt(int x, int y);

//获得食物
void SN_SetFood(int x, int y);

#endif // !SNAKE_H
