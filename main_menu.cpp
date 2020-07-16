#include <stdio.h>
#include <Windows.h>
#include "shadow_snake.h"

/*主界面打印函数*/
void MMU_ShowMainMenu()
{
	CS_InitWindow();
	CS_Print(48, 12, "1.	新游戏");
	CS_Print(48, 14, "2.	继续游戏");
	CS_Print(48, 16, "3.	设置");
	CS_Print(48, 18, "4.	排行榜");
	CS_Print(48, 20, "5.	退出游戏");
	printf("\n");
}

/*设置界面打印函数*/
void MMU_ShowSettingsMenu()
{
	CS_InitWindow();
	CS_Print(10, 2, "音乐开关");
	CS_Print(24, 2, "开<y>   关<n>");
	CS_Print(10, 6, "游戏帮助");
	CS_Print(16, 10, "移动：");
	CS_Print(24, 10, "↑ 向上爬行	");
	CS_Print(36, 10, "↓ 向下爬行	");
	CS_Print(24, 12, "← 向左爬行	");
	CS_Print(36, 12, " → 向右爬行	");
	CS_Print(16, 14, "技能：");
	CS_Print(24, 16, "1.世界变慢");
	CS_Print(24, 18, "2.穿墙，穿障碍物");
	CS_Print(24, 20, "3.吸附食物");
	CS_Print(16, 22, "障碍物类型：");
	CS_Print(28, 22, "  墙，山，水，子弹");

	// 设置音乐开关显示
	if (g_IsMusicOn == true)
	{
		CS_SetColor(9, 0);
		CS_Print(24, 2, "开<y>");
		CS_SetColor(7, 0);
	}
	else
	{
		CS_SetColor(9, 0);
		CS_Print(32, 2, "关<n>");
		CS_SetColor(7, 0);
	}
}