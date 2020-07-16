
//��Ļ��С   120*36

#include <Windows.h>
#include <stdio.h>
#include <string>
#include <conio.h>
#include <time.h>
#include "shadow_snake.h"

#define LENGTH 100
#define LEFT 35
#define RIGHT 85
#define INIT_CURSOR_HEIGHT 5
#define TIME_PERIOD 200

char* readLine(FILE* file, bool *isEnd);

void DR_ScrollView(const char* filename) {

	int count = 0;
	char temp[LENGTH] = { 0 };
	bool isEnd = 0;
	CS_InitWindow();
	CS_SetPosition(LEFT, 0);

	FILE* file;
	if (fopen_s(&file,filename, "r"))
	{
		std::string s;
		s.append(filename);
		s.append("��ʧ��");
		LOG_WriteError(s.c_str());
	}

	//����̨��ز���
	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);//��ñ�׼����ľ��

	CONSOLE_SCREEN_BUFFER_INFO csbi;   //���崰����Ϣ�ṹ��

	SMALL_RECT scroll, cutArea;                                //�����ƶ�����

	COORD  position = { LEFT,INIT_CURSOR_HEIGHT };                    //�����ƶ�����λ��

	CHAR_INFO  char_fill;                           //���������ַ�

	GetConsoleScreenBufferInfo(handle_out, &csbi);    //��ȡ���ڻ�������Ϣ

	char_fill.Char.UnicodeChar = 0;                  //�������������������
	char_fill.Attributes = csbi.wAttributes;


	//�����ƶ������й�λ��
	scroll.Left = LEFT;
	scroll.Right = RIGHT;
	scroll.Top = INIT_CURSOR_HEIGHT;
	scroll.Bottom = 35;

	cutArea.Left = LEFT;
	cutArea.Right = RIGHT;
	cutArea.Top = INIT_CURSOR_HEIGHT;
	scroll.Bottom = 36;


	//��ȡ����
	strcpy_s(temp, readLine(file, &isEnd));
	//strcpy(temp, readLine(file));
	int flag = 0;
	CS_SetColor(14, 0);
	while (!isEnd)
	{
		//ʱ�������ڼ����û�����
		clock_t inittime = clock();
		clock_t nowtime = clock();
		if (temp[0] != 0 && count < 31) {
			CS_SetPosition(LEFT, count + INIT_CURSOR_HEIGHT);
			temp[strlen(temp) - 1] = 0;
			printf("%s", temp);
		}
		else
		{
			ScrollConsoleScreenBuffer(handle_out, &scroll, &cutArea, position, &char_fill);
			CS_ClearByCoord(LEFT, 36, 1, 1);
			CS_SetPosition(LEFT, 36);
			printf("%s", temp);
		}
		strcpy_s(temp, readLine(file, &isEnd));
		count++;
		while (difftime(nowtime, inittime) <= TIME_PERIOD)
		{
			nowtime = clock();
			if (_kbhit())
			{
				flag = 1;
				break;
			}
		}
	}
	CS_SetColor(7, 0);
	if (flag)
		_getch();
	CS_Print(0, 35, "������");
	for(int i=0;i<114;i++){	
		if (i < 70)
			Sleep(20);
		else if (i < 80)
			Sleep(80);
		else
			Sleep(20);
		if (i == 90)
			Sleep(300);
		CS_Print(0, 38+i, ">");
	}
	
}

char* readLine(FILE* file, bool *isEnd)
{
	char *str_line = new char[LENGTH];

	if (!*isEnd)
		if (fgets(str_line, LENGTH, file) == NULL) {
			*isEnd = 1;
			for (int i = 0; i < LENGTH; i++)
				str_line[i] = 0;
		}
	return str_line;
}
