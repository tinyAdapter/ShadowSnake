#include <string.h>
#include <windows.h>
#include "shadow_snake.h"
#include <iostream>
#include <time.h>
#include <conio.h>

#define TIME_PERIOD 1000.0

void showSnake();
void gameStarting();
void showSnakeControl();
COORD listGet(int index);

//游戏区域 96*32
//小地图     10*10	右上角
//提示		  行：35，36 
//状态表		97,11->119,34

void GP_NewGame()
{
	DR_ScrollView("1_Story.txt");
	strcpy_s(g_Name, IN_GetString("请输入用户名："));

	//窗口初始化
	memset(g_GameTile, 0, 32 * 96);
	memset(g_GameView, 0, 32 * 96);
	memset(g_GameView_Old, 0, 32 * 96);
	CS_InitWindow();
	ST_Init();
	BD_Display();
	MMP_ShowNextRoom(1);

	//角色初始化
	g_HP = 4;
	g_Speed = 1.5;
	g_Level = 1;
	g_Mode = 0;
	g_Food = 0;
	g_Power = 0;
	g_Score = 0;
	g_Snake.clear();
	g_EndGame = false;
	g_UserInput = 77;

	//等待开始
	CS_SetColor(6, 0);
	char c[2]{ 's', 'q' };
	char choice = PB_WaitChar(c, "是否开始游戏（s开始，q退出）：");
	CS_SetColor(7, 0);
	if (choice == 'q')
		return;

	//定义蛇头位置
	COORD S_Head;
	S_Head.X = 50;
	S_Head.Y = 18;
	//定义初始位置和长度
	COORD temp;
	for (int i = 1; i < 5; i++) {

		temp.X = S_Head.X - i;
		temp.Y = S_Head.Y;
		g_Snake.push_back(temp);
	}
	g_Snake.push_front(S_Head);

	//游戏开始前的准备
	gameStarting();
	//进入主循环
	GP_MainLoop();
}

void gameStarting()
{
	GT_Show();
	showSnake();
	GV_Refresh();
	showSnakeControl();
}

void GP_LoadGame()
{
	//读取存档
	SD_LoadAll();

	//窗口初始化
	CS_InitWindow();
	ST_Init();
	BD_Display();
	for (size_t i = 1; i <= g_Level; i++)
	{
		MMP_ShowNextRoom(g_Level);
	}

	//角色初始化
	g_EndGame = false;

	//等待开始
	CS_SetColor(6, 0);
	char c[2]{ 's', 'q' };
	char choice = PB_WaitChar(c, "是否开始游戏（s开始，q退出）：");
	CS_SetColor(7, 0);
	if (choice == 'q')
		return;

	//游戏开始前的准备
	gameStarting();
	//进入主循环
	GP_MainLoop();
}

/*打印操作方式*/
void showSnakeControl()
{
	PB_SetValue("  W      ↑     ESC", 33);
	PB_SetValue("A S D ← ↓ →  暂停", 34);
	PB_SetValue("");
}

/*主循环*/
void GP_MainLoop()
{
	while (!g_EndGame)
	{
		while (true)
		{
			//计算
			SN_Impact();
			GV_SetFood();
			//绘图
			ST_Refresh(); //状态表刷新

			//时钟周期内监听用户输入
			clock_t inittime = clock();
			clock_t nowtime = clock();
			char tempChar;
			int sign = 0;
			while (difftime(nowtime, inittime) <= 1000 / g_Speed && !g_EndGame)
			{
				nowtime = clock();
				if (_kbhit())
				{

					tempChar = _getch();
					if (!isascii(tempChar))
						tempChar = _getch();
					switch (tempChar)
					{
					case 72:
					case 'w':
					case 75:
					case 'a':
					case 77:
					case 'd':
					case 80:
					case 's':
						g_UserInput = tempChar;
						sign = 1;
						break;
					case 27:
						RT_Pause(false);
						sign = 1;
						break;
					case 49:
					case 50:
					case 51:
						g_Mode_Input = tempChar;
						sign = 2;
						break;
					default:
						break;
					}
					if (sign == 1)
						break;
					else
						continue;
				}
			}
			//如果游戏处于结束状态，直接退出
			if (g_EndGame) break;

			switch (g_UserInput)
			{
			case 72:
			case 'w':
				g_LastHead = listGet(0);    //记录上一次蛇头位置
				if (g_GetFood)
					SN_MovePlus(Direction::Up);
				else
					SN_Move(Direction::Up);
				GV_Refresh();
				break;
			case 75:
			case 'a':
				g_LastHead = listGet(0);
				if (g_GetFood)
					SN_MovePlus(Direction::Left);
				else
					SN_Move(Direction::Left);
				GV_Refresh();
				break;
			case 77:
			case 'd':
				g_LastHead = listGet(0);
				if (g_GetFood)
					SN_MovePlus(Direction::Right);
				else
					SN_Move(Direction::Right);
				GV_Refresh();
				break;
			case 80:
			case 's':
				g_LastHead = listGet(0);
				if (g_GetFood)
					SN_MovePlus(Direction::Down);
				else
					SN_Move(Direction::Down);
				GV_Refresh();
				break;
			default:
				break;
			}
			if (g_Power >= 30)
			{
				switch (g_Mode_Input)
				{
				case 49:
					g_Mode = 1;
					g_Power -= 20;

					break;
				case 50:
					g_Mode = 2;
					g_Power -= 20;
					break;
				case 51:
					g_Mode = 3;
					g_Power -= 20;
					break;
				default:
					break;
				}
				//g_Mode_Input = 0;
			}

			//标记是否有障碍物在蛇身内
			int flag = 0;

			char temp;
			COORD coord;

			//模式一开启，世界变慢
			if (g_Mode == 1)
				g_Speed += 0.5;
			else
				g_Speed = 1.0 + g_Level*0.5;

			//开启模式未撞之前
			if (g_Mode != 0)
				g_ModeRemainStep++;

			if (g_ModeRemainStep == (5 + g_Level * 5) && g_Mode != 0) {
				g_Mode = 0;
				g_ModeRemainStep = 0;
			}

			//进入之后,通过之后将其模式置为0
			if (g_Mode_Input == 2)
			{
				for (size_t i = 0; i < g_Snake.size(); i++)
				{
					coord = listGet(i);
					temp = g_GameTile[coord.Y][coord.X];
					if (temp == '2' || temp == '3' || temp == '4')
						flag = 1;
					if (flag) {
						g_Mode = 2;
						g_ModeRemainStep--;
						break;
					}
				}
			}
			//未出去时模式2
			else if (g_Mode_Input = 1 || g_Mode == 3)
				g_Mode_Input = 0;

			GV_Show();
			GT_Refresh();
		}
	}
}

//下一关
void GP_ToNextLevel()
{
	//窗口初始化
	memset(g_GameTile, 0, 32 * 96);
	memset(g_GameView, 0, 32 * 96);
	memset(g_GameView_Old, 0, 32 * 96);
	CS_InitWindow();
	ST_Init();
	BD_Display();
	MMP_ShowNextRoom(g_Level);

	//角色初始化
	g_Food = 0;
	g_Snake.clear();
	g_UserInput = 77;

	//定义蛇头位置
	COORD S_Head;
	S_Head.X = 50;
	S_Head.Y = 18;
	//定义初始位置和长度
	COORD temp;
	for (int i = 1; i < 5; i++) {

		temp.X = S_Head.X - i;
		temp.Y = S_Head.Y;
		g_Snake.push_back(temp);
	}
	g_Snake.push_front(S_Head);

	if (g_Level % 2 != 0)
		CS_SetColor(7, 0);

	gameStarting();
	//返回后，回到主循环
	return;
}

//打印界面布局
void BD_Display()
{
	int len = 96 * 32;
	int row = 0;
	int col = 0;
	for (int i = 1; i <= len; i++)
	{
		row++;
		if (i % 96 == 0) {
			CS_Print(row, col, "\u2593");
			col++;
			row = 0;
		}
	}
	for (int i = 0; i < 120; i += 2)
		CS_Print(i, col, "\u2593");
	for (int i = 0; i < 24; i += 2)
		CS_Print(96 + i, 10, "\u2593");
}

// 得到List里的具体位置元素
COORD listGet(int index)
{
	int count = 0;
	for (std::list<COORD>::iterator it = g_Snake.begin(); it != g_Snake.end(); it++, count++)
		if (count == index)
			return *it;
	// UNABLE TO REACH
	return *g_Snake.end();
}

//打印蛇的位置
void showSnake()
{
	COORD temp;
	for (std::list<COORD>::iterator it = g_Snake.begin(); it != g_Snake.end(); it++) {
		temp = *it;
		if (it == g_Snake.begin())
			CS_Print(temp.X, temp.Y, '@');
		else
			CS_Print(temp.X, temp.Y, '#');
	}
}