#include <stdio.h>
#include "shadow_snake.h"

#define MMP_INIT_X 98
#define MMP_INIT_Y 0
#define MMP_WIDTH 22
#define MMP_HEIGHT 10

//0 - 无,1 - 墙,2 - 已探索,3 - 未探索,4-所在地
//(1,7) 开局 ;(1,10)小草地；(1,13)小树林；
//(4,13)亚马逊；(7,13)保护伞营地；(7,16)终结之地；
const int g_WorldRoom[10][22] = {
	{ 0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,1,3,1,1,3,1,1,3,1,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,1,3,1,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,1,3,1,1,3,1,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 } };

int g_ShownRoom[10][22] = {
	{ 0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,1,4,1,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 } };

void showWaitForExploredRoom(int x, int y);

//显示小地图;当前角色位置
void MMP_ShowMap(int x, int y) 
{
	CS_ClearByCoord(MMP_INIT_X, MMP_INIT_Y, MMP_HEIGHT,MMP_WIDTH);
	//显示小地图
	for (int i= 0; i < MMP_HEIGHT; i++)
	{
		for (int j = 0; j < MMP_WIDTH; j++)
		{
			//将之前所在位置改为已探索
			if (g_ShownRoom[i][j] == 4)
			{
				g_ShownRoom[i][j] = 2;
			}
			if (i == x&&j == y)
			{
				g_ShownRoom[i][j] = 4;
			}

			switch (g_ShownRoom[i][j])
			{
			case 0:CS_Print(MMP_INIT_X + j, MMP_INIT_Y + i, " ");    //无
				break;
			case 1:CS_Print(MMP_INIT_X + j, MMP_INIT_Y + i, "+");   //墙
				break;
			case 2:CS_Print(MMP_INIT_X + j, MMP_INIT_Y + i, "O");   //已探索
				break;
			case 3:CS_Print(MMP_INIT_X + j, MMP_INIT_Y + i, "X");   //未探索
				break;
			case 4:CS_Print(MMP_INIT_X + j, MMP_INIT_Y + i, "@");   //所在地
				break;
			}
		}	
		printf("\n");
		    
	}

}


//(1,7) 开局 ;(1,10)小草地；(1,13)小树林；
//(4,13)亚马逊；(7,13)保护伞营地；(7,16)终结之地；
//显示角色当前所处房间周围8个格子中尚未显示的房间
void MMP_ShowNextRoom(int level)
{
	switch (level)
	{
	case 1:
		showWaitForExploredRoom(1, 10);
		MMP_ShowMap(1,7);
		break;
	case 2:
		showWaitForExploredRoom(1, 13);
		showWaitForExploredRoom(4, 13);
		MMP_ShowMap(1, 10);
		break;
	case 3:
		showWaitForExploredRoom(4, 13);
		MMP_ShowMap(1, 13);
		break;
	case 4:
		showWaitForExploredRoom(7, 13);
		showWaitForExploredRoom(7, 16);
		MMP_ShowMap(4, 13);
		break;
	case 5:
		showWaitForExploredRoom(7, 16);
		MMP_ShowMap(7, 13);
		break;
	case 6:
		MMP_ShowMap(7, 16);
		break;
	}
}

void showWaitForExploredRoom(int x, int y)
{
	for (int i = x-1; i < x+2; i++)
	{
		for (int j = y-1; j < y+2; j++)
		{
			if (i != x||j != y)
			{
				g_ShownRoom[i][j] = 1;
			}
		}
	}

	//避免将已探索改为未探索
	if (g_ShownRoom[x][y] != 2&& g_ShownRoom[x][y] != 4)
	{
		g_ShownRoom[x][y] = 3;
	}
	
}