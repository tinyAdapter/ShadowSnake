#include <stdio.h>
#include "shadow_snake.h"
#include <string>
#include <time.h>

#define FOOD_NUM 5

/*      1.（40，12）->（59,21）
2. (24 ,10) ->(64,19)
3.（30 ,0） ->（66,31）
4.（18，4） ->（77,26）
5.（0 , 0） ->(95,31)
6.（0 , 0） ->(95,31)
*/


void GV_LoadLevel(const char* filename)
{
	int i, j;
	FILE* fp;
	errno_t err	= fopen_s(&fp, filename, "r"); //打开文件
	if (err)
	{
		LOG_WriteError("关卡打开失败");
	}
	for (i = 0; i < 32; i++)
	{
		for (j = 0; j < 96; j++)
		{
			g_GameTile[i][j] = fgetc(fp);
		}
		fscanf_s(fp, "\n");
	}
	fclose(fp);
}


//刷新游戏界面
void GV_Show()
{
	if (g_Mode == 2)
		GT_Refresh();
	int len = 96 * 32;
	int row = 0;
	int col = 0;
	//CS_ClearByCoord(0, 0, 32, 96);
	for (int i = 1; i <= len; i++)
	{

		//抹掉原来蛇身
		switch (g_GameView_Old[col][row])
		{
		case '8':
		case '9':
		case 'a':
		case 'c':
		case 'b':
		case 'd':
		case 'e':
		case 'f':
			CS_Print(row, col, ' ');
		default:
			break;
		}


		//打印新的蛇身和食物
		switch (g_GameView[col][row])
		{

		case '8':
			CS_SetColor(g_SnakeColor, 0);
			CS_Print(row, col,'@');
			break;
		case '9':
			CS_SetColor(g_SnakeColor, 0);
			CS_Print(row, col, '#');
			break;
		case 'a':
			CS_SetColor(4, 0);
			CS_Print(row, col, 'A');


			break;
		case 'b':
			CS_SetColor(5, 0);
			CS_Print(row, col, 'B');


			break;
		case 'c':
			CS_SetColor(10, 0);
			CS_Print(row, col, 'C');


			break;
		case 'd':
			CS_SetColor(13, 0);
			CS_Print(row, col, 'D');


			break;
		case 'e':
			CS_SetColor(14, 0);
			CS_Print(row, col, 'E');


			break;
		case 'f':
			CS_SetColor(15, 0);
			CS_Print(row, col, 'F');

			break;
		default:
			break;
		}

		CS_SetColor(7, 0);

		CS_SetPosition(0, 0);
		row++;
		if (i % 96 == 0) {
			col++;
			row = 0;
		}
	}
	ST_Refresh();
}

/*显示地形*/
void GT_Show()
{
	//载入关卡信息
	char levelName[6];
	_itoa_s(g_Level, levelName, 6, 10);
	strcat_s(levelName, ".txt");
	GV_LoadLevel(levelName);

	int len = 96 * 32;
	int row = 0;
	int col = 0;
	CS_ClearByCoord(0, 0, 32, 96);
	for (int i = 1; i <= len; i++)
	{

		if (g_GameTile[col][row] == ' ')
			CS_Print(row, col, ' ');

		else if (g_GameTile[col][row] == '1')
			CS_Print(row, col, 'H');

		else if (g_GameTile[col][row] == '2')
			CS_Print(row, col, 'o');

		else if (g_GameTile[col][row] == '3')
			CS_Print(row, col, '&');

		else if (g_GameTile[col][row] == '4')
			CS_Print(row, col, 'S');

		else if (g_GameTile[col][row] == '+')
			CS_Print(row, col, '+');

		else if (g_GameTile[col][row] == '-')
			CS_Print(row, col, '-');

		CS_SetPosition(0, 0);
		row++;
		if (i % 96 == 0) {
			col++;
			row = 0;
		}
	}
}


//刷新g_GameView[][] ,并缓存数据
void GV_Refresh()
{
	for (int i = 0; i < 32; i++)

		for (int j = 0; j < 96; j++)

			g_GameView_Old[i][j] = g_GameView[i][j];


	for (int i = 0; i < 32; i++)
	{
		for (int j = 0; j < 96; j++)
		{
			if (g_GameView[i][j] == '8' || g_GameView[i][j] == '9')
				g_GameView[i][j] = 0;
		}
	}

	for (std::list<COORD>::iterator it = g_Snake.begin(); it != g_Snake.end(); it++) {
		if (it == g_Snake.begin())
			g_GameView[(*it).Y][(*it).X] = '8';
		else
			g_GameView[(*it).Y][(*it).X] = '9';
	}
	g_GetFood = 0;
}



void GT_Refresh()
{


	int len = 96 * 32;
	int row = 0;
	int col = 0;
	for (int i = 1; i <= len; i++)
	{


		if (g_GameTile[col][row] == '2')
			CS_Print(row, col, 'O');

		if (g_GameTile[col][row] == '3')
			CS_Print(row, col, '&');

		if (g_GameTile[col][row] == '4')
			CS_Print(row, col, 'S');

		CS_SetPosition(0, 0);
		row++;
		if (i % 96 == 0) {
			col++;
			row = 0;
		}
	}


}


void GV_setfood_in_area(int left, int up, int right, int down)
{
	srand((unsigned)time(NULL));

	//随机特殊点个数
	int g_special = 0;
	if ((g_Level > 2) && rand() % (5 - g_Level / 2) == 0)
	{
		g_special = rand() % ((g_Level + 1) / 2);
	}
	else
	{
		g_special = 0;
	}

	/*特殊点
	第三关   （1, 37）（30, 42）
	第四关   （6，43）（20, 31）（24，58）（24，60）（25，56）（25，59）（25，61）
	第五关    （30, 17）（1, 35）（1, 39）（1, 69）（2, 36）（2, 68）（2, 71）
	（10, 7）（8, 78）
	第六关     （4, 74）（5, 73）（5, 75）（12, 53）（12, 56）（13, 55）（15, 3）
	（29, 36）（29, 38）（30, 35）（30, 37）（30, 39）
	*/
	while (g_Food <= FOOD_NUM * g_Level && g_special > 0)
	{
		switch (g_Level)
		{
		case 3:
			switch (rand() % 2)
			{
			case 0:g_GameView[1][37] = rand() % 6 + 97;
				break;
			case 1:g_GameView[30][42] = rand() % 6 + 97;
				break;
			}
			break;
		case 4://（6，43）（20, 31）（24，58）（24，60）（25，56）（25，59）（25，61）
			switch (rand() % 7)
			{
			case 0:g_GameView[6][43] = rand() % 6 + 97;
				break;
			case 1:g_GameView[20][31] = rand() % 6 + 97;
				break;
			case 2:g_GameView[24][58] = rand() % 6 + 97;
				break;
			case 3:g_GameView[24][60] = rand() % 6 + 97;
				break;
			case 4:g_GameView[25][56] = rand() % 6 + 97;
				break;
			case 5:g_GameView[25][59] = rand() % 6 + 97;
				break;
			case 6:g_GameView[25][61] = rand() % 6 + 97;
				break;
			}
			break;
		case 5://（30, 17）（1, 35）（1, 39）（1, 69）（2, 36）（2, 68）（2, 71）
			   //（10, 7）（8, 78）
			switch (rand() % 9)
			{
			case 0:g_GameView[30][17] = rand() % 6 + 97;
				break;
			case 1:g_GameView[1][35] = rand() % 6 + 97;
				break;
			case 2:g_GameView[1][39] = rand() % 6 + 97;
				break;
			case 3:g_GameView[1][69] = rand() % 6 + 97;
				break;
			case 4:g_GameView[2][36] = rand() % 6 + 97;
				break;
			case 5:g_GameView[2][68] = rand() % 6 + 97;
				break;
			case 6:g_GameView[2][71] = rand() % 6 + 97;
				break;
			case 7:g_GameView[10][7] = rand() % 6 + 97;
				break;
			case 8:g_GameView[8][78] = rand() % 6 + 97;
				break;
			}
			break;
		case 6:// （4, 74）（5, 73）（5, 75）（12, 53）（12, 56）（13, 55）（15, 3）
			   //（29, 36）（29, 38）（30, 35）（30, 37）（30, 39）
			switch (rand() % 12)
			{
			case 0:g_GameView[4][74] = rand() % 6 + 97;
				break;
			case 1:g_GameView[5][73] = rand() % 6 + 97;
				break;
			case 2:g_GameView[5][75] = rand() % 6 + 97;
				break;
			case 3:g_GameView[12][53] = rand() % 6 + 97;
				break;
			case 4:g_GameView[12][56] = rand() % 6 + 97;
				break;
			case 5:g_GameView[13][55] = rand() % 6 + 97;
				break;
			case 6:g_GameView[15][3] = rand() % 6 + 97;
				break;
			case 7:g_GameView[29][36] = rand() % 6 + 97;
				break;
			case 8:g_GameView[29][38] = rand() % 6 + 97;
				break;
			case 9:g_GameView[30][35] = rand() % 6 + 97;
				break;
			case 10:g_GameView[30][37] = rand() % 6 + 97;
				break;
			case 11:g_GameView[30][39] = rand() % 6 + 97;
				break;
			}
			break;
		}
		g_special--;
		g_Food++;
	}

	//一般点
	while (g_Food <= FOOD_NUM * g_Level)
	{
		int x = rand() % (right - left) + left + 1;
		int y = rand() % (down - up) + up + 1;
		double length = sqrt(pow(x - g_Snake.front().X, 2) + pow(y - g_Snake.front().Y, 2));
		if (g_GameView[y][x] == 0 && g_GameTile[y][x] == ' ' && (length > 4 * g_Level))
		{
			g_GameView[y][x] = rand() % 6 + 97;
			g_Food++;
		}
	}


}

void GV_SetFood()
{
	switch (g_Level)
	{
	case 1:GV_setfood_in_area(40, 12, 59, 21);
		break;
	case 2:GV_setfood_in_area(24, 10, 64, 19);
		break;
	case 3:GV_setfood_in_area(30, 0, 66, 31);
		break;
	case 4:GV_setfood_in_area(18, 4, 77, 26);
		break;
	case 5:
	case 6:GV_setfood_in_area(0, 0, 95, 31);
		break;
	}
}


