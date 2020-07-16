#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "shadow_snake.h"

#define INIT_HEIGHT 12
void ST_Init()
{
	CS_SetWindowSize(120, 37);
	CS_Print(98, INIT_HEIGHT, "��ɫ����");
	CS_Print(98, INIT_HEIGHT + 2, "����ֵ��");
	CS_Print(98, INIT_HEIGHT + 4, "������");
	CS_Print(98, INIT_HEIGHT + 6, "ģʽ��");
	CS_Print(98, INIT_HEIGHT + 8, "�ٶȣ�");
	CS_Print(98, INIT_HEIGHT + 10, "������");
	CS_Print(114, INIT_HEIGHT + 10, "/100");
	CS_Print(98, INIT_HEIGHT + 12, "���ȣ�");


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
	CS_Print(100, INIT_HEIGHT + 16, "���٣��� 1");
	CS_Print(100, INIT_HEIGHT + 17, "��Խ���� 2");
	CS_Print(100, INIT_HEIGHT + 18, "���գ��� 3");
	if (g_ModeRemainStep <= 5 + g_Level * 5 && g_Mode != 0) {
		CS_Print(100, INIT_HEIGHT + 14, "  *��*��*��*��*");
		CS_Print(100, INIT_HEIGHT + 15, "�뼼�ܹرջ��� ");
		printf("%d ��", (4+g_Level*5)-g_ModeRemainStep);
	}
	else
	{
		CS_Print(100, INIT_HEIGHT + 14, "*��*��*��*��*");
		CS_ClearByCoord(100, INIT_HEIGHT + 15, 1, 12);
	}
}