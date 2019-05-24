// Test.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//
#include "pch.h"
#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <malloc.h>
#include <time.h>
#include "conio.h"
#include "direct.h"
#include "test.h"
#include <math.h>
//#pragma warning( disable : 4996 )
using namespace std;
int cont(int x, int y) {
	int ans;
	int a = (0 - x);
	int b = (4 - y);
	ans = abs(a * a + b * b);
	return ans;
}
int curv(int x, int y) {
	int ans;
	int a = (0 - 2 * x + 3);
	int b = (4 - 2 * y + 4);
	ans = abs(a*a + b * b);
	return ans;
}
int main()
{
	int ans;
	ans = cont(2, 3) + curv(2, 3);
	cout << ans << endl;
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
