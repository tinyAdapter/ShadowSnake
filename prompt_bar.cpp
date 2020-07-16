#include <stdio.h>
#include "shadow_snake.h"

/*获取提示栏当前显示文字*/
char* PB_GetValue()
{
	return NULL;
}

/*设置提示栏显示文字*/
void PB_SetValue(const char* prompt,int col)
{
	CS_ClearByCoord(0, col, 1, 120);
	CS_SetPosition(0, col);
	CS_Print(0, col, prompt);
}

void PB_SetValue(const char* prompt)
{
	CS_ClearByCoord(0, 35, 1, 120);
	CS_SetPosition(0, 35);
	CS_Print(0, 35, prompt);
}

/*简单调用*/
int PB_WaitInt(int min, int max, char * prompt)
{
	return IN_GetInt(min, max, prompt);
}
double PB_WaitDouble(double min, double max, char * prompt)
{
	return IN_GetDouble(min, max, prompt);
}
char PB_WaitChar(char valid[], char *prompt)
{
	return IN_GetChar(valid, prompt);
}
char* PB_WaitString(char* prompt)
{
	return IN_GetString(prompt);
}