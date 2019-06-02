#pragma once
#include "define.h"

struct material {
	//weapon armor or item
	int mateTag;
	int weaponType;
	int armorType;
	int itemType;
	
	int atk;
	float def;
	int hp;
	int maxHp;
	int value;

	char name[32];
	char text[128];

	bool flag = false;
	bool drop;
};
extern material nothing;

extern material fist;
extern material sword;
extern material axe;
extern material spear;

extern material leatherArmor;
extern material heavyLeatherArmor;
extern material noArmor;

extern material simplePotion;

void WeaponOption();
void ArmorOption();
//void SetAtk();
void CreateVoid();
void ItemOption();