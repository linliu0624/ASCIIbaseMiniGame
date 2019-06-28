// Test.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
#include "pch.h"
#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <malloc.h>
#include <time.h>
#include <stack>
#include <queue>
#include "conio.h"
#include "direct.h"
#include "test.h"
#include <math.h>
#include <fstream>
#include <string>
#include <time.h>
//#pragma warning( disable : 4996 )
using namespace std;
#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75
#define RANK_LENGTH 8
void StartRnd();
inline void GotoXY(int, int);
/*
從文件中把資料存到變數身上時，string遇到空白時候就會被分割
*/
struct ranking {
	char name[32];
	int score = 0;
	time_t nowTime = time(0);
	string sTime;
};
ranking arank[RANK_LENGTH];
string fileName = "rank.txt";
void InputFile(ranking[]);
void SortRank(ranking[], ranking);
void OutputFile(ranking[]);
void ShowRank(ranking[]);

void main() {
	ranking tmp;
	cout << "what's you name:";
	cin >> tmp.name;
	cout << "set score:";
	cin >> tmp.score;

	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&tmp.nowTime);
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
	tmp.sTime = buf;

	OutputFile(arank);
	SortRank(arank, tmp);
	InputFile(arank);
	ShowRank(arank);
}
/*把資料從Code寫進文件*/
void InputFile(ranking r[]) {
	//fstream file;
	//file.open("rank.txt", ios::out);//寫入文件
	ofstream file; //類似 file.open("....", ios::out) 
	file.open(fileName);
	if (file)
		for (int i = 0; i < RANK_LENGTH - 1; i++)
			if (r[i].score > 0)
				file << r[i].name << " " << r[i].score << " " << r[i].sTime << endl;
	file.close();
}
/*把文件中的資料存進code*/
void OutputFile(ranking r[]) {
	fstream file;
	file.open(fileName, ios::in);
	int n = 0;
	while (!file.eof() && file) {
		file >> r[n].name;
		file >> r[n].score;
		file >> r[n].sTime;
		file << endl;
		n++;
	}
	file.close();
}
/*insert sort*/
void SortRank(ranking r[], ranking newPlayer) {
	if (newPlayer.score > r[RANK_LENGTH - 1].score) {
		r[RANK_LENGTH - 1] = newPlayer;
	}
	for (int i = 0; i < RANK_LENGTH; i++) {
		int n = i;
		ranking tmp = r[n];
		while (i > 0) {
			if (r[n].score > r[n - 1].score && n > 0) {
				r[n] = r[n - 1];
				r[n - 1] = tmp;
				n--;
			}
			else
				break;
		}
	}
}

void ShowRank(ranking r[]) {
	cout << "No.  Name          Score      time" << endl;
	cout << "================================================" << endl;
	int n = 1;
	for (int i = 0; i < RANK_LENGTH - 1; i++) {
		if (r[i].score > 0) {
			cout << n << ".   " << r[i].name << "          " << r[i].score << "      " << r[i].sTime << endl;
			if (r[i].score != r[i + 1].score) {
				n++;
			}
		}
	}
}

inline void GotoXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void StartRnd() {
	unsigned seed;
	seed = (unsigned)time(NULL);
	srand(seed);
}
// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的秘訣: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案
