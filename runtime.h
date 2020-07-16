#ifndef RUNTIME_H
#define RUNTIME_H

//截取屏幕上的所有数据；
void interceptScreenStrings();

//跳转到某一状态
void RT_JumpToState(int stateId);

//暂停游戏
void RT_Pause(bool isDead, const char* prompt = "暂停");

//恢复游戏
void RT_Resume();

//退出游戏
void RT_Exit(int exitCode);

#endif
