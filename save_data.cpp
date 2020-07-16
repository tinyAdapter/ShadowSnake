#include <stdio.h>
#include "shadow_snake.h"

/*��Ϸ�浵*/
void SD_SaveAll()
{
	FILE *pFile;
	errno_t err = fopen_s(&pFile, "save.dat", "wb");
	if (err)
	{
		LOG_WriteError("�浵�ļ���ʧ��");
		return;
	}
	fwrite(&g_Name, sizeof(char), 20, pFile);			//��ɫ��
	fwrite(&g_HP, sizeof(int), 1, pFile);				//��ɫ����ֵ
	fwrite(&g_Score, sizeof(int), 1, pFile);			//���÷���
	fwrite(&g_Mode, sizeof(int), 1, pFile);				//�ߵ�ģʽ
	fwrite(&g_Speed, sizeof(double), 1, pFile);			//�ߵ��ٶ�
	fwrite(&g_Power, sizeof(int), 1, pFile);			//��ǰ����
	fwrite(&g_GameView, sizeof(char), 32 * 96, pFile);	//�洢�ߣ�ʳ��λ��
	fwrite(&g_GameTile, sizeof(char), 32 * 96, pFile);	//�洢���εľ���
	int size = g_Snake.size();
	fwrite(&size, sizeof(int), 1, pFile);
	for (std::list<COORD>::iterator it = g_Snake.begin(); it != g_Snake.end(); it++)
	{
		fwrite(&*it, sizeof(COORD), 1, pFile);//�洢����λ��
	}
	fwrite(&g_UserInput, sizeof(char), 1, pFile);		//�����û�����
	fwrite(&g_GetFood, sizeof(int), 1, pFile);			//�˿��Ƿ�Ե�ʳ��
	fwrite(&g_Level, sizeof(int), 1, pFile);			//��ǰ�����ؿ��ȼ�
	fwrite(&g_Food, sizeof(int), 1, pFile);				//��Ϸ������ʳ������
	fwrite(&g_GameView_Old, sizeof(char), 32 * 96, pFile); 	//�ߣ�ʳ��λ�û���
	fwrite(&g_SnakeColor, sizeof(int), 1, pFile);		//�ߵ���ɫ
	fwrite(&g_ModeRemainStep, sizeof(int), 1, pFile);	//�߼���ʣ��ʱ��
	fwrite(&g_LastHead, sizeof(COORD), 1, pFile);		//��¼��һ����ͷλ��
	fclose(pFile);
	return;
}

/*�ָ��浵*/
void SD_LoadAll()
{
	FILE *pFile;
	errno_t err = fopen_s(&pFile, "save.dat", "rb");
	if (err)
	{
		LOG_WriteError("�浵�ļ���ʧ��");
		return;
	}
	fread(&g_Name, sizeof(char), 20, pFile);			//��ɫ��
	fread(&g_HP, sizeof(int), 1, pFile);				//��ɫ����ֵ
	fread(&g_Score, sizeof(int), 1, pFile);				//���÷���
	fread(&g_Mode, sizeof(int), 1, pFile);				//�ߵ�ģʽ
	fread(&g_Speed, sizeof(double), 1, pFile);			//�ߵ��ٶ�
	fread(&g_Power, sizeof(int), 1, pFile);				//��ǰ����
	fread(&g_GameView, sizeof(char), 32 * 96, pFile);	//�洢�ߣ�ʳ��λ��
	fread(&g_GameTile, sizeof(char), 32 * 96, pFile);	//�洢���εľ���
	int size = 0;
	fread(&size, sizeof(int), 1, pFile);
	g_Snake.clear();
	for (int i = 0; i < size; i++)
	{
		COORD c;
		fread(&c, sizeof(COORD), 1, pFile);//�洢����λ��
		g_Snake.push_back(c);
	}
	fread(&g_UserInput, sizeof(char), 1, pFile);		//�����û�����
	fread(&g_GetFood, sizeof(int), 1, pFile);			//�˿��Ƿ�Ե�ʳ��
	fread(&g_Level, sizeof(int), 1, pFile);				//��ǰ�����ؿ��ȼ�
	fread(&g_Food, sizeof(int), 1, pFile);				//��Ϸ������ʳ������
	fread(&g_GameView_Old, sizeof(char), 32 * 96, pFile); 	//�ߣ�ʳ��λ�û���
	fread(&g_SnakeColor, sizeof(int), 1, pFile);		//�ߵ���ɫ
	fread(&g_ModeRemainStep, sizeof(int), 1, pFile);	//�߼���ʣ��ʱ��
	fread(&g_LastHead, sizeof(COORD), 1, pFile);		//��¼��һ����ͷλ��
	fclose(pFile);
	return;
}
