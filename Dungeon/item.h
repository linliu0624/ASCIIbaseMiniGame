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
	int atkType;
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

extern material simplePotion;

void WeaponInit();
void ArmorInit();
void CreateEmpty();
void ItemInit();
int Damage(int);