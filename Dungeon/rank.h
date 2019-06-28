#pragma once
#include <time.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "define.h"
struct ranking {
	char name[32];
	int score = 0;
	time_t nowTime = time(0);
	std::string strTime;
};
extern ranking gameRank[RANK_LENGTH];
extern std::string fileName;
void InputFile(ranking[]);
void SortRank(ranking[], ranking);
void OutputFile(ranking[]);
void MakeFile();
//void ShowRank(ranking[]);