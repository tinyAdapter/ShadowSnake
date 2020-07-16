#ifndef INPUT_H
#define INPUT_H

#define MAX_NAME 10
#define MAX_CHARACTER 10

//获取指定范围的整形
int IN_GetInt(int min, int max, const char* prompt);

//获取指定范围浮点型
double IN_GetDouble(double min, double max, char * prompt);

//获取指定范围Char型
char IN_GetChar(char valid[], char *prompt);

//获取指定范围字符串
char* IN_GetString(char* prompt);
#endif