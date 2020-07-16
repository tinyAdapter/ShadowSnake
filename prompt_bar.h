#ifndef PROMPT_BAR_H
#define PROMPT_BAR_H

//获取提示栏当前显示文字
char* PB_GetValue();

//设置提示栏显示文字
void PB_SetValue(const char* prompt);

//获取指定范围的整形
int PB_WaitInt(int min, int max, char* prompt);

//获取指定范围浮点型
double PB_WaitDouble(double min, double max, char * prompt);

//获取指定范围Char型
char PB_WaitChar(char valid[], char *prompt);

//获取指定范围字符串
char* PB_WaitString(char* prompt);

//指定位置打印
void PB_SetValue(const char* prompt, int col);

#endif // !PROMPT_BAR_H
