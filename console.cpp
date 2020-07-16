#include <windows.h>
#include <stdio.h>
#include "shadow_snake.h"

/*窗口初始化*/
void CS_InitWindow()
{
	CS_SetWindowSize(120, 37);
	CS_ClearByCoord(0, 0, 37, 120);
}

/*设置光标位置*/
void CS_SetPosition(int x, int y)
{
	COORD cursorPosition;   //光标的坐标
	HANDLE handle;          //当前窗口句柄
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	cursorPosition.X = x;   //设置x、y坐标
	cursorPosition.Y = y;
	SetConsoleCursorPosition(handle, cursorPosition);
}

/* 根据宽高设置控制台窗口的大小 */
void CS_SetWindowSize(short width, short height)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	//设置控制台窗口的缓冲区大小
	COORD size = { width, height };
	SetConsoleScreenBufferSize(handle, size);
	//设置控制台窗口大小,最大坐标是缓冲区大小-1
	SMALL_RECT rect = { 0, 0, width - 1, height - 1 };
	SetConsoleWindowInfo(handle, 1, &rect);
	//CloseHandle(handle);
}


/*根据坐标清除窗口中的指定位置*/
void CS_ClearByCoord(short x, short y, int rowCount, int columnCount)
{
	COORD coordStart = { x, y };
	int i = 0;
	DWORD written;
	HANDLE handle;                              //当前窗口句柄
	CONSOLE_SCREEN_BUFFER_INFO bInfo;           //窗口信息结构
	handle = GetStdHandle(STD_OUTPUT_HANDLE);   //获得标准输出设备句柄
	GetConsoleScreenBufferInfo(handle, &bInfo);  //获得窗口信息

	for (i = 0; i < rowCount; i++)
	{
		CS_SetPosition(coordStart.X, coordStart.Y);
		FillConsoleOutputCharacter(handle, ' ', columnCount, coordStart, &written);
		coordStart.Y++;
	}

}

/*设置光标颜色*/
/* 0-黑色, 1-蓝色,   2-绿色,      3-浅绿色,     4-红色,   5-紫色,   6-黄色,   7-白色,
* 8-灰色, 9-淡蓝色, 10-淡绿色,   11-淡浅绿色   12-淡红色 13-淡紫色 14-淡黄色 15-亮白色*/
void CS_SetColor(int foreground, int background) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);                    //获取当前窗口句柄
	SetConsoleTextAttribute(handle, foreground + background * 0x10);//设置颜色

}

/*打印字符串*/
void CS_Print(int x, int y, const char *value) {
	CS_SetPosition(x, y);
	printf("%s", value);
}
/*打印整数*/
void CS_Print(int x, int y, int value) {
	CS_SetPosition(x, y);
	printf("%-d", value);
}

/*打印字符*/
void CS_Print(int x, int y, char value) {
	CS_SetPosition(x, y);
	printf("%c", value);
}

void CS_Print(int x, int y, double value) {
	
	CS_SetPosition(x, y);
	printf("%.2f", value);
	
}