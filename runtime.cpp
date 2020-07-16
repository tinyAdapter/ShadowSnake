#include <stdio.h>
#include <Windows.h>
#include "shadow_snake.h"

//跳转到某一状态   
/*1-世界变慢；2-穿墙，穿越障碍物；3-吸附周围的食物*/
void RT_JumpToState(int stateId)
{
	if (stateId == 1 || stateId == 2 || stateId == 3)
	{
		switch (stateId)
		{
		case 1:
			g_Speed -= 0.2;
			break;
		case 2:
			g_Mode = 2;

			break;
		case 3:
			g_Mode = 3;
			break;
		}
	}
}

void RT_Pause(bool isDead, const char* prompt)
{
	char *choice1, *choice2 = " 2.退出游戏";
	if (isDead && g_HP)
		choice1 = "1.重新开始";
	else if (isDead || g_Level == 6)
		choice1 = "1.回到主菜单";
	else
	{
		choice1 = "1.恢复游戏";
		choice2 = " 2.保存并退出";
	}
	std::string s;
	int result = IN_GetInt(1, 2, (s.append(prompt).append("[").append(choice1).append(choice2).append("] ")).c_str());
	switch (result)
	{
	case 1:
		if (isDead && g_HP)//剩余生命时死亡
		{
			GP_ToNextLevel();
		}
		else if (isDead || g_Level == 6) //通关或无生命剩余
		{
			CS_SetColor(7, 0);
			g_EndGame = true;
		}
		else//游戏中暂停
		{
			//重新开始
		}
		break;
	case 2:
		if (!isDead)
		{
			SD_SaveAll();
		}
		g_EndGame = true;
		break;
	}
}

//退出游戏 0-正常 -1-错误退出
void RT_Exit(int exitCode)
{
	switch (exitCode)
	{
	case 0:
		//关闭音乐
		mciSendString(TEXT("close bgm"), NULL, 0, NULL);
		exit(0);
		break;
	case -1:
		LOG_WriteInfo("Program exit with code 0xffffffff");
		exit(-1);
		break;
	}
}
