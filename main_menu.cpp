#include <stdio.h>
#include <Windows.h>
#include "shadow_snake.h"

/*�������ӡ����*/
void MMU_ShowMainMenu()
{
	CS_InitWindow();
	CS_Print(48, 12, "1.	����Ϸ");
	CS_Print(48, 14, "2.	������Ϸ");
	CS_Print(48, 16, "3.	����");
	CS_Print(48, 18, "4.	���а�");
	CS_Print(48, 20, "5.	�˳���Ϸ");
	printf("\n");
}

/*���ý����ӡ����*/
void MMU_ShowSettingsMenu()
{
	CS_InitWindow();
	CS_Print(10, 2, "���ֿ���");
	CS_Print(24, 2, "��<y>   ��<n>");
	CS_Print(10, 6, "��Ϸ����");
	CS_Print(16, 10, "�ƶ���");
	CS_Print(24, 10, "�� ��������	");
	CS_Print(36, 10, "�� ��������	");
	CS_Print(24, 12, "�� ��������	");
	CS_Print(36, 12, " �� ��������	");
	CS_Print(16, 14, "���ܣ�");
	CS_Print(24, 16, "1.�������");
	CS_Print(24, 18, "2.��ǽ�����ϰ���");
	CS_Print(24, 20, "3.����ʳ��");
	CS_Print(16, 22, "�ϰ������ͣ�");
	CS_Print(28, 22, "  ǽ��ɽ��ˮ���ӵ�");

	// �������ֿ�����ʾ
	if (g_IsMusicOn == true)
	{
		CS_SetColor(9, 0);
		CS_Print(24, 2, "��<y>");
		CS_SetColor(7, 0);
	}
	else
	{
		CS_SetColor(9, 0);
		CS_Print(32, 2, "��<n>");
		CS_SetColor(7, 0);
	}
}