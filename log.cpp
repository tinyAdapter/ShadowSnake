#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "shadow_snake.h"

//获得时间
void getLocalTime(char* buffer)
{
	time_t rawtime;
	tm *timeinfo = new tm;
	time(&rawtime);
	localtime_s(timeinfo,&rawtime);
	sprintf_s(buffer, 30, "[%04d/%02d/%02d %02d:%02d:%02d]",
		(timeinfo->tm_year + 1900), timeinfo->tm_mon, timeinfo->tm_mday,
		timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
	delete timeinfo;
}


bool LOG_WriteError(const char* log)
{
	if (log != NULL)
	{
		FILE *pFile;
		fopen_s(&pFile, "shadowsnake.log", "a+");
		char buffer[30];
		getLocalTime(buffer);				//获得时间
		char error[] = " Error: ";
		strcat_s(buffer, error);
		size_t size = strlen(log) + sizeof(buffer);
		char *all = (char*)malloc(size);	//之前用sizeof（log）出错计算的是指针的长度
		strcpy_s(all, size, buffer);				//将blog与buffer中的数据存到all中
		strcat_s(all, size, log);
		fprintf(pFile, "%s\n", all);

		fclose(pFile);
		free(all);
		all = NULL;

		exit(-1);

		return true;
	}
	else
		return false;

}


bool LOG_WriteWarning(const char* log)
{
	if (log != NULL)
	{
		FILE *pFile;
		fopen_s(&pFile, "shadowsnake.log", "a+");
		char buffer[32];
		getLocalTime(buffer);      //获得时间
		char warning[] = " Warning: ";
		strcat_s(buffer, warning);
		size_t size = strlen(log) + sizeof(buffer);
		char *all = (char*)malloc(size);	//之前用sizeof（log）出错计算的是指针的长度
		strcpy_s(all, size, buffer);				//将blog与buffer中的数据存到all中
		strcat_s(all, size, log);
		fprintf(pFile, "%s\n", all);

		fclose(pFile);
		free(all);
		all = NULL;
		return true;
	}
	else
		return false;
}
bool LOG_WriteInfo(const char* log)
{
	if (log != NULL)
	{
		FILE *pFile;
		errno_t err = fopen_s(&pFile, "shadowsnake.log", "a+");
		char buffer[30];
		getLocalTime(buffer);      //获得时间
		char info[] = " Info: ";
		strcat_s(buffer, info);
		size_t size = strlen(log) + sizeof(buffer);
		char *all = (char*)malloc(size);	//之前用sizeof（log）出错计算的是指针的长度
		strcpy_s(all, size, buffer);				//将blog与buffer中的数据存到all中
		strcat_s(all, size, log);
		fprintf(pFile, "%s\n", all);

		fclose(pFile);
		free(all);
		all = NULL;
		return true;
	}
	else
		return false;
}


