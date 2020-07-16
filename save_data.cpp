#include <stdio.h>
#include "shadow_snake.h"

/*游戏存档*/
void SD_SaveAll()
{
	FILE *pFile;
	errno_t err = fopen_s(&pFile, "save.dat", "wb");
	if (err)
	{
		LOG_WriteError("存档文件打开失败");
		return;
	}
	fwrite(&g_Name, sizeof(char), 20, pFile);			//角色名
	fwrite(&g_HP, sizeof(int), 1, pFile);				//角色生命值
	fwrite(&g_Score, sizeof(int), 1, pFile);			//所得分数
	fwrite(&g_Mode, sizeof(int), 1, pFile);				//蛇的模式
	fwrite(&g_Speed, sizeof(double), 1, pFile);			//蛇的速度
	fwrite(&g_Power, sizeof(int), 1, pFile);			//当前能量
	fwrite(&g_GameView, sizeof(char), 32 * 96, pFile);	//存储蛇，食物位置
	fwrite(&g_GameTile, sizeof(char), 32 * 96, pFile);	//存储地形的矩阵
	int size = g_Snake.size();
	fwrite(&size, sizeof(int), 1, pFile);
	for (std::list<COORD>::iterator it = g_Snake.begin(); it != g_Snake.end(); it++)
	{
		fwrite(&*it, sizeof(COORD), 1, pFile);//存储蛇身位置
	}
	fwrite(&g_UserInput, sizeof(char), 1, pFile);		//保留用户输入
	fwrite(&g_GetFood, sizeof(int), 1, pFile);			//此刻是否吃到食物
	fwrite(&g_Level, sizeof(int), 1, pFile);			//当前所处关卡等级
	fwrite(&g_Food, sizeof(int), 1, pFile);				//游戏场景上食物数量
	fwrite(&g_GameView_Old, sizeof(char), 32 * 96, pFile); 	//蛇，食物位置缓存
	fwrite(&g_SnakeColor, sizeof(int), 1, pFile);		//蛇的颜色
	fwrite(&g_ModeRemainStep, sizeof(int), 1, pFile);	//蛇技能剩余时间
	fwrite(&g_LastHead, sizeof(COORD), 1, pFile);		//记录上一次蛇头位置
	fclose(pFile);
	return;
}

/*恢复存档*/
void SD_LoadAll()
{
	FILE *pFile;
	errno_t err = fopen_s(&pFile, "save.dat", "rb");
	if (err)
	{
		LOG_WriteError("存档文件打开失败");
		return;
	}
	fread(&g_Name, sizeof(char), 20, pFile);			//角色名
	fread(&g_HP, sizeof(int), 1, pFile);				//角色生命值
	fread(&g_Score, sizeof(int), 1, pFile);				//所得分数
	fread(&g_Mode, sizeof(int), 1, pFile);				//蛇的模式
	fread(&g_Speed, sizeof(double), 1, pFile);			//蛇的速度
	fread(&g_Power, sizeof(int), 1, pFile);				//当前能量
	fread(&g_GameView, sizeof(char), 32 * 96, pFile);	//存储蛇，食物位置
	fread(&g_GameTile, sizeof(char), 32 * 96, pFile);	//存储地形的矩阵
	int size = 0;
	fread(&size, sizeof(int), 1, pFile);
	g_Snake.clear();
	for (int i = 0; i < size; i++)
	{
		COORD c;
		fread(&c, sizeof(COORD), 1, pFile);//存储蛇身位置
		g_Snake.push_back(c);
	}
	fread(&g_UserInput, sizeof(char), 1, pFile);		//保留用户输入
	fread(&g_GetFood, sizeof(int), 1, pFile);			//此刻是否吃到食物
	fread(&g_Level, sizeof(int), 1, pFile);				//当前所处关卡等级
	fread(&g_Food, sizeof(int), 1, pFile);				//游戏场景上食物数量
	fread(&g_GameView_Old, sizeof(char), 32 * 96, pFile); 	//蛇，食物位置缓存
	fread(&g_SnakeColor, sizeof(int), 1, pFile);		//蛇的颜色
	fread(&g_ModeRemainStep, sizeof(int), 1, pFile);	//蛇技能剩余时间
	fread(&g_LastHead, sizeof(COORD), 1, pFile);		//记录上一次蛇头位置
	fclose(pFile);
	return;
}
