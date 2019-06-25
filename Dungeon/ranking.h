#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include "define.h"
//#pragma warning( disable : 4996 )
/*
從文件中把資料存到變數身上時，string遇到空白時候就會被分割
*/

struct ranking {
	char name[32];
	int score = 0;
	time_t time;
	string strTime;
};
extern ranking rank[RANK_LENGTH];
extern string fileName;
void InputFile(ranking[]);
void SortRank(ranking[]);
void OutputFile(ranking[], ranking);
void ShowRank(ranking[]);
void CreateFile();