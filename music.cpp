#include <Windows.h>
#include "shadow_snake.h"

#pragma comment(lib,"winmm.lib")

void MS_Refresh()
{
	if (g_IsMusicOn == true)
	{
		LOG_WriteInfo("音乐开");
		//音乐开
		mciSendString(TEXT("resume bgm"), NULL, 0, NULL);
	}
	else
	{
		LOG_WriteInfo("音乐关");
		//音乐关
		mciSendString(TEXT("pause bgm"), NULL, 0, NULL);
	}
}