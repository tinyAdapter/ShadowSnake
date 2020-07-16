#ifndef CONSOLE_H
#define CONSOLE_H

/*���ڳ�ʼ��*/
void CS_InitWindow();

/*���ù��λ��*/
void CS_SetPosition(int x, int y);

/* ���ݿ�����ÿ���̨���ڵĴ�С */
void CS_SetWindowSize(short width, short height);

/*����������������е�ָ��λ��*/
void CS_ClearByCoord(short x, short y, int rowCount, int columnCount);

/*���ù����ɫ*/
/* 0-��ɫ, 1-��ɫ,   2-��ɫ,      3-ǳ��ɫ,     4-��ɫ,   5-��ɫ,   6-��ɫ,   7-��ɫ,
* 8-��ɫ, 9-����ɫ, 10-����ɫ,   11-��ǳ��ɫ   12-����ɫ 13-����ɫ 14-����ɫ 15-����ɫ*/
void CS_SetColor(int foreground, int background);

/*��ӡ����*/
void CS_Print(int x, int y, const char *value);
void CS_Print(int x, int y, int value);
void CS_Print(int x, int y, char value);
void CS_Print(int x, int y, double value);

#endif