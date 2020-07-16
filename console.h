#ifndef CONSOLE_H
#define CONSOLE_H

/*窗口初始化*/
void CS_InitWindow();

/*设置光标位置*/
void CS_SetPosition(int x, int y);

/* 根据宽高设置控制台窗口的大小 */
void CS_SetWindowSize(short width, short height);

/*根据坐标清除窗口中的指定位置*/
void CS_ClearByCoord(short x, short y, int rowCount, int columnCount);

/*设置光标颜色*/
/* 0-黑色, 1-蓝色,   2-绿色,      3-浅绿色,     4-红色,   5-紫色,   6-黄色,   7-白色,
* 8-灰色, 9-淡蓝色, 10-淡绿色,   11-淡浅绿色   12-淡红色 13-淡紫色 14-淡黄色 15-亮白色*/
void CS_SetColor(int foreground, int background);

/*打印函数*/
void CS_Print(int x, int y, const char *value);
void CS_Print(int x, int y, int value);
void CS_Print(int x, int y, char value);
void CS_Print(int x, int y, double value);

#endif