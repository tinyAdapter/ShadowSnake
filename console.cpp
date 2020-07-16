#include <windows.h>
#include <stdio.h>
#include "shadow_snake.h"

/*���ڳ�ʼ��*/
void CS_InitWindow()
{
	CS_SetWindowSize(120, 37);
	CS_ClearByCoord(0, 0, 37, 120);
}

/*���ù��λ��*/
void CS_SetPosition(int x, int y)
{
	COORD cursorPosition;   //��������
	HANDLE handle;          //��ǰ���ھ��
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	cursorPosition.X = x;   //����x��y����
	cursorPosition.Y = y;
	SetConsoleCursorPosition(handle, cursorPosition);
}

/* ���ݿ�����ÿ���̨���ڵĴ�С */
void CS_SetWindowSize(short width, short height)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	//���ÿ���̨���ڵĻ�������С
	COORD size = { width, height };
	SetConsoleScreenBufferSize(handle, size);
	//���ÿ���̨���ڴ�С,��������ǻ�������С-1
	SMALL_RECT rect = { 0, 0, width - 1, height - 1 };
	SetConsoleWindowInfo(handle, 1, &rect);
	//CloseHandle(handle);
}


/*����������������е�ָ��λ��*/
void CS_ClearByCoord(short x, short y, int rowCount, int columnCount)
{
	COORD coordStart = { x, y };
	int i = 0;
	DWORD written;
	HANDLE handle;                              //��ǰ���ھ��
	CONSOLE_SCREEN_BUFFER_INFO bInfo;           //������Ϣ�ṹ
	handle = GetStdHandle(STD_OUTPUT_HANDLE);   //��ñ�׼����豸���
	GetConsoleScreenBufferInfo(handle, &bInfo);  //��ô�����Ϣ

	for (i = 0; i < rowCount; i++)
	{
		CS_SetPosition(coordStart.X, coordStart.Y);
		FillConsoleOutputCharacter(handle, ' ', columnCount, coordStart, &written);
		coordStart.Y++;
	}

}

/*���ù����ɫ*/
/* 0-��ɫ, 1-��ɫ,   2-��ɫ,      3-ǳ��ɫ,     4-��ɫ,   5-��ɫ,   6-��ɫ,   7-��ɫ,
* 8-��ɫ, 9-����ɫ, 10-����ɫ,   11-��ǳ��ɫ   12-����ɫ 13-����ɫ 14-����ɫ 15-����ɫ*/
void CS_SetColor(int foreground, int background) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);                    //��ȡ��ǰ���ھ��
	SetConsoleTextAttribute(handle, foreground + background * 0x10);//������ɫ

}

/*��ӡ�ַ���*/
void CS_Print(int x, int y, const char *value) {
	CS_SetPosition(x, y);
	printf("%s", value);
}
/*��ӡ����*/
void CS_Print(int x, int y, int value) {
	CS_SetPosition(x, y);
	printf("%-d", value);
}

/*��ӡ�ַ�*/
void CS_Print(int x, int y, char value) {
	CS_SetPosition(x, y);
	printf("%c", value);
}

void CS_Print(int x, int y, double value) {
	
	CS_SetPosition(x, y);
	printf("%.2f", value);
	
}