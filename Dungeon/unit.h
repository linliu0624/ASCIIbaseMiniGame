#pragma once
#include "define.h"
#include "item.h"
struct unit {
	//�@�P
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


	//���a
	float maxWeight;
	float weight;
	char name[32] = { NULL };
	int loan = 0;
	bool inventoryMode = false;
	//�ĤH
	bool samePosWithPlayer = false;
	bool moveWay = true; //�ĤH�����ʼҦ�
};

