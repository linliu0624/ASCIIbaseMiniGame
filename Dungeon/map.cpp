#include "pch.h"
#include "map.h"
#include "define.h"
#include <queue>
using namespace std;
bigmap dangeon[MAPRANGE][MAPRANGE];
roomObj room[ROOMRANGE][ROOMRANGE];
struct point {
	int x, y;
};
bool SearchRoom()
{
	int walkAbleNum = 0, isMarkNum = 0;;
	queue<point> roomQue;
	point tp;
	tp.x = 1; tp.y = 1;
	roomQue.push(tp);
	int fx[4] = { -1,1,0,0 }, fy[4] = { 0,0,-1,1 };//0¥ª 1¥k 2¤W 3¤U
	do {
		tp = roomQue.front();  roomQue.pop();
		for (int i = 0; i < 4; i++) {
			if (tp.x + fx[i] < ROOMRANGE && tp.y + fy[i] < ROOMRANGE && tp.x + fx[i] > 0 && tp.y + fy[i] > 0 &&
				room[tp.y + fy[i]][tp.x + fx[i]].type == FLOOR)
			{
				point tmp;
				tmp.x = tp.x + fx[i];
				tmp.y = tp.y + fy[i];
				if (!room[tmp.y][tmp.x].mark)
					roomQue.push(tmp);
				room[tmp.y][tmp.x].mark = true;
				
			}
		}
	} while (!roomQue.empty());

	for (int i = 1; i < ROOMRANGE; i++) {
		for (int j = 1; j < ROOMRANGE; j++) {
			if (room[i][j].type == FLOOR)
				walkAbleNum++;
			if (room[i][j].mark) {
				isMarkNum++;
			}
		}
	}
	cout << walkAbleNum << " | " << isMarkNum << endl;
	
	if (walkAbleNum == isMarkNum)
		return true;
	else
		return false;
}
