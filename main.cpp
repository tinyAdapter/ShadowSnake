#include <windows.h>
#include <vector>
#include "shadow_snake.h"

#pragma comment(lib,"winmm.lib")

/*全局变量区*/
bool g_IsMusicOn = true;			//音乐开关
std::vector<Rank> g_Ranks;			//排行榜数据
char g_Name[20];					//角色名
int g_HP;							//角色生命值
int g_Score;						//所得分数
int g_Mode;							//蛇的模式
double g_Speed;						//蛇的速度
int g_Power;						//当前能量
char g_GameView[32][96] = { 0 };	//存储蛇，食物位置
char g_GameTile[32][96] = { 0 };	//存储地形的矩阵
std::list<COORD> g_Snake;			//存储蛇身位置
char g_UserInput;                   //保留用户输入
int g_GetFood;						//是否获得食物
unsigned int g_Level;				//当前关卡数
unsigned int g_Food;				//场景中食物数量
char g_GameView_Old[32][96];		//蛇，食物位置缓存
int g_SnakeColor = 7;				//蛇的颜色
unsigned int g_ModeRemainStep = 0;	//技能剩余步数
char g_Mode_Input = ' ';			//用户释放技能
bool g_EndGame;						//游戏是否结束
COORD g_LastHead = { 50,18 };		//记录上一次蛇头位置


/*主函数*/
int main()
{
	/*初始化*/
	CS_InitWindow();
	CS_SetColor(7, 0);
	//从文件读取排行榜数据
	RK_FromFile();	
	// 音乐开
	mciSendString(L"open music.mp3 alias bgm", NULL, 0, NULL);
	mciSendString(L"play bgm repeat", NULL, 0, 0);
	/*主循环*/
	while (true)
	{
		MMU_ShowMainMenu();
		//接收用户输入
		int choice = PB_WaitInt(1, 5, "请输入1-5： ");
		switch (choice)
		{
		case 1:
			GP_NewGame();
			break;
		case 2:
			GP_LoadGame();
			break;
		case 3:
		{
			char choiceSettings = '\0';
			while (choiceSettings != 'q')
			{
				//打印设置界面
				MMU_ShowSettingsMenu();
				//接收用户输入
				char c[3] = { 'y','n','q' };
				choiceSettings = PB_WaitChar(c, "请输入设置（按q退出)： ");
				switch (choiceSettings)
				{
				case 'y':
					g_IsMusicOn = true;
					MS_Refresh();	//刷新音乐设置
					break;
				case 'n':
					g_IsMusicOn = false;
					MS_Refresh();	//刷新音乐设置
					break;
				default:
					break;
				}
			}
		}
		break;
		case 4:
			RK_Show();	//打印排行榜
			break;
		case 5:
			RT_Exit(0);
			break;
		default:
			break;
		}
	}
}