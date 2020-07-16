#ifndef RANKING_H
#define RANKING_H

/*排行榜*/
typedef struct
{
	int list;
	char name[100];
	int grades;
}Rank;

/*排行榜数据排序*/
void RK_Trim();

/*打印排行榜*/
void RK_Show();

/*存储排行榜数据到文件*/
void RK_ToFile();

/*存储当前玩家数据到排行榜*/
void RK_Store();

/*从文件读取排行榜数据*/
void RK_FromFile();

#endif // !RANKING_H
