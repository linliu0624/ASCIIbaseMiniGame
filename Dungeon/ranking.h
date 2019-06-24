#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "define.h"
//#pragma warning( disable : 4996 )
/*
從文件中把資料存到變數身上時，string遇到空白時候就會被分割
*/

 struct ranking {
	char name[32];
	int score;
};
extern ranking rank[RANK_LENGTH];
extern string fileName;
void inputFile(ranking[], int);
void sortRank(ranking[], int);
void outputFile(ranking[], ranking);

