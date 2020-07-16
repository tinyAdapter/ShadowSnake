#ifndef SHADOW_SNAKE_H
#define SHADOW_SNAKE_H

#include <vector>
#include <list>
#include <windows.h>

#include "console.h"
#include "drama.h"
#include "input.h"
#include "log.h"
#include "main_menu.h"
#include "music.h"
#include "prompt_bar.h"
#include "ranking.h"
#include "status_table.h"
#include "runtime.h"
#include "game_process.h"
#include "mini_map.h"
#include "snake.h"
#include "game_view.h"
#include "save_data.h"

extern bool g_IsMusicOn;			//���ֿ���
extern std::vector<Rank> g_Ranks;	//���а�����
extern char g_Name[20];				//��ɫ��
extern int g_HP;					//��ɫ����ֵ
extern int g_Score;					//���÷���
extern int g_Mode;					//�ߵ�ģʽ
extern double g_Speed;				//�ߵ��ٶ�
extern int g_Power;					//��ǰ����
extern char g_GameView[32][96];		//�ߣ�ʳ��λ��
extern std::list<COORD> g_Snake;	//�߸���������
extern char g_GameTile[32][96];		//���ξ���
extern int g_GetFood;				//�Ƿ���ʳ��
extern unsigned int g_Level;		//��ǰ�ؿ���
extern char g_UserInput;			//�û�����
extern char g_GameView_Old[32][96]; //�ߣ�ʳ��λ�û���
extern unsigned int g_Food;			//������ʳ������
extern int g_SnakeColor;			//�ߵ���ɫ
extern unsigned int g_ModeRemainStep;	//����ʣ�ಽ��
extern COORD g_LastHead;			//��һʱ����ͷλ��
extern char g_Mode_Input;			//�û��ͷż���
extern bool g_EndGame;				//��Ϸ�Ƿ����

#endif // !SHADOW_SNAKE_H
