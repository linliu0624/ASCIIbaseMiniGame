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



typedef struct ranking {
	char name[32];
	int score;
}tmpRank;

void inputFile(rank[], int);
void sortRank(rank[], int);
void outputFile(rank[], rank);

void inputFile(rank r[], int size) {
	//fstream file;
	//file.open("rank.txt", ios::out);//寫入文件
	ofstream file; //類似 file.open("....", ios::out) 
	file.open("rank.txt");
	for (int i = 0; i < size - 1; i++)
		file << r[i].name << " " << r[i].score << endl;
	file.close();
}
void outputFile(rank r[], rank newguy) {
	fstream file;
	file.open("rank.txt", ios::in);
	int n = 0;
	while (true) {
		file >> r[n].name;
		file >> r[n].score;
		cout << r[n].name << " " << r[n].score << endl;
		file << endl;
		n++;
		if (n == RANK_LENGTH - 1) {
			strcpy_s(r[n].name, newguy.name);
			r[n].score = newguy.score;
			break;
		}
	}
	file.close();
}
/*insert sort*/
void sortRank(rank r[], int size) {
	for (int i = 0; i < size; i++) {
		int n = i;
		rank tmp = r[n];
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
void main() {
	StartRnd();
	rank mainRank[RANK_LENGTH];
	for (int i = 0; i < RANK_LENGTH; i++) {
		strcpy_s(mainRank[i].name, "");
		mainRank[i].score = 0;
	}
	strcpy_s(mainRank[0].name, "kyon");
	strcpy_s(mainRank[1].name, "yume");
	strcpy_s(mainRank[2].name, "aa");
	strcpy_s(mainRank[3].name, "bb");
	strcpy_s(mainRank[4].name, "cc");
	strcpy_s(mainRank[5].name, "dd");
	strcpy_s(mainRank[6].name, "ee");
	for (int i = 0; i < RANK_LENGTH - 1; i++) {
		mainRank[i].score = rand() % 100;
	}
	rank newGuy;
	strcpy_s(newGuy.name, "newone");
	newGuy.score = rand() % 100;
	//outputFile(mainRank, newGuy);


	int size = sizeof(mainRank) / sizeof(rank);
	sortRank(mainRank, size);
	inputFile(mainRank, size);


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
