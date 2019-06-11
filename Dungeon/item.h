#pragma once
#include "define.h"

struct material {
	//weapon armor or item
	int mateTag;
	int weaponType;
	int armorType;
	int itemType;

	char name[32];
	char text[128];
	
	int atk;
	int atkRange;
	int hp;
	int maxHp;
	int value;

	float weight;
	float def;

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

void WeaponInit();
void ArmorInit();
void CreateEmpty();
void ItemInit();
int Damage(int);