#include"pch.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include"item.h"

material fist;
material sword;
material spear;
material axe;

material noArmor;
material leatherArmor;
material nothing;

void WeaponOption() {
	//拳
	strcpy(fist.name, "fist");
	strcpy(fist.text, "~ Just hands, attack distance is one. atk=1~4 ~");
	fist.mateTag = WEAPON;
	fist.weaponType = FIST;
	fist.value = 0;
	fist.flag = true;
	

	//剣
	strcpy(sword.name, "long sword");
	sword.mateTag = WEAPON;
	sword.weaponType = SWORD;
	sword.value = 15;
	sword.flag = true;

	//斧
	strcpy(axe.name, "axe");
	axe.mateTag = WEAPON;
	axe.weaponType = AXE;
	axe.value = 20;
	axe.flag = true;

	//槍
	strcpy(spear.name, "spear");
	spear.mateTag = WEAPON;
	spear.weaponType = SPEAR;
	spear.value = 20;
	spear.flag = true;
}
void ArmorOption() {
	//裸体
	strcpy(noArmor.name, "no armor");
	noArmor.mateTag = ARMOR;
	noArmor.armorType = NO_ARMOR;
	noArmor.value = 0;
	noArmor.def = 0;
	noArmor.maxHp = 0;
	noArmor.hp = noArmor.maxHp;
	noArmor.flag = true;

	//皮甲
	strcpy(leatherArmor.name, "leather armor");
	leatherArmor.mateTag = ARMOR;
	leatherArmor.armorType = LEATHER_ARMOR;
	leatherArmor.value = 30;
	leatherArmor.flag = true;
	leatherArmor.maxHp = 40;
	leatherArmor.hp = leatherArmor.maxHp;
	leatherArmor.def = 0.33f;
}
void CreateVoid() {
	strcpy(nothing.name, "nothing");
	nothing.mateTag = NOTHING;
	nothing.value = 0;
	nothing.flag = false;
}
/*攻擊力計算*/
//void SetAtk() {
//
//	int dice4 = rand() % 4 + 1;
//	int dice6 = rand() % 6 + 1;
//	int dice8 = rand() % 8 + 1;
//	int dice10 = rand() % 10 + 1;
//	int dice20 = rand() % 20 + 1;
//
//	fist.atk = dice4;
//	sword.atk = dice6 + 2;
//}

