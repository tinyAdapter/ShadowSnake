#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include "shadow_snake.h"

extern std::vector<Rank> g_Ranks;

void RK_FromFile()
{
	Rank *rank = NULL;
	int n, i;
	FILE *fp;

	errno_t err = fopen_s(&fp, "ranks.txt", "r");//���ļ�
	if (err)
	{
		LOG_WriteError("�����а��ļ�ʧ��");
	}


	fscanf_s(fp, "%d\n", &n);
	if (n <= 0)//���������Ƿ�
	{
		fclose(fp);
		return;
	}
	rank = (Rank*)malloc(sizeof(Rank));//�����ڴ�ռ�
	for (i = 0; i < n; i++)
	{
		if (fscanf_s(fp, "%d %s %d", &rank->list, &rank->name, 20, &rank->grades) != 3)
		{
			break;//��ȡ����
		}
		g_Ranks.push_back(*rank);
	}

	fclose(fp);//�ر��ļ�
	free(rank);//�ͷ��ڴ�
}

void RK_Trim()
{
	// ���ݳɼ�����
	for (size_t i = 0; i < g_Ranks.size(); i++)
	{
		for (size_t j = g_Ranks.size() - 1; j > i; j--)
		{
			if (g_Ranks[j].grades > g_Ranks[i].grades)
				std::swap(g_Ranks[i], g_Ranks[j]);
		}
	}

	// Vacuum
	for (size_t i = 0; i < g_Ranks.size(); i++)
	{
		g_Ranks[i].list = i + 1;
	}
	for (size_t i = 0; i < g_Ranks.size() - 1; i++)
	{
		if (g_Ranks[i].grades == g_Ranks[i + 1].grades)
		{
			g_Ranks[i + 1].list = g_Ranks[i].list;
		}
	}
}

void RK_Show()
{
	if (g_Ranks.size() == 0)
	{
		RK_FromFile();
	}
	CS_InitWindow();

	CS_Print(50, 14, "����\t����\t����");
	for (size_t i = 0; i < g_Ranks.size(); i++)
	{
		CS_SetPosition(50, 15+i);
		printf("%-d\t%s\t%-d\n", g_Ranks[i].list, g_Ranks[i].name, g_Ranks[i].grades);

	}
	_getch();
}

void RK_ToFile()
{
	FILE *fp = NULL;
	if (fopen_s(&fp, "ranks.txt", "w"))
	{
		LOG_WriteError("�����а��ļ�ʧ��");
		return;
	}

	fprintf(fp, "%d\n", g_Ranks.size());

	for (size_t i = 0; i < g_Ranks.size(); i++)
	{
		fprintf(fp, "%d\t%s\t%d\n", g_Ranks[i].list, g_Ranks[i].name, g_Ranks[i].grades);
	}

	fclose(fp);
}

void RK_Store()
{
	bool flag = false;
	for (size_t i = 0; i < g_Ranks.size(); i++)
	{
		if (g_Ranks[i].grades < g_Score)
		{
			flag = true;
		}
	}
	if (flag)
	{
		Rank rank;
		strcpy_s(rank.name, g_Name);
		rank.list = 0;
		rank.grades = g_Score;
		g_Ranks.push_back(rank);
		RK_Trim();
		g_Ranks.pop_back();
		RK_ToFile();

		LOG_WriteInfo("new rank");
	}
}