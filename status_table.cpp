#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "shadow_snake.h"

#define INIT_HEIGHT 12
void ST_Init()
{
	CS_SetWindowSize(120, 37);
	CS_Print(98, INIT_HEIGHT, "角色名：");
	CS_Print(98, INIT_HEIGHT + 2, "生命值：");
	CS_Print(98, INIT_HEIGHT + 4, "分数：");
	CS_Print(98, INIT_HEIGHT + 6, "模式：");
	CS_Print(98, INIT_HEIGHT + 8, "速度：");
	CS_Print(98, INIT_HEIGHT + 10, "能量：");
	CS_Print(114, INIT_HEIGHT + 10, "/100");
	CS_Print(98, INIT_HEIGHT + 12, "长度：");


	CS_Print(109, INIT_HEIGHT, g_Name);
}

void ST_Refresh()
{
	CS_ClearByCoord(109, INIT_HEIGHT + 10, 1, 4);
	CS_Print(109, INIT_HEIGHT + 2, g_HP);
	CS_Print(109, INIT_HEIGHT + 4, g_Score);
	CS_Print(109, INIT_HEIGHT + 6, g_Mode);
	CS_Print(109, INIT_HEIGHT + 8, g_Speed);
	CS_Print(109, INIT_HEIGHT + 10, g_Power);
	CS_Print(109, INIT_HEIGHT + 12, (int)g_Snake.size());
	CS_Print(100, INIT_HEIGHT + 16, "加速：按 1");
	CS_Print(100, INIT_HEIGHT + 17, "穿越：按 2");
	CS_Print(100, INIT_HEIGHT + 18, "吸收：按 3");
	if (g_ModeRemainStep <= 5 + g_Level * 5 && g_Mode != 0) {
		CS_Print(100, INIT_HEIGHT + 14, "  *技*能*开*启*");
		CS_Print(100, INIT_HEIGHT + 15, "离技能关闭还有 ");
		printf("%d 步", (4+g_Level*5)-g_ModeRemainStep);
	}
	else
	{
		CS_Print(100, INIT_HEIGHT + 14, "*技*能*关*闭*");
		CS_ClearByCoord(100, INIT_HEIGHT + 15, 1, 12);
	}
}