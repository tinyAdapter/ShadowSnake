#ifndef RANKING_H
#define RANKING_H

/*���а�*/
typedef struct
{
	int list;
	char name[100];
	int grades;
}Rank;

/*���а���������*/
void RK_Trim();

/*��ӡ���а�*/
void RK_Show();

/*�洢���а����ݵ��ļ�*/
void RK_ToFile();

/*�洢��ǰ������ݵ����а�*/
void RK_Store();

/*���ļ���ȡ���а�����*/
void RK_FromFile();

#endif // !RANKING_H
