#pragma once
#include "define.h"
#include "item.h"
struct unit {
	//共同
	int type;
	int mapX;
	int mapY;
	int roomX;
	int roomY;
	int maxHp;
	int hp;
	material weapon;
	material armor;
	material inventory[64];
	bool alive;
	
	
	//玩家
	char name[100];
	bool inventoryMode = false;
	//敵人
	bool samePosWithPlayer = false;
	bool attackAble = false;
};

