/*
*作者：横林
*/
#include"pch.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include"item.h"

material fist;
material dagger;
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
material powerPostion;

material gold;
material silver;
material ivory;
material brokenDiamond;
void WeaponInit() {
	//拳
	strcpy(fist.name, "拳");
	strcpy(fist.text, "~ 自身の拳、武器がない時に頼るものといえばコレ");
	strcpy(fist.atktext, "atk: 10~40");
	fist.mateTag = WEAPON;
	fist.weaponType = FIST;
	fist.value = 0;
	fist.weight = 0.0f;
	fist.atkRange = ONE;
	fist.atkType = CUT_STAB;
	fist.flag = true;

	//匕首
	strcpy(dagger.name, "ダガー");
	strcpy(dagger.text, "短剣、急所に当たれば大ダメージ");
	strcpy(dagger.atktext, "atk: 10~200");
	dagger.mateTag = WEAPON;
	dagger.weaponType = SHORT_SWORD;
	dagger.maxValue = 10;
	dagger.value = dagger.maxValue;
	dagger.maxHp = 10;
	dagger.hp = dagger.maxHp;
	dagger.weight = 1.0f;
	dagger.atkRange = ONE;
	dagger.atkType = CUT_STAB;
	dagger.flag = true;

	//短剣
	strcpy(shortSword.name, "ショートソード");
	strcpy(shortSword.atktext, "atk: 30~60");
	strcpy(shortSword.text, "バランスのとれた剣、大量生産品");
	shortSword.mateTag = WEAPON;
	shortSword.weaponType = SHORT_SWORD;
	shortSword.maxValue = 60;
	shortSword.value = shortSword.maxValue;
	shortSword.maxHp = 30;
	shortSword.hp = shortSword.maxHp;
	shortSword.weight = 1.5f;
	shortSword.atkRange = ONE;
	shortSword.atkType = CUT_STAB;
	shortSword.flag = true;
	//長剣
	strcpy(longSword.name, "ロングソード");
	strcpy(longSword.atktext, "atk=40~100");
	longSword.mateTag = WEAPON;
	longSword.weaponType = LONG_SWORD;
	longSword.maxValue = 40;
	longSword.value = longSword.maxValue;
	longSword.maxHp = 15;
	longSword.hp = shortSword.maxHp;
	longSword.weight = 2.0f;
	longSword.atkRange = ONE;
	longSword.atkType = CUT_STAB;
	longSword.flag = true;
	//バナナ剣
	strcpy(banana.name, "バナナ");
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
	strcpy(battleAxe.name, "バトルアックス");
	strcpy(battleAxe.atktext, "atk: 10~80");
	strcpy(battleAxe.text, "切ることしかできない武器、ダメージは安定しないが、運がいいと大ダメージ");
	battleAxe.mateTag = WEAPON;
	battleAxe.weaponType = BATTLE_AXE;
	battleAxe.maxValue = 75;
	battleAxe.value = battleAxe.maxValue;
	battleAxe.maxHp = 30;
	battleAxe.hp = shortSword.maxHp;
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
	strcpy(marius.name, "marius(axe)");
	strcpy(marius.atktext, "atk:30~120");
	marius.mateTag = WEAPON;
	marius.weaponType = MARIUS;
	marius.maxValue = 50;
	marius.value = marius.maxValue;
	marius.maxHp = 15;
	marius.hp = marius.maxHp;
	marius.weight = 3.5f;
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
	strcpy(spear.name, "スピア");
	strcpy(spear.atktext, "atk: 30~60");
	strcpy(spear.text, "長い柄の先に尖った金属がついている武器、ダメージは普通だがリーチを生かして2マス前の敵まで攻撃が届く");
	spear.mateTag = WEAPON;
	spear.weaponType = SPEAR;
	spear.maxValue = 100;
	spear.value = spear.maxValue;
	spear.maxHp = 20;
	spear.hp = shortSword.maxHp;
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
	strcpy(scorpion.atktext, "atk: 40~100");
	scorpion.mateTag = WEAPON;
	scorpion.weaponType = SCORPION;
	scorpion.maxValue = 100;
	scorpion.value = scorpion.maxValue;
	scorpion.maxHp = 10;
	scorpion.hp = scorpion.maxHp;
	scorpion.weight = 5.0f;
	scorpion.atkRange = TWO;
	scorpion.atkType = STAB;
	scorpion.flag = true;
}
void ArmorInit() {
	//裸体
	strcpy(noArmor.name, "裸");
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
	strcpy(leatherArmor.name, "レザーアーマー");
	strcpy(leatherArmor.text, "動物の皮でできた鎧、これではちょっと心もとない");
	leatherArmor.mateTag = ARMOR;
	leatherArmor.armorType = LEATHER_ARMOR;
	leatherArmor.maxValue = 90;
	leatherArmor.value = leatherArmor.maxValue;
	leatherArmor.flag = true;
	leatherArmor.maxHp = 400;
	leatherArmor.hp = leatherArmor.maxHp;
	leatherArmor.def = 0.2f;
	leatherArmor.weight = 5.0f;
	leatherArmor.defType = NORMAL_DEF;
	//重皮甲
	strcpy(heavyLeatherArmor.name, "ハードレザーアーマー");
	strcpy(heavyLeatherArmor.text, "レザーアーマーより分厚く、防御力もある");
	heavyLeatherArmor.mateTag = ARMOR;
	heavyLeatherArmor.armorType = HEAVY_LEATHE_RARMOR;
	heavyLeatherArmor.maxValue = 110;
	heavyLeatherArmor.value = heavyLeatherArmor.maxValue;
	heavyLeatherArmor.flag = true;
	heavyLeatherArmor.maxHp = 300;
	heavyLeatherArmor.hp = heavyLeatherArmor.maxHp;
	heavyLeatherArmor.def = 0.33f;
	heavyLeatherArmor.weight = 7.5f;
	heavyLeatherArmor.defType = NORMAL_DEF;
	//鎖甲(鎖帷子)
	strcpy(chainmail.name, "チェーンメイル");
	strcpy(chainmail.text, "着心地最悪、高価でタフな鎧、しかし刺突攻撃に対しての防御力は低い ");
	chainmail.mateTag = ARMOR;
	chainmail.armorType = CHAINMAIL;
	chainmail.maxValue = 175;
	chainmail.value = chainmail.maxValue;
	chainmail.flag = true;
	chainmail.maxHp = 500;
	chainmail.hp = chainmail.maxHp;
	chainmail.def = 0.6f;
	chainmail.weight = 14.0f;
	chainmail.defType = CANNOT_DEF_STAB;
}
void ItemInit() {
	//簡易藥水
	strcpy(simplePotion.name, "ただのポーション");
	strcpy(simplePotion.text, "使うとHPを75回復");
	simplePotion.mateTag = ITEM;
	simplePotion.itemType = SIMPLE_POTION;
	simplePotion.value = 40;
	simplePotion.flag = true;
	simplePotion.hp = 75;
	simplePotion.weight = 0.2f;
	//超級藥水
	strcpy(superPotion.name, "すげえポーション");
	strcpy(superPotion.text, "使用すると全回復、多分ヤバい薬");
	superPotion.mateTag = ITEM;
	superPotion.itemType = SUPER_POTION;
	superPotion.value = 200;
	superPotion.flag = true;
	superPotion.hp = 300;
	superPotion.weight = 0.2f;
	//耐重要水
	strcpy(powerPostion.name, "力のポーション");
	strcpy(powerPostion.text, "使用すると持てる最大重量が10増える");
	powerPostion.mateTag = ITEM;
	powerPostion.itemType = POWER_POTION;
	powerPostion.value = 100;
	powerPostion.flag = true;
	powerPostion.hp = 10;
	powerPostion.weight = 0.2f;

	//黃金
	strcpy(gold.name, "金塊");
	strcpy(gold.text, "お金になるものといえばやはり金");
	gold.mateTag = ITEM;
	gold.itemType = GOLD;
	gold.value = 100;
	gold.flag = true;
	gold.weight = 1.0f;

	//銀
	strcpy(silver.name, "銀塊");
	strcpy(silver.text, "銀、金には劣るがこれも充分高価な金属");
	silver.mateTag = ITEM;
	silver.itemType = GOLD;
	silver.value = 80;
	silver.flag = true;
	silver.weight = 1.0f;

	//象牙
	strcpy(ivory.name, "象牙");
	strcpy(ivory.text, "現在では取ることが禁止されている象牙、非常に高価だが持ち運ぶのも大変");
	ivory.mateTag = ITEM;
	ivory.itemType = IVORY;
	ivory.value = 400;
	ivory.flag = true;
	ivory.weight = 23.0f;

	//碎鑽
	strcpy(brokenDiamond.name, "砕けたダイヤモンド");
	strcpy(brokenDiamond.text, "ダイヤモンドは砕けないなんて事はなかった");
	brokenDiamond.mateTag = ITEM;
	brokenDiamond.itemType = IVORY;
	brokenDiamond.value = 10;
	brokenDiamond.flag = true;
	brokenDiamond.weight = 0.01f;
}
void CreateEmpty() {
	strcpy(nothing.name, "虚無");
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
		return dice4 * 10 + 10 + 10; //30~60
	else if (weaponType == BATTLE_AXE)
		return dice8 * 10; //10~80
	else if (weaponType == SCORPION || weaponType == LONG_SWORD)
		return (dice4 + dice4) * 10 + 20;
	else if (weaponType == MARIUS)
		return (dice4 + dice4 + dice4) * 10;
	else if (weaponType == DAGGER)
		return dice20 * 10;

}

