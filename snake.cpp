#include <windows.h>
#include "shadow_snake.h"

void SN_Move(Direction direction)
{
	g_Snake.pop_back();
	SN_MovePlus(direction);
}

void SN_MovePlus(Direction direction)
{
	COORD firstElem = g_Snake.front();
	COORD newFront;
	newFront.X = firstElem.X;
	newFront.Y = firstElem.Y;
	switch (direction)
	{
	case Up:
		newFront.Y--;
		break;
	case Down:
		newFront.Y++;
		break;
	case Left:
		newFront.X--;
		break;
	case Right:
		newFront.X++;
		break;
	default:
		break;
	}
	g_Snake.push_front(newFront);
}

void SN_ImpactIsFood(int Y, int X)
{
	PB_SetValue("��Ӱ֮�߻����ʳ�� ");
	printf("%c", g_GameView_Old[Y][X] - 32);
	printf("������2");
	g_Score += 2;
	if (g_Snake.size() > g_Level * 5 + 5)
		PB_SetValue("\t\t*****��һ���ѿ��������Խ���(+Ϊ��һ��)******", 36);
	else
		CS_ClearByCoord(0, 36, 1, 30);
	if (g_Power<100)
		g_Power += 5;
	ST_Refresh();
	g_GameView[Y][X] = '0';
	g_GetFood = 1;
	g_Food--;
}

void SN_Impact()
{
	COORD Head = g_Snake.front();
	int X = Head.X;
	int Y = Head.Y;

	//0 - �յ�  1 - ǽ   2 - ʯͷ   3 - ɽ   4 - ˮ   8 - ��ͷ    9 - ����     abcdefʳ��  +��

	switch (g_GameView_Old[Y][X])
	{
	case 'a':
		g_SnakeColor = 4;
		SN_ImpactIsFood(Y, X);
		if (g_Power<100)
			g_Power += 5;
		break;

	case 'b':
		g_SnakeColor = 5;
		SN_ImpactIsFood(Y, X);
		if (g_Power<100)
			g_Power += 5;
		break;
	case 'c':
		g_SnakeColor = 10;
		SN_ImpactIsFood(Y, X);
		if (g_Power<100)
			g_Power += 5;
		break;
	case 'd':
		g_SnakeColor = 13;
		SN_ImpactIsFood(Y, X);
		if (g_Power<100)
			g_Power += 5;
		break;
	case 'e':
		g_SnakeColor = 14;
		SN_ImpactIsFood(Y, X);
		if (g_Power<100)
			g_Power += 5;
		break;
	case 'f':
		g_SnakeColor = 15;
		SN_ImpactIsFood(Y, X);

		break;
	case '9':
		if (g_Mode != 2)
		{
			g_HP--;
			RT_Pause(true, "�𾪣���Ӱ֮�߾��Լ�����Լ���");
		}
		break;
	}


	switch (g_GameTile[Y][X])
	{
	case '0':
		break;
	case '1':
		if (g_Mode != 2)
		{
			g_HP--;
			ST_Refresh();
			RT_Pause(true, "�𾪣���Ӱ֮�߾���ǽ�����");
		}

		break;
	case '2':
		if (g_Mode != 2)
		{
			g_HP--;
			ST_Refresh();
			RT_Pause(true, "�𾪣���Ӱ֮�߾�����ʯͷ���");
		}
		break;
	case '3':
		if (g_Mode != 2)
		{
			g_HP--;
			ST_Refresh();
			RT_Pause(true, "�𾪣���Ӱ֮�߾�����Сɽ���");
		}

		break;
	case '4':
		if (g_Mode != 2)
		{
			g_HP--;
			ST_Refresh();
			RT_Pause(true, "�𾪣���Ӱ֮�߾������ˣ�");
		}

		break;
	case '+':
		//���ȴﵽҪ����ͨ�أ���������
		if (g_Snake.size() >= 5 + 5 * g_Level)
		{
			if (g_Level == 6)
			{
				PB_SetValue("��Ӱ֮�߸���ɹ���");
				DR_ScrollView("Story_end.txt");
				RK_Store();
				//RT_Exit(0);
				//MMU_ShowMainMenu();
				g_EndGame = true;
			}
			g_Level++;

			//�������
			if (g_Level <= 6) {
				char StoryName[15];
				_itoa_s(g_Level, StoryName, 15);
				strcat_s(StoryName, "_Story.txt");
				//RT_Pause(false, "��Ӱ֮�߿�������һ�����̣���ѡ��");
				PB_SetValue("��Ӱ֮�߿�������һ�����̣�");
				Sleep(2000);
				DR_ScrollView(StoryName);
				GP_ToNextLevel();
			}
		}
		else
		{
			g_HP--;
			RT_Pause(true, "��С����δ����Σ���ķ�������ѷ��");
		}
		break;
	case '-':
		g_Level--;
		PB_SetValue("��Ӱ֮�߻ص����Լ�����ء�");
		GP_ToNextLevel();
		break;
	}

	if (g_Mode == 3)
	{
		SN_sorpt(X, Y);
		SN_sorpt(X - 1, Y);
		SN_sorpt(X, Y + 1);
		SN_sorpt(X, Y - 1);
	}
}

void SN_sorpt(int x, int y)
{
	SN_SetFood(x, y + 1);
	SN_SetFood(x, y - 1);
	SN_SetFood(x + 1, y);
	SN_SetFood(x - 1, y);
}

void SN_SetFood(int x, int y)
{
	switch (g_GameView_Old[y][x])
	{
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
		PB_SetValue("��Ӱ֮�߻����ʳ�");
		g_GameView[y][x] = '0';
		CS_Print(x, y, ' ');
		g_GetFood++;

		g_Food--;
		break;
	default:
		break;
	}
}