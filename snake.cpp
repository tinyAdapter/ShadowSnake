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
	PB_SetValue("暗影之蛇获得了食物 ");
	printf("%c", g_GameView_Old[Y][X] - 32);
	printf("分数加2");
	g_Score += 2;
	if (g_Snake.size() > g_Level * 5 + 5)
		PB_SetValue("\t\t*****下一关已开启，可以进入(+为下一关)******", 36);
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

	//0 - 空地  1 - 墙   2 - 石头   3 - 山   4 - 水   8 - 蛇头    9 - 蛇身     abcdef食物  +门

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
			RT_Pause(true, "震惊，暗影之蛇竟自己怼死自己！");
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
			RT_Pause(true, "震惊，暗影之蛇竟被墙怼死！");
		}

		break;
	case '2':
		if (g_Mode != 2)
		{
			g_HP--;
			ST_Refresh();
			RT_Pause(true, "震惊，暗影之蛇竟惨遭石头蹂躏！");
		}
		break;
	case '3':
		if (g_Mode != 2)
		{
			g_HP--;
			ST_Refresh();
			RT_Pause(true, "震惊，暗影之蛇竟惨遭小山蹂躏！");
		}

		break;
	case '4':
		if (g_Mode != 2)
		{
			g_HP--;
			ST_Refresh();
			RT_Pause(true, "震惊，暗影之蛇竟淹死了！");
		}

		break;
	case '+':
		//长度达到要求则通关，否则死亡
		if (g_Snake.size() >= 5 + 5 * g_Level)
		{
			if (g_Level == 6)
			{
				PB_SetValue("暗影之蛇复仇成功！");
				DR_ScrollView("Story_end.txt");
				RK_Store();
				//RT_Exit(0);
				//MMU_ShowMainMenu();
				g_EndGame = true;
			}
			g_Level++;

			//载入剧情
			if (g_Level <= 6) {
				char StoryName[15];
				_itoa_s(g_Level, StoryName, 15);
				strcat_s(StoryName, "_Story.txt");
				//RT_Pause(false, "暗影之蛇开启了下一段征程！请选择");
				PB_SetValue("暗影之蛇开启了下一段征程！");
				Sleep(2000);
				DR_ScrollView(StoryName);
				GP_ToNextLevel();
			}
		}
		else
		{
			g_HP--;
			RT_Pause(true, "弱小的你未能在危机四伏的亚马逊存活。");
		}
		break;
	case '-':
		g_Level--;
		PB_SetValue("暗影之蛇回到了自己的领地。");
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
		PB_SetValue("暗影之蛇获得了食物。");
		g_GameView[y][x] = '0';
		CS_Print(x, y, ' ');
		g_GetFood++;

		g_Food--;
		break;
	default:
		break;
	}
}