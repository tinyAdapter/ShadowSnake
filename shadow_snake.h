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

extern bool g_IsMusicOn;			//音乐开关
extern std::vector<Rank> g_Ranks;	//排行榜数据
extern char g_Name[20];				//角色名
extern int g_HP;					//角色生命值
extern int g_Score;					//所得分数
extern int g_Mode;					//蛇的模式
extern double g_Speed;				//蛇的速度
extern int g_Power;					//当前能量
extern char g_GameView[32][96];		//蛇，食物位置
extern std::list<COORD> g_Snake;	//蛇各部分坐标
extern char g_GameTile[32][96];		//地形矩阵
extern int g_GetFood;				//是否获得食物
extern unsigned int g_Level;		//当前关卡数
extern char g_UserInput;			//用户输入
extern char g_GameView_Old[32][96]; //蛇，食物位置缓存
extern unsigned int g_Food;			//场景中食物数量
extern int g_SnakeColor;			//蛇的颜色
extern unsigned int g_ModeRemainStep;	//技能剩余步数
extern COORD g_LastHead;			//上一时刻蛇头位置
extern char g_Mode_Input;			//用户释放技能
extern bool g_EndGame;				//游戏是否结束

#endif // !SHADOW_SNAKE_H
