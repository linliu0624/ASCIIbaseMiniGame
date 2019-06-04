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
	queue<point> roomQue;
	point tp;
	tp.x = 1; tp.y = 1;
	roomQue.push(tp);
	int fx[4] = { -1,1,0,0 }, fy[4] = { 0,0,-1,1 };
	while (!roomQue.empty()) {
		tp = roomQue.front();  roomQue.pop();
		if (tp.x == MAPRANGE && tp.y == MAPRANGE)break;
		for (int i = 0; i < 4; i++) {
			if (tp.x + fx[i] < MAPRANGE && tp.y + fy[i] < MAPRANGE && tp.x + fx[i] > 0 && tp.y + fy[i] > 0)
			{
				point tmp;
				tmp.x = tp.x + fx[i];
				tmp.y = tp.y + fy[i];
				
			}
		}
	}
	return true;
}
