#ifndef INPUT_H
#define INPUT_H

#define MAX_NAME 10
#define MAX_CHARACTER 10

//��ȡָ����Χ������
int IN_GetInt(int min, int max, const char* prompt);

//��ȡָ����Χ������
double IN_GetDouble(double min, double max, char * prompt);

//��ȡָ����ΧChar��
char IN_GetChar(char valid[], char *prompt);

//��ȡָ����Χ�ַ���
char* IN_GetString(char* prompt);
#endif