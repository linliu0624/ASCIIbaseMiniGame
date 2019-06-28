#pragma once
#include "define.h"
#include "item.h"
struct unit {
	//共同
	int type;
	int mapX;
	int mapY;
	int roomX;
	int firstRoomX;
	int firstRoomY;
	int roomY;
	int maxHp;
	int hp;
	material weapon;
	material armor;
	material inventory[MAX_INVENTORY];
	bool alive;


	//玩家
	float maxWeight;
	float weight;
	char name[32] = { NULL };
	int loan = 0;
	bool inventoryMode = false;
	//敵人
	bool samePosWithPlayer = false;
	bool moveWay = true; //敵人的移動模式
};

