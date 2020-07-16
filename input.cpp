#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "shadow_snake.h"

int IN_GetInt(int min, int max, const char* prompt) {

	int numberData = 0, flag = 0;
	char temp[MAX_CHARACTER];
	CS_ClearByCoord(0, 35, 1, 120);
	CS_Print(0, 35, prompt);
	do {
		int count = 0;//记住用户输入的个数

		scanf_s("%s", temp, MAX_CHARACTER);
		numberData = atoi(temp);
		if (numberData < min || numberData >max) {
			flag = 1;
			CS_ClearByCoord(0, 35, 1, 120);
			CS_Print(0, 35, "请重新输入: ");
		}
		else
			flag = 0;
	} while (flag);
	return numberData;
}

double IN_GetDouble(double min, double max, char * prompt) {
	double numberData = 0, flag = 0;
	char temp[MAX_CHARACTER];
	CS_ClearByCoord(0, 35, 1, 120);
	CS_Print(0, 35, prompt);
	printf("%s", prompt);
	do {
		int count = 0;//记住用户输入的个数

		scanf_s("%s", temp, MAX_CHARACTER);
		numberData = strtod(temp, NULL);
		if (numberData < min || numberData >max) {
			flag = 1;
			CS_ClearByCoord(0, 35, 1, 120);
			CS_Print(0, 35, "请重新输入: ");
		}
		else
			flag = 0;
	} while (flag);
	return numberData;
}

char IN_GetChar(char valid[], char *prompt) {

	char temp;
	size_t length = strlen(valid);
	int flag = 1;
	CS_ClearByCoord(0, 35, 1, 120);
	CS_Print(0, 35, prompt);
	do {
		temp = _getch();
		printf("%c", temp);
		_getch();
		for (size_t i = 0; i < length; i++)
		{
			if (temp == valid[i]) {
				flag = 0;
				break;
			}
		}
		if(flag==1){
			CS_ClearByCoord(0, 35, 1, 120);
			CS_Print(0, 35, "请重新输入: ");
		}
	} while (flag);
	return temp;
}

char* IN_GetString(char* prompt) {

	char* name = (char*)malloc(10);
	memset(name, 0, MAX_NAME);

	CS_ClearByCoord(0, 35, 1, 120);
	CS_SetPosition(0, 35);
	printf("%s", prompt);
	scanf_s("%9s", name, 10);
	return name;
}
