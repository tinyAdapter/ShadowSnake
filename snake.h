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

//��ײ���
void SN_Impact();

//������Χ������λ�õ�ʳ��
void SN_sorpt(int x, int y);

//���ʳ��
void SN_SetFood(int x, int y);

#endif // !SNAKE_H
