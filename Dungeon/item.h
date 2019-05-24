#pragma once
#include "define.h"

struct material {
	//weapon armor or item
	int mateTag;

	int weaponType;
	
	int armorType;
	
	int atk;
	float def;
	int hp;
	int value;

	char name[32];

	bool flag = false;
	bool drop;
};
extern material nothing;

extern material fist;
extern material sword;
extern material leatherArmor;
extern material noArmor;

void WeaponOption();
void ArmorOption();
void SetAtk(int);
void CreateVoid();