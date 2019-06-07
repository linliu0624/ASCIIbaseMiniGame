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
//#pragma warning( disable : 4996 )
using namespace std;
#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75
void StartRnd();
inline void GotoXY(int, int);
struct map {
	int x, y, n;
	bool flag = false;
	bool goAble;
	bool isMark;
} a[5][5];
void Search(int, int);
int fx[4] = { -1,1,0,0 }, fy[4] = { 0,0,-1,1 };
struct point {
	int x, y;
};
void main() {

	StartRnd();
	a[0][0].isMark = true;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			int n = rand() % 3 + 1;
			a[i][j].y = i;
			a[i][j].x = j;
			if ((i == 0 && j == 0) || (i == 4 && j == 4)) {
				a[i][j].n = 0;
				a[i][j].goAble = true;
			}

			else
				if (n == 3) {
					a[i][j].n = 1;
					a[i][j].goAble = false;
				}
				else {
					a[i][j].n = 0;
					a[i][j].goAble = true;
				}

		}
	}
	

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cout << a[i][j].n << " ";
		}
		cout << endl;
	}

	Search(0, 0);

	cout << endl;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (a[i][j].goAble == true && a[i][j].isMark == true) {
				cout << "X ";
			}
			else {
				cout << a[i][j].n << " ";
			}
		}
		cout << endl;
	}
}

void Search(int x, int y) {
	queue<point> myque;
	point tp;
	tp.x = x; tp.y = y; //初始化开始节点dis设为0
	myque.push(tp);
	do
	{
		tp = myque.front(); myque.pop();//从队头取节点
		for (int i = 0; i < 4; i++)
		{
			if (tp.x + fx[i] < 5 && tp.x + fx[i] >= 0 && tp.y + fy[i] < 5 &&
				tp.y + fy[i] >= 0 && a[tp.x + fx[i]][tp.y + fy[i]].n == 0)
			{
				point tmp;
				tmp.x = tp.x + fx[i];
				tmp.y = tp.y + fy[i];
				if (!a[tmp.x][tmp.y].isMark)
					myque.push(tmp);
				a[tmp.x][tmp.y].isMark = true;
			}
		}
		//cout << myque.front().x << "," << myque.front().y << endl;
		//cout << myque.size() << endl;
		/*for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (a[i][j].goAble == true && a[i][j].isMark == true) {
					cout << "X ";
				}
				else {
					cout << a[i][j].n << " ";
				}
			}
			cout << endl;
		}*/
	} while (!myque.empty());
}
void StartRnd() {
	unsigned seed;
	seed = (unsigned)time(NULL);
	srand(seed);
}
/*画面の座標を(x,y)に移動する*/
inline void GotoXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
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
