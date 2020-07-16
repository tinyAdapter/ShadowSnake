
//屏幕大小   120*36

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
		s.append("打开失败");
		LOG_WriteError(s.c_str());
	}

	//控制台相关操作
	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);//获得标准输入的句柄

	CONSOLE_SCREEN_BUFFER_INFO csbi;   //定义窗口信息结构体

	SMALL_RECT scroll, cutArea;                                //定义移动区域

	COORD  position = { LEFT,INIT_CURSOR_HEIGHT };                    //定义移动到的位置

	CHAR_INFO  char_fill;                           //定义填充的字符

	GetConsoleScreenBufferInfo(handle_out, &csbi);    //获取窗口缓冲区信息

	char_fill.Char.UnicodeChar = 0;                  //设置填充字体的相关属性
	char_fill.Attributes = csbi.wAttributes;


	//定义移动区域有关位置
	scroll.Left = LEFT;
	scroll.Right = RIGHT;
	scroll.Top = INIT_CURSOR_HEIGHT;
	scroll.Bottom = 35;

	cutArea.Left = LEFT;
	cutArea.Right = RIGHT;
	cutArea.Top = INIT_CURSOR_HEIGHT;
	scroll.Bottom = 36;


	//读取数据
	strcpy_s(temp, readLine(file, &isEnd));
	//strcpy(temp, readLine(file));
	int flag = 0;
	CS_SetColor(14, 0);
	while (!isEnd)
	{
		//时钟周期内监听用户输入
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
	CS_Print(0, 35, "载入中");
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
