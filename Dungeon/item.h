#pragma once
#include "define.h"

struct material {
	//weapon armor or item
	int mateTag;
	int weaponType;
	int armorType;
	int itemType;

	int atk;
	int atkRange;
	int atkType;

	float def;
	int defType;
	int hp;
	int maxHp;

	char name[32];
	char text[128];
	int value;
	int amount;//用在背包的堆疊
	float weight;
	bool flag = false;
};
extern material nothing;

extern material fist;
extern material longSword;
extern material shortSword;
extern material banana;
extern material graduationCetificateTube;
extern material cutlass;
extern material battleAxe;
extern material kendama;
extern material obrist;
extern material marius;
extern material spear;
extern material pocky;
extern material gungnir;
extern material gaeBolg;
extern material scorpion;

extern material leatherArmor;
extern material heavyLeatherArmor;
extern material noArmor;
extern material chainmail;

extern material simplePotion;
extern material superPotion;

extern material gold;
extern material silver;
extern material ivory;
extern material brokenDiamond;

void WeaponInit();
void ArmorInit();
void CreateEmpty();
void ItemInit();
int Damage(int);