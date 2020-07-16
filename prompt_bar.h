#ifndef PROMPT_BAR_H
#define PROMPT_BAR_H

//��ȡ��ʾ����ǰ��ʾ����
char* PB_GetValue();

//������ʾ����ʾ����
void PB_SetValue(const char* prompt);

//��ȡָ����Χ������
int PB_WaitInt(int min, int max, char* prompt);

//��ȡָ����Χ������
double PB_WaitDouble(double min, double max, char * prompt);

//��ȡָ����ΧChar��
char PB_WaitChar(char valid[], char *prompt);

//��ȡָ����Χ�ַ���
char* PB_WaitString(char* prompt);

//ָ��λ�ô�ӡ
void PB_SetValue(const char* prompt, int col);

#endif // !PROMPT_BAR_H
