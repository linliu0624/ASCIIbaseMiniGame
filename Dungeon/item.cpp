﻿/*
*作者：横林
*/
#include"pch.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include"item.h"

material fist;
material longSword;
material shortSword;
material banana;
material graduationCetificateTube;
material cutlass;

material battleAxe;
material kendama;
material marius;
material obrist;

material spear;
material pocky;
material gungnir;
material gaeBolg;
material scorpion;

material noArmor;
material leatherArmor;
material heavyLeatherArmor;
material chainmail;
material nothing;

material simplePotion;
material superPotion;

material gold;
material silver;
material ivory;
material brokenDiamond;
void WeaponInit() {
	//拳
	strcpy(fist.name, "fist");
	strcpy(fist.text, "~ Just hands, attack distance is one. atk=1~4 ~");
	fist.mateTag = WEAPON;
	fist.weaponType = FIST;
	fist.value = 0;
	fist.weight = 0.0f;
	fist.atkRange = ONE;
	fist.atkType = CUT_STAB;
	fist.flag = true;

	//長剣
	strcpy(longSword.name, "long sword");
	longSword.mateTag = WEAPON;
	longSword.weaponType = LONG_SWORD;
	longSword.value = 15;
	longSword.weight = 2.0f;
	longSword.atkRange = ONE;
	longSword.atkType = CUT_STAB;
	longSword.flag = true;
	//短剣
	strcpy(shortSword.name, "short sword");
	shortSword.mateTag = WEAPON;
	shortSword.weaponType = SHORT_SWORD;
	shortSword.value = 15;
	shortSword.atkRange = ONE;
	shortSword.atkType = CUT_STAB;
	shortSword.flag = true;
	//バナナ剣
	strcpy(banana.name, "banana");
	banana.mateTag = WEAPON;
	banana.weaponType = BANANA;
	banana.value = 15;
	banana.atkRange = ONE;
	banana.atkType = CUT_STAB;
	banana.flag = true;
	//卒業証書剣
	strcpy(graduationCetificateTube.name, "sotsugyoshosho no tsutsu");
	graduationCetificateTube.mateTag = WEAPON;
	graduationCetificateTube.weaponType = GRADUATION_CERTIFICATE_TUBE;
	graduationCetificateTube.value = 15;
	graduationCetificateTube.atkRange = ONE;
	graduationCetificateTube.atkType = CUT_STAB;
	graduationCetificateTube.flag = true;
	//彎刀
	strcpy(cutlass.name, "cutlass");
	cutlass.mateTag = WEAPON;
	cutlass.weaponType = CUTLASS;
	cutlass.value = 15;
	cutlass.atkRange = ONE;
	cutlass.atkType = CUT_STAB;
	cutlass.flag = true;

	//斧
	strcpy(battleAxe.name, "battle axe");
	battleAxe.mateTag = WEAPON;
	battleAxe.weaponType = BATTLE_AXE;
	battleAxe.value = 20;
	battleAxe.weight = 2.5f;
	battleAxe.atkRange = ONE;
	battleAxe.armorType = CUT;
	battleAxe.flag = true;
	//劍玉(斧)
	strcpy(kendama.name, "kendama");
	kendama.mateTag = WEAPON;
	kendama.weaponType = KENDAMA;
	kendama.value = 20;
	kendama.atkRange = ONE;
	kendama.armorType = CUT;
	kendama.flag = true;
	//長斧(?)
	strcpy(marius.name, "marius");
	marius.mateTag = WEAPON;
	marius.weaponType = MARIUS;
	marius.value = 20;
	marius.atkRange = ONE;
	marius.armorType = CUT;
	marius.flag = true;
	//也是斧
	strcpy(obrist.name, "obrist");
	obrist.mateTag = WEAPON;
	obrist.weaponType = OBRIST;
	obrist.value = 20;
	obrist.atkRange = ONE;
	obrist.armorType = CUT;
	obrist.flag = true;

	//槍
	strcpy(spear.name, "spear");
	spear.mateTag = WEAPON;
	spear.weaponType = SPEAR;
	spear.value = 20;
	spear.weight = 3.5f;
	spear.atkRange = TWO;
	spear.atkType = STAB;
	spear.flag = true;
	//pocky槍
	strcpy(pocky.name, "pocky");
	pocky.mateTag = WEAPON;
	pocky.weaponType = POCKY;
	pocky.value = 15;
	pocky.atkRange = TWO;
	pocky.atkType = STAB;
	pocky.flag = true;
	//奧丁的永恆之槍
	strcpy(gungnir.name, "gungnir");
	gungnir.mateTag = WEAPON;
	gungnir.weaponType = GUNGNIR;
	gungnir.value = 20;
	gungnir.atkRange = TWO;
	gungnir.atkType = STAB;
	gungnir.flag = true;
	//庫丘林之槍
	strcpy(gaeBolg.name, "gae bolg");
	gaeBolg.mateTag = WEAPON;
	gaeBolg.weaponType = GAE_BULG;
	gaeBolg.value = 20;
	gaeBolg.atkRange = TWO;
	gaeBolg.atkType = STAB;
	gaeBolg.flag = true;
	//蠍刺(?)
	strcpy(scorpion.name, "scorpion");
	scorpion.mateTag = WEAPON;
	scorpion.weaponType = SCORPION;
	scorpion.value = 20;
	scorpion.atkRange = TWO;
	scorpion.atkType = STAB;
	scorpion.flag = true;
}
void ArmorInit() {
	//裸体
	strcpy(noArmor.name, "no armor");
	noArmor.mateTag = ARMOR;
	noArmor.armorType = NO_ARMOR;
	noArmor.value = 0;
	noArmor.def = 0;
	noArmor.maxHp = 0;
	noArmor.hp = noArmor.maxHp;
	noArmor.weight = 0.0f;
	noArmor.defType = NORMAL_DEF;
	noArmor.flag = true;
	//皮甲
	strcpy(leatherArmor.name, "leather armor");
	leatherArmor.mateTag = ARMOR;
	leatherArmor.armorType = LEATHER_ARMOR;
	leatherArmor.value = 40;
	leatherArmor.flag = true;
	leatherArmor.maxHp = 400;
	leatherArmor.hp = leatherArmor.maxHp;
	leatherArmor.def = 0.2f;
	leatherArmor.weight = 5.0f;
	leatherArmor.defType = NORMAL_DEF;
	//重皮甲
	strcpy(heavyLeatherArmor.name, "hLeather armor");
	heavyLeatherArmor.mateTag = ARMOR;
	heavyLeatherArmor.armorType = HEAVY_LEATHE_RARMOR;
	heavyLeatherArmor.value = 45;
	heavyLeatherArmor.flag = true;
	heavyLeatherArmor.maxHp = 300;
	heavyLeatherArmor.hp = heavyLeatherArmor.maxHp;
	heavyLeatherArmor.def = 0.33f;
	heavyLeatherArmor.weight = 7.5f;
	heavyLeatherArmor.defType = NORMAL_DEF;
	//鎖甲(鎖帷子)
	strcpy(chainmail.name, "chainmail");
	chainmail.mateTag = ARMOR;
	chainmail.armorType = CHAINMAIL;
	chainmail.value = 150;
	chainmail.flag = true;
	chainmail.maxHp = 500;
	chainmail.hp = chainmail.maxHp;
	chainmail.def = 0.75f;
	chainmail.weight = 14.0f;
	chainmail.defType = CNAT_DEF_STAB;
}
void ItemInit() {
	//簡易藥水
	strcpy(simplePotion.name, "simple potion");
	strcpy(simplePotion.text, "Use to +75 hp");
	simplePotion.mateTag = ITEM;
	simplePotion.itemType = SIMPLE_POTION;
	simplePotion.value = 40;
	simplePotion.flag = true;
	simplePotion.hp = 75;
	simplePotion.weight = 0.2f;
	//超級藥水
	strcpy(superPotion.name, "super potion");
	strcpy(superPotion.text, "Use to restore all hp");
	superPotion.mateTag = ITEM;
	superPotion.itemType = SUPER_POTION;
	superPotion.value = 200;
	superPotion.flag = true;
	superPotion.hp = 300;
	superPotion.weight = 0.2f;

	//黃金
	strcpy(gold.name, "gold");
	strcpy(gold.text, "Gold is a popular precious metal");
	gold.mateTag = ITEM;
	gold.itemType = GOLD;
	gold.value = 100;
	gold.flag = true;
	gold.weight = 1.0f;

	//銀
	strcpy(silver.name, "silver");
	strcpy(silver.text, "Silver is a popular precious metal");
	silver.mateTag = ITEM;
	silver.itemType = GOLD;
	silver.value = 80;
	silver.flag = true;
	silver.weight = 1.0f;

	//象牙
	strcpy(ivory.name, "ivory");
	strcpy(ivory.text, "Although selling ivory is not ethical, it is still valuable");
	ivory.mateTag = ITEM;
	ivory.itemType = IVORY;
	ivory.value = 400;
	ivory.flag = true;
	ivory.weight = 20.0f;

	//碎鑽
	strcpy(brokenDiamond.name, "broken diamond");
	strcpy(brokenDiamond.text, "Diamond fragment, not very valuable");
	brokenDiamond.mateTag = ITEM;
	brokenDiamond.itemType = IVORY;
	brokenDiamond.value = 10;
	brokenDiamond.flag = true;
	brokenDiamond.weight = 0.01f;
}
void CreateEmpty() {
	strcpy(nothing.name, "nothing");
	nothing.mateTag = NOTHING;
	nothing.value = 0;
	nothing.flag = false;
}
/*
*ダメージの計算
*int weaponType　武器のタイプ
*/
int Damage(int weaponType) {
	int dice4 = rand() % 4 + 1;
	int dice6 = rand() % 6 + 1;
	int dice8 = rand() % 8 + 1;
	int dice10 = rand() % 10 + 1;
	int dice20 = rand() % 20 + 1;

	if (weaponType == FIST)
		return dice4 * 10; //10~40
	else if (weaponType == SHORT_SWORD || weaponType == SPEAR)
		return (dice4 + 1) * 10; //20~50
	else if (weaponType == BATTLE_AXE)
		return dice6 * 10; //10~60

}

