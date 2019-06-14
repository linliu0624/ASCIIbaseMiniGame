#include "pch.h"
#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <malloc.h>
#include <time.h>
#include <cstdlib>
#include "item.h"
#include "conio.h"
#include "define.h"
#include "map.h"
#include "unit.h"
#include <queue>
using namespace std;
/*************待解決問題***************
敵人的生成有時候會有bug(機率低)
包包滿了的情況與重做
逃出
玩家死
依照玩家的武器和護甲來決定敵人裝備物品
商人
敵人尋找路徑
起始畫面
**************************************/
//初期化
void Init();
//更新
void Update();
//古い画面を削除して、新しい画面を表示する。
void Refresh();
//指定されているさ表に移動（表示関連）
inline void GotoXY(int, int);
//ランダム機能の初期化
void StartRnd();
//ダンジョン初期化
void CreateMap();
//ダンジョン内容更新
void UpdateBigMap();
//ダンジョンを表示する
void ShowBigMap();
//部屋の初期化
void CreateRoom();
//部屋の表示
void ShowRoom();
//プレイヤーの初期化
void CreatePlayer();
//プレイヤーの状態を表示する
void ShowPlayerStatus();
//敵の初期化
void CreateEnemy();
//敵の配置
void SpawnEnemy();
//敵の削除
void DeleteAllEnemy();
//プレイヤーと同じ部屋の敵を探す。
bool SearchEnemy();
//敵の状態を表示する
void ShowEnemyStatus();
//ルールの表示
void ShowRule();
//戦闘
void Battle();
//プレイヤーの攻撃
void PlayerAttack();
//プレイヤーの移動先は敵がいる
bool IsEnemy(int);
//敵の攻撃
bool EnemyAttack(int);
//プレイヤーのタン
void PlayerTurn();
//敵のターン
void EnemyTurn();
//敵の移動
void EnemyMove(int);
//敵が死ぬ
void EnemyDieAndDrop(int);
//装備管理
void InventoryManage();
//ダメージの計算
int Damage(int);
//void Damage(int, int, int, bool);
//攻撃
void Attack(material, bool);
//玩家死亡
void PlayerDie();


unit player;
unit enemy[ENEMYNUMBER];

//int sameMapEnemy[MAX_ENEMY_IN_ONEROOM];
int playerMoveCounter = 0;
//玩家裝備的武器與護甲價值
int playerWAVAlue = 0;
//int enemyPtr = 0;
//int sameMapEnemyPtr = 0;

//攻撃先の敵の座標
int enemyPosX, enemyPosY;


bool clsFlag_Inventory;
bool haveEnemyFlag;
bool isBattle;

int main()
{
	StartRnd();
	Init();
	//画面表示
	Refresh();
	// ゲームの循環
	while (true)
	{
		Update();
	}
	return 0;
}

/*初始化*/
void Init() {

	//ゲーム画面の大きさを設定する
	system("mode con cols=150");  //system("mode con cols=100 lines=100");//改變寬高
	//char flag;
	bool flag;
	clsFlag_Inventory = false;
	haveEnemyFlag = false;
	//ダンジョン生成
	do {
		system("cls");
		CreateMap();
		//部屋生成
		CreateRoom();
		cout << "Loading..." << endl;
		flag = SearchRoom();
	} while (flag == false);
	//Sleep(1000);
	//武器の初期化
	WeaponInit();
	//アーマーの初期化
	ArmorInit();
	//アイテムの初期化
	ItemInit();
	//空欄
	CreateEmpty();
	//プレイヤー生成
	CreatePlayer();
	//敵の初期化
	CreateEnemy();
	//敵配置
	SpawnEnemy();
}
/*更新*/
void Update() {
	bool haveEnemy;
	//装備管理モードか？
	if (player.inventoryMode == false) {
		SearchEnemy();
		PlayerTurn();
		UpdateBigMap();
		Refresh();
		if (player.inventoryMode == false) {
			haveEnemy = SearchEnemy();
			if (haveEnemy)
				EnemyTurn();
			//敵を削除して。生成と配置をし直す。
			if (playerMoveCounter > RE_ENEMYNUMBER && !haveEnemy) {
				DeleteAllEnemy();
				CreateEnemy();
				SpawnEnemy();
				playerMoveCounter = 0;
			}
			Refresh();
		}
	}
	else {
		InventoryManage();
		Refresh();
	}
}

/*畫面刷新*/
static void Refresh() {
	// 刷新
	system("cls");
	// 顯示
	ShowBigMap();
	ShowRoom();
	ShowPlayerStatus();
	ShowEnemyStatus();
}

/***************************************
*ダンジョンの生成
*作者：林
***************************************/
void CreateMap() {
	int wallNum = 5;
	for (int i = 0; i < MAPRANGE; i++) {
		for (int j = 0; j < MAPRANGE; j++) {
			//如果不是邊框
			if (i != 0 && i != MAPRANGE - 1 && j != 0 && j != MAPRANGE - 1) {
				//一番左上はプレイヤーの生成位置
				if (i == 1 && j == 1) {
					dangeon[i][j].type = ROOM;
					dangeon[i][j].playerPos = true;
				}
				else {
					//部屋の生成
					int type = rand() % 5 + 1;//(1~5)
					if (type == WALL) {
						wallNum--;
						if (wallNum <= 0) {
							type = ROOM;
						}
					}
					else {
						type = ROOM;
					}
					dangeon[i][j].type = type;
					dangeon[i][j].playerPos = false;

				}
			}
			else {
				dangeon[i][j].type = WALL;
				dangeon[i][j].playerPos = false;

			}
		}
	}
}
/***************************************
*playerの生成
*作者：荒井
***************************************/
void CreatePlayer() {
	char flag;
	player.alive = true;
	player.inventoryMode = false;
	player.maxHp = 300;
	player.hp = player.maxHp;
	player.type = PLAYER;
	player.weapon = fist;
	player.armor = noArmor;
	player.maxWeight = INIT_MAX_WEIGHT;
	player.weight = 0;
	for (int i = 0; i < MAX_INVENTORY; i++) {
		player.inventory[i] = nothing;
	}
	player.inventory[0] = superPotion;
	player.inventory[1] = superPotion;
	player.inventory[2] = superPotion;
	for (int i = 0; i < MAX_INVENTORY; i++)
		player.loan -= player.inventory[i].value;
	player.weight = player.inventory[0].weight + player.inventory[1].weight + player.inventory[2].weight;
	//プレイヤーの生成位置を決める
	room[3][3].playerPos = true;
	player.roomX = 3;
	player.roomY = 3;
	//while (true) {
	system("cls");
	cout << "Please input name:";
	cin >> player.name;
	cin.clear();
	cin.ignore(100, '\n');
	//	cout << "Your name is [" << player.name << "], are you sure?(y/n):";
	//}
}
/***************************************
*enemyの生成
*作者：林
***************************************/
void CreateEnemy() {
	//未來可以依照玩家的武器和護甲來決定敵人裝備物品
	playerWAVAlue = player.weapon.value + player.armor.value;
	int weaponRnd;
	int armorRnd;
	int itemRnd;
	for (int i = 0; i < ENEMYNUMBER; i++) {
		enemy[i].maxHp = 300;
		enemy[i].hp = 150 + rand() % 75 + rand() % 75;
		enemy[i].type = ENEMY;
		if (i % 4 == 0) {
			strcpy(enemy[i].name, "!");
		}
		else if (i % 4 == 1) {
			strcpy(enemy[i].name, "@");
		}
		else if (i % 4 == 2) {
			strcpy(enemy[i].name, "#");
		}
		else if (i % 4 == 3) {
			strcpy(enemy[i].name, "$");
		}
		if (i % 2 == 0)enemy[i].moveWay = true;
		else enemy[i].moveWay = false;
		weaponRnd = rand() % 100 + 1;
		armorRnd = rand() % 100 + 1;
		itemRnd = rand() % 100 + 1;
		//武器を装備する
		if (weaponRnd <= 20)
			enemy[i].weapon = fist;
		else if (weaponRnd >= 20 && weaponRnd < 40)
			enemy[i].weapon = battleAxe;
		else if (weaponRnd >= 40 && weaponRnd < 60)
			enemy[i].weapon = spear;
		else
			enemy[i].weapon = shortSword;
		//防具を装備する
		if (armorRnd < 50)
			enemy[i].armor = noArmor;
		else if (armorRnd >= 50 && armorRnd < 70) {
			enemy[i].armor = leatherArmor;
			enemy[i].armor.hp = rand() % 200 + 200;
		}
		else if (armorRnd >= 70 && armorRnd < 85) {
			enemy[i].armor = heavyLeatherArmor;
			enemy[i].armor.hp = rand() % 150 + 150;
		}
		else {
			enemy[i].armor = chainmail;
			enemy[i].armor.hp = rand() % 250 + 250;
		}

		//アイテムを装備する
		if (itemRnd <= 80) {
			enemy[i].inventory[0] = nothing;
		}
		else {
			enemy[i].inventory[0] = simplePotion;
		}
	}
}
/***************************************
*enemyの配置
*作者：田子
***************************************/
void SpawnEnemy() {
	//PlayerPos of map turn to room
	int enemyCount = 0;
	//int roomX_min, roomY_min, roomX_max, roomY_max;
	int enemyPtr = 0;
	//ダンジョンの部屋の移動
	for (int i = 1; i < MAPRANGE - 1; i++) {
		for (int j = 1; j < MAPRANGE - 1; j++) {
			if (dangeon[i][j].playerPos != true) {
				//部屋のマスの移動
				for (int roomY = i * 5 - 4; roomY <= i * 5; roomY++) {
					for (int roomX = j * 5 - 4; roomX <= j * 5; roomX++) {
						//一つ部屋の敵はMAX_ENEMY_IN_ONEROOM以下
						if (enemyCount < MAX_ENEMY_IN_ONEROOM) {
							if (room[roomY][roomX].playerPos != true && room[roomY][roomX].enemyPos != true &&
								room[roomY][roomX].type == FLOOR &&
								(roomY % 5 != 0 && roomY % 5 != 1) && (roomX % 5 != 0 && roomX % 5 != 1)) {
								//敵の出現確率
								int rnd = rand() % ENEMY_SPAWN_PROBABILITY;
								if (rnd == 3 || rnd == 5) {
									//敵の出現
									room[roomY][roomX].enemyPos = true;
									enemy[enemyPtr].alive = true;
									enemy[enemyPtr].roomX = roomX;
									enemy[enemyPtr].roomY = roomY;
									enemy[enemyPtr].firstRoomX = roomX;
									enemy[enemyPtr].firstRoomY = roomY;
									enemyPtr++;
									enemyCount++;
								}
								if (enemyPtr == ENEMYNUMBER - 1) {
									enemyPtr = 0;
								}
							}
						}
					}
				}
			}
			enemyCount = 0;
		}
	}
}
/***************************************
*enemyを削除する
*作者：田子
***************************************/
void DeleteAllEnemy() {
	for (int i = 0; i < ROOMRANGE; i++) {
		for (int j = 0; j < ROOMRANGE; j++) {
			room[i][j].enemyPos = false;
		}
	}
	for (int i = 0; i < ENEMYNUMBER; i++) {
		enemy[i].alive = false;
		enemy[i].roomX = -1;
		enemy[i].roomY = -1;
	}
}
/***************************************
*plyaerと同じ部屋のenemyを探す
*作者：荒井
***************************************/
bool SearchEnemy() {
	//取得玩家大地圖座標
	int roomX_min, roomY_min, roomX_max, roomY_max;
	bool haveEnemy = false;
	for (int i = 1; i < MAPRANGE - 1; i++) {
		for (int j = 1; j < MAPRANGE - 1; j++) {
			if (dangeon[i][j].playerPos == true) {
				//轉換大地圖座標為房間座標
				roomX_max = j * 5; roomX_min = roomX_max - 4;
				roomY_max = i * 5; roomY_min = roomY_max - 4;
			}
		}
	}

	for (int i = roomY_min; i <= roomY_max; i++) {
		for (int j = roomX_min; j <= roomX_max; j++) {
			if (room[i][j].enemyPos == true)
				haveEnemy = true;
			for (int e = 0; e < ENEMYNUMBER; e++) {
				if ((enemy[e].roomX <= roomX_max && enemy[e].roomX >= roomX_min) &&
					(enemy[e].roomY <= roomY_max && enemy[e].roomY >= roomY_min)) {//(enemy[e].roomX == j && enemy[e].roomY == i) {
					enemy[e].samePosWithPlayer = true;
				}
				else {
					enemy[e].samePosWithPlayer = false;
					if (enemy[e].alive == true) {
						room[enemy[e].roomY][enemy[e].roomX].enemyPos = false;
						enemy[e].roomX = enemy[e].firstRoomX;
						enemy[e].roomY = enemy[e].firstRoomY;
						room[enemy[e].roomY][enemy[e].roomX].enemyPos = true;
					}
				}
			}

		}
	}
	if (haveEnemy) {
		return true;
	}
	return false;
}

/***************************************
*プレーヤーのターン
*作者：林
***************************************/
void PlayerTurn() {
	int ch;
	bool flag = false;

	//玩家負重計算與檢測
	player.weight = 0;
	player.weight += player.weapon.weight;
	player.weight += player.armor.weight;
	for (int i = 0; i < MAX_INVENTORY; i++) {
		player.weight += player.inventory[i].weight;
	}
	if (player.weight > player.maxWeight) {
		player.inventoryMode = !player.inventoryMode;
		flag = true;
	}

	while (!flag) {
		ch = _getch();
		//基於技術上的原因(因為方向鍵為驅動鍵，所以需要讀取兩次)
		if (ch == 224) {
			ch = _getch();
		}
		int currentX, currentY, newX, newY;
		currentX = player.roomX; currentY = player.roomY;
		//如果過重就不能動，然後跳通知說要丟裝備
		if (ch == UP || ch == LEFT || ch == DOWN || ch == RIGHT) {
			switch (ch) {
			case UP: {
				//武器の攻撃範囲で敵がいるかどうかを判定する
				//いれば戦闘に入る
				if (IsEnemy(UP) == true) {
					//戰鬥=>賦予武器攻擊力=>計算敵人防禦血量
					Attack(player.weapon, true);
				}
				else {
					//なければ移動
					if (player.roomY - 1 != 0 && room[player.roomY - 1][player.roomX].type != WALL) {
						room[player.roomY][player.roomX].playerPos = false;
						room[player.roomY - 1][player.roomX].playerPos = true;
						player.roomY--;
					}
				}
				break;
			}
			case DOWN: {
				if (IsEnemy(DOWN) == true) {
					Attack(player.weapon, true);
				}
				else {
					if (player.roomY + 1 != ROOMRANGE && room[player.roomY + 1][player.roomX].type != WALL && player.roomY < 25) {
						room[player.roomY][player.roomX].playerPos = false;
						room[player.roomY + 1][player.roomX].playerPos = true;
						player.roomY++;
					}
				}
				break;
			}
			case LEFT: {
				if (IsEnemy(LEFT) == true) {
					Attack(player.weapon, true);
				}
				else {
					if (player.roomX - 1 != 0 && room[player.roomY][player.roomX - 1].type != WALL) {
						room[player.roomY][player.roomX].playerPos = false;
						room[player.roomY][player.roomX - 1].playerPos = true;
						player.roomX--;
					}
				}
				break;
			}
			case RIGHT: {
				if (IsEnemy(RIGHT) == true) {
					Attack(player.weapon, true);
				}
				else {
					if (player.roomX + 1 != ROOMRANGE && room[player.roomY][player.roomX + 1].type != WALL && player.roomX < 25) {
						room[player.roomY][player.roomX].playerPos = false;
						room[player.roomY][player.roomX + 1].playerPos = true;
						player.roomX++;
					}
				}
				break;
			}
			}
			newX = player.roomX; newY = player.roomY;
			if (currentX != newX || currentY != newY) {
				playerMoveCounter++;
			}
			flag = true;
		}
		else if (ch == SPACE) {
			flag = true;
		}
		else if ((ch == 'i' || ch == 'I')) {
			player.inventoryMode = !player.inventoryMode;
			flag = true;
		}
		else {
			flag = false;
		}
	}
}
/***************************************
*敵のターン
*作者：林
***************************************/
void EnemyTurn() {
	for (int i = 0; i < ENEMYNUMBER; i++) {
		if (enemy[i].samePosWithPlayer == true && enemy[i].alive == true) {
			if (EnemyAttack(i))
				EnemyMove(i);
			continue;
		}
	}
}
/***************************************
*敵の移動
*int enemyNumber 敵が配列にいる番号
*int type 武器の攻撃種類
*作者：林
***************************************/
void EnemyMove(int enemyNumber) {
	//敵人拿攻擊距離2武器還是會依照1的方式行動
	int enemyX, enemyY;
	enemyX = enemy[enemyNumber].roomX;
	enemyY = enemy[enemyNumber].roomY;
	//-----------------------是否會碰到隊友-----------------------
		//もし、enemy[i]の下は仲間がいなければ。
	if (enemy[enemyNumber].moveWay) {
		if (enemyY != player.roomY) {
			if (enemyY > player.roomY && room[enemyY - 1][enemyX].enemyPos != true && room[enemyY - 1][enemyX].type != WALL) {
				room[enemyY][enemyX].enemyPos = false;
				enemy[enemyNumber].roomY--;
				enemyY = enemy[enemyNumber].roomY;
				room[enemyY][enemyX].enemyPos = true;
			}
			else if (enemyY < player.roomY && room[enemyY + 1][enemyX].enemyPos != true && room[enemyY + 1][enemyX].type != WALL) {
				room[enemyY][enemyX].enemyPos = false;
				enemy[enemyNumber].roomY++;
				enemyY = enemy[enemyNumber].roomY;
				room[enemyY][enemyX].enemyPos = true;
			}
		}
		else if (enemyX != player.roomX) {
			if (enemyX > player.roomX && room[enemyY][enemyX - 1].enemyPos != true && room[enemyY][enemyX - 1].type != WALL) {
				room[enemyY][enemyX].enemyPos = false;
				enemy[enemyNumber].roomX--;
				enemyX = enemy[enemyNumber].roomX;
				room[enemyY][enemyX].enemyPos = true;
			}
			else if (enemyX < player.roomX && room[enemyY][enemyX + 1].enemyPos != true && room[enemyY][enemyX + 1].type != WALL) {
				room[enemyY][enemyX].enemyPos = false;
				enemy[enemyNumber].roomX++;
				enemyX = enemy[enemyNumber].roomX;
				room[enemyY][enemyX].enemyPos = true;
			}
		}
	}
	else {
		if (enemyX != player.roomX) {
			if (enemy[enemyNumber].roomX > player.roomX && room[enemyY][enemyX - 1].enemyPos != true && room[enemyY][enemyX - 1].type != WALL) {
				room[enemyY][enemyX].enemyPos = false;
				enemy[enemyNumber].roomX--;
				enemyX = enemy[enemyNumber].roomX;
				room[enemyY][enemyX].enemyPos = true;
			}
			else if (enemyX < player.roomX && room[enemyY][enemyX + 1].enemyPos != true && room[enemyY][enemyX + 1].type != WALL) {
				room[enemyY][enemyX].enemyPos = false;
				enemy[enemyNumber].roomX++;
				enemyX = enemy[enemyNumber].roomX;
				room[enemyY][enemyX].enemyPos = true;
			}
		}
		else if (enemyY != player.roomY) {
			if (enemyY > player.roomY && room[enemyY - 1][enemyX].enemyPos != true && room[enemyY - 1][enemyX].type != WALL) {
				room[enemyY][enemyX].enemyPos = false;
				enemy[enemyNumber].roomY--;
				enemyY = enemy[enemyNumber].roomY;
				room[enemyY][enemyX].enemyPos = true;
			}
			else if (enemyY < player.roomY && room[enemyY + 1][enemyX].enemyPos != true && room[enemyY + 1][enemyX].type != WALL) {
				room[enemyY][enemyX].enemyPos = false;
				enemy[enemyNumber].roomY++;
				enemyY = enemy[enemyNumber].roomY;
				room[enemyY][enemyX].enemyPos = true;
			}
		}
	}
	enemy[enemyNumber].moveWay = !enemy[enemyNumber].moveWay;
}
/***************************************
*enemyの攻撃
*int enemyNumber　敵が配列にいる番号
*作者：林
***************************************/
bool EnemyAttack(int enemyNumber) {
	int enemyX, enemyY;
	material enemyWeaponType;
	enemyX = enemy[enemyNumber].roomX;
	enemyY = enemy[enemyNumber].roomY;
	enemyWeaponType = enemy[enemyNumber].weapon;
	//-------------------是否會碰到玩家-----------------------
	if (enemyWeaponType.atkRange == ONE) {
		//下
		if (room[enemyY + 1][enemyX].playerPos == true) {
			//攻擊
			Attack(enemy[enemyNumber].weapon, false); return false;
		}
		//上
		else if (room[enemyY - 1][enemyX].playerPos == true) {
			//攻擊
			Attack(enemy[enemyNumber].weapon, false); return false;
		}
		//右
		else if (room[enemyY][enemyX + 1].playerPos == true) {
			//攻擊
			Attack(enemy[enemyNumber].weapon, false); return false;
		}
		//左
		else if (room[enemyY][enemyX - 1].playerPos == true) {
			//攻擊
			Attack(enemy[enemyNumber].weapon, false); return false;
		}
	}
	else if (enemyWeaponType.atkRange == TWO) {
		//下
		if ((room[enemyY + 1][enemyX].playerPos == true || room[enemyY + 2][enemyX].playerPos == true) &&
			room[enemyY + 1][enemyX].type != WALL) {
			//攻擊
			Attack(enemy[enemyNumber].weapon, false); return false;
		}
		//上
		else if ((room[enemyY - 1][enemyX].playerPos == true || room[enemyY - 2][enemyX].playerPos == true) &&
			room[enemyY - 1][enemyX].type != WALL) {
			//攻擊
			Attack(enemy[enemyNumber].weapon, false); return false;
		}
		//右
		else if ((room[enemyY][enemyX + 1].playerPos == true || room[enemyY][enemyX + 2].playerPos == true) &&
			room[enemyY][enemyX + 1].type != WALL) {
			//攻擊
			Attack(enemy[enemyNumber].weapon, false); return false;
		}
		//左
		else if ((room[enemyY][enemyX - 1].playerPos == true || room[enemyY][enemyX - 2].playerPos == true) &&
			room[enemyY][enemyX - 1].type != WALL) {
			//攻擊
			Attack(enemy[enemyNumber].weapon, false); return false;
		}
	}
	return true;
}
/***************************************
*部屋を作る
*作者：林
***************************************/
void CreateRoom() {
	int rnd;
	//歩けるマスと壁の生成
	for (int i = 1; i < ROOMRANGE; i++) {
		for (int j = 1; j < ROOMRANGE; j++) {
			room[i][j].mark = false;
			rnd = rand() % 8;
			if (rnd == 5 && i > 5 && j > 5) {
				room[i][j].type = WALL;
			}
			else {
				room[i][j].type = FLOOR;
			}
		}
	}
	//ダンジョンこの地域は壁だと、部屋も壁
	for (int i = 1; i < MAPRANGE - 1; i++) {
		for (int j = 1; j < MAPRANGE - 1; j++) {
			if (dangeon[i][j].type == WALL) {
				for (int y = i * 5 - 4; y <= i * 5; y++) {
					for (int x = j * 5 - 4; x <= j * 5; x++) {
						room[y][x].type = WALL;
					}
				}
			}
		}
	}
	room[1][1].exitPos = true;
}
/***************************************
*攻撃
*int weaponType 武器のタイプ
*bool playerToEnemy プレイヤーの攻撃か
*作者：荒井
****************************************/
void Attack(material weapon, bool playerToEnemy) {

	int totalDamage;
	int armorDamage;
	int bodyDamage;
	totalDamage = Damage(weapon.weaponType);


	if (playerToEnemy) {
		for (int i = 0; i < ENEMYNUMBER; i++) {
			if (enemy[i].roomX == enemyPosX && enemy[i].roomY == enemyPosY) {
				float armorDef = enemy[i].armor.def;
				// 可砍可刺的武器對護甲造成的傷害一般
				if (weapon.atkType == CUT_STAB) {
					armorDef = armorDef;
				}
				//只能砍的武器對鎖甲造成的傷害低
				else if (weapon.atkType == CUT) {
					if (enemy[i].armor.defType == CNAT_DEF_STAB) {
						armorDef = armorDef * 1.4f;
					}
					else {
						armorDef = armorDef;
					}

				}
				//只能刺的武器對鎖甲造成傷害高
				else if (weapon.atkType == STAB) {
					if (enemy[i].armor.defType == CNAT_DEF_STAB) {
						armorDef = armorDef * 0.4f;
					}
					else {
						armorDef = armorDef;
					}
				}

				armorDamage = armorDef * totalDamage;
				//armorDamage少なくても1
				if (armorDamage < 1) {
					armorDamage = 1;
				}
				//armorDamageが壊れた時
				if (enemy[i].armor.hp <= 0) {
					enemy[i].armor.hp = 0;
					enemy[i].armor = noArmor;
					armorDamage = 0;
				}
				enemy[i].armor.hp -= armorDamage;
				bodyDamage = totalDamage - armorDamage;
				if (bodyDamage <= 0) {
					bodyDamage = 0;
				}
				enemy[i].hp -= bodyDamage;
				//敵が死んだ時
				if (enemy[i].hp <= 0) {
					if (!enemy[i].alive)continue;
					EnemyDieAndDrop(i);
				}
				break;
			}
		}
	}
	else {
		float armorDef = player.armor.def;
		if (weapon.atkType == CUT_STAB) {
			armorDef = armorDef;
		}
		//只能砍的武器對鎖甲造成的傷害低
		else if (weapon.atkType == CUT) {
			if (player.armor.defType == CNAT_DEF_STAB) {
				armorDef = armorDef * 1.4f;
			}
			else {
				armorDef = armorDef;
			}
		}
		//只能刺的武器對鎖甲造成傷害高
		else if (weapon.atkType == STAB) {
			if (player.armor.defType == CNAT_DEF_STAB) {
				armorDef = armorDef * 0.4f;
			}
			else {
				armorDef = armorDef;
			}
		}
		armorDamage = armorDef * totalDamage;

		//armorDamage少なくても1
		if (armorDamage < 1) {
			armorDamage = 1;
		}
		//armorDamageが壊れた時
		if (player.armor.hp <= 0) {
			player.armor.hp = 0;
			player.armor = noArmor;
			armorDamage = 0;
		}
		player.armor.hp -= armorDamage;
		bodyDamage = totalDamage - armorDamage;
		if (bodyDamage <= 0) {
			bodyDamage = 0;
		}
		player.hp -= bodyDamage;

		//敵が死んだ時
		if (player.hp <= 0) {
			player.alive = false;
		}
	}
}

/***************************************
*enemyが死んだ時とアイテムドロップ
*number:敵配列の番号
*作者：田子
***************************************/
void EnemyDieAndDrop(int number) {
	enemy[number].hp = 0;
	enemy[number].alive = false;
	room[enemy[number].roomY][enemy[number].roomX].enemyPos = false;
	for (int i = 0; i < MAX_INVENTORY; i++) {
		if (player.inventory[i].mateTag != WEAPON && player.inventory[i].mateTag != ARMOR &&
			player.inventory[i].mateTag != ITEM) {
			if (enemy[number].weapon.weaponType != FIST) {
				player.inventory[i] = enemy[number].weapon;
				player.weight += player.inventory[i].weight;
				enemy[number].weapon = fist;
				continue;
			}
			else if (enemy[number].armor.armorType != NO_ARMOR) {
				player.inventory[i] = enemy[number].armor;
				player.weight += player.inventory[i].weight;
				enemy[number].armor = noArmor;
				continue;
			}
			else if (enemy[number].inventory[0].mateTag != NOTHING) {
				player.inventory[i] = enemy[number].inventory[0];
				player.weight += player.inventory[i].weight;
				enemy[number].inventory[0] = nothing;
				continue;
			}
		}
	}
}
/***************************************
*武器の攻撃範囲で敵を探す
*int playerの移動方向
*作者：荒井
***************************************/
bool IsEnemy(int dir) {
	if (player.weapon.atkRange == ONE) {
		if (dir == UP) {
			enemyPosX = player.roomX;
			enemyPosY = player.roomY - 1;
		}
		else if (dir == DOWN) {
			enemyPosX = player.roomX;
			enemyPosY = player.roomY + 1;
		}
		else if (dir == LEFT) {
			enemyPosX = player.roomX - 1;
			enemyPosY = player.roomY;
		}
		else {
			enemyPosX = player.roomX + 1;
			enemyPosY = player.roomY;
		}
		for (int i = 0; i < ENEMYNUMBER; i++)
			if (room[enemyPosY][enemyPosX].enemyPos == true && enemy[i].samePosWithPlayer == true) {
				return true;
			}
	}
	else if (player.weapon.atkRange == TWO) {
		if (dir == UP) {
			enemyPosX = player.roomX;
			enemyPosY = player.roomY - 1;
			if (room[enemyPosY][enemyPosX].enemyPos) {

			}
			else if (room[enemyPosY - 1][enemyPosX].enemyPos && room[enemyPosY][enemyPosX].type != WALL)
				enemyPosY--;
		}
		else if (dir == DOWN) {
			enemyPosX = player.roomX;
			enemyPosY = player.roomY + 1;
			if (room[enemyPosY][enemyPosX].enemyPos) {

			}
			else if (room[enemyPosY + 1][enemyPosX].enemyPos && room[enemyPosY][enemyPosX].type != WALL)
				enemyPosY++;
		}
		else if (dir == LEFT) {
			enemyPosX = player.roomX - 1;
			enemyPosY = player.roomY;
			if (room[enemyPosY][enemyPosX].enemyPos) {

			}
			else if (room[enemyPosY][enemyPosX - 1].enemyPos && room[enemyPosY][enemyPosX].type != WALL) {
				enemyPosX--;
			}
		}
		else {
			enemyPosX = player.roomX + 1;
			enemyPosY = player.roomY;
			if (room[enemyPosY][enemyPosX].enemyPos) {

			}
			else if (room[enemyPosY][enemyPosX + 1].enemyPos && room[enemyPosY][enemyPosX].type != WALL) {
				enemyPosX++;
			}
		}
		for (int i = 0; i < ENEMYNUMBER; i++) {
			if (room[enemyPosY][enemyPosX].enemyPos && enemy[i].samePosWithPlayer) {
				return true;
			}
		}
	}
	return false;
}
/***************************************
*ダンジョン更新
*作者：林
***************************************/
void UpdateBigMap() {
	int mapX, mapY;
	mapX = (player.roomX - 1) / 5 + 1;
	mapY = (player.roomY - 1) / 5 + 1;

	for (int i = 0; i < MAPRANGE; i++) {
		for (int j = 0; j < MAPRANGE; j++) {
			if (i == mapY && j == mapX) {
				dangeon[mapY][mapX].playerPos = true;
				player.mapX = mapX;
				player.mapY = mapY;
			}
			else
			{
				dangeon[i][j].playerPos = false;
			}
		}
	}
}
/***************************************
*ダンジョンの表示
*作者：林
***************************************/
void ShowBigMap() {
	cout << ">dungenon map<" << endl;
	for (int i = 0; i < MAPRANGE; i++) {
		for (int j = 0; j < MAPRANGE; j++) {
			if (dangeon[i][j].type == WALL && dangeon[i][j].playerPos != true) {
				cout << "X ";
			}
			if (dangeon[i][j].type == ROOM && dangeon[i][j].playerPos != true) {
				cout << "  ";
			}
			if (dangeon[i][j].type == ROOM && dangeon[i][j].playerPos == true) {
				cout << "P ";
			}

		}
		cout << endl;
	}
}
/***************************************
*部屋の表示
*作者：林
***************************************/
void ShowRoom() {
	//顯示玩家存在的區域的地圖
	cout << "->room map<-" << endl;
	for (int i = 1; i < MAPRANGE; i++) {
		for (int j = 1; j < MAPRANGE; j++) {
			if (dangeon[i][j].playerPos == true)
			{
				for (int y = i * 5 - 4; y <= i * 5; y++) {
					cout << "|";
					for (int x = j * 5 - 4; x <= j * 5; x++) {
						if (room[y][x].type == FLOOR && room[y][x].playerPos == true) {
							cout << "P ";
						}
						else if (room[y][x].type == WALL) {
							cout << "X ";
						}
						else if (room[y][x].enemyPos == true) {
							for (int i = 0; i < ENEMYNUMBER; i++)
								if (enemy[i].roomX == x && enemy[i].roomY == y && enemy[i].alive)
									cout << enemy[i].name << " ";
						}
						else if (room[y][x].type == FLOOR && room[y][x].playerPos != true && !room[y][x].exitPos) {
							cout << "  ";
						}
						if (room[y][x].exitPos && !room[y][x].playerPos) {
							cout << "E ";
						}
					}
					cout << "|" << endl;
				}
			}
		}
	}
	cout << "===============================================================================" << endl;
	//顯示所有區域的地圖(debug mode)
	//cout << "---------------" << endl;
	//for (int y = 1; y < ROOMRANGE; y++) {
	//	cout << "|";
	//	for (int x = 1; x < ROOMRANGE; x++) {
	//		if (room[y][x].enemyPos)
	//			for (int i = 0; i < ENEMYNUMBER; i++) {
	//				if (enemy[i].roomX == x && enemy[i].roomY == y) {
	//					if (i < 10)
	//						cout << i << " ";
	//					else
	//						cout << i;
	//				}
	//			}
	//		else
	//			if (room[y][x].type == FLOOR)
	//				cout <<"  ";
	//			else
	//				cout << "X ";

	//		//if (room[y][x].type == FLOOR && room[y][x].playerPos == true) {
	//		//	cout << "P ";
	//		//}
	//		//else if (room[y][x].type == WALL) {
	//		//	cout << "X ";
	//		//}
	//		//else if (room[y][x].enemyPos == true) {
	//		//	for (int i = 0; i < ENEMYNUMBER; i++)
	//		//		if (enemy[i].roomX == x && enemy[i].roomY == y && enemy[i].alive)
	//		//			if (i < 10)
	//		//				cout << i << " ";//cout << enemy[i].name << " ";
	//		//			else
	//		//				cout << i;
	//		//}
	//		//else if (room[y][x].type == FLOOR && room[y][x].playerPos != true) {
	//		//	cout << "  ";
	//		//}
	//		///*if (room[y][x].type == FLOOR && !room[y][x].mark) {
	//		//	cout << "?";
	//		//}*/
	//		if (x % 5 == 0)
	//			cout << "|";

	//	}
	//	if (y % 5 == 0) {
	//		cout << endl;
	//	}
	//	cout << "|" << endl;
	//}
	//cout << "===============================================================================" << endl;

}
/***************************************
*装備管理
*作者：横林
***************************************/
void InventoryManage() {
	bool outFlag = false;
	if (clsFlag_Inventory == false) {
		system("CLS");
		clsFlag_Inventory = !clsFlag_Inventory;
	}
	if (player.weight > player.maxWeight) {
		cout << ">>You carry to many things, discard something!<<" << endl;
		cout << "weight:" << player.weight << "/" << player.maxWeight << endl << endl;
	}

	int a, b;
	cout << "Weapon:" << player.weapon.name << endl;
	cout << "Armor:" << player.armor.name << endl << "=======================" << endl;
	for (int i = 0; i < 64; i++) {
		if (player.inventory[i].flag == true) {
			cout << i + 1 << "." << player.inventory[i].name << "[value:" << player.inventory[i].value << " ,weight:" << player.inventory[i].weight << "]"
				<< endl << "  " << player.inventory[i].text << endl;
		}
	}

	cout << endl;
	while (1) {
		cout << "Input a number that you want to change(twice time same number to equip or use , '888' to back ,'999' to discard):";
		cin >> a;
		if ((a < 1 || a > MAX_INVENTORY) && a != 999 && a != 888) {
			cin.clear();
			cin.ignore(100, '\n');
		}
		else if (a > 0 && a < MAX_INVENTORY || a == 999 || a == 888)break;
	}

	if (a == 888) {
	}
	else if (a == 999) {
		while (true) {
			while (true) {
				cout << "Discard:";
				cin >> b;
				if (b < 1 || player.inventory[b - 1].mateTag == NOTHING) {
					cin.clear();
					cin.ignore(100, '\n');
				}
				else if (b > 0 && b < INT_MAX)break;

			}
			b--;
			cout << "If you discard, your item will never back. Are you sure?(y/n):";
			char ch;
			cin >> ch;
			if (ch == 'y' || ch == 'Y') {
				player.weight -= player.inventory[b].weight;
				player.inventory[b] = nothing;
				break;
			}
			else {
				break;
			}
		}
	}
	else if (a < MAX_INVENTORY) {
		while (true) {
			cout << "Change to:";
			cin >> b;
			if (b < 1 || b > MAX_INVENTORY) {
				cin.clear();
				cin.ignore(100, '\n');
			}
			else if (b > 0 && b < MAX_INVENTORY)break;
		}
		a--;
		b--;

		material tmp;
		if (a != b) {
			tmp = player.inventory[a];
			player.inventory[a] = player.inventory[b];
			player.inventory[b] = tmp;
		}
		else {
			if (player.inventory[a].mateTag == ARMOR) {
				tmp = player.inventory[a];
				if (player.armor.armorType == NO_ARMOR) {
					player.inventory[a] = nothing;
				}
				else {
					player.inventory[a] = player.armor;
				}
				player.armor = tmp;
			}
			else if (player.inventory[a].mateTag == WEAPON) {
				tmp = player.inventory[a];
				if (player.weapon.weaponType == FIST) {
					player.inventory[a] = nothing;
				}
				else {
					player.inventory[a] = player.weapon;
				}
				player.weapon = tmp;

			}
			else if (player.inventory[a].mateTag == ITEM) {
				if (player.inventory[a].itemType == SIMPLE_POTION ) {
					if (player.hp + simplePotion.hp >= player.maxHp) {
						player.hp = player.maxHp;
					}
					else {
						player.hp += simplePotion.hp;
					}
				}
				else if (player.inventory[a].itemType == SUPER_POTION) {
					if (player.hp + superPotion.hp >= player.maxHp) {
						player.hp = player.maxHp;
					}
					else {
						player.hp += superPotion.hp;
					}
				}
				player.inventory[a] = nothing;
				player.weight -= player.inventory[a].weight;
			}
		}
	}
	player.inventoryMode = false;
	clsFlag_Inventory = false;
}
/***************************************
*playerの状態を表示する
*作者：荒井
***************************************/
void ShowPlayerStatus() {
	cout << "press 'i' to manage inventory, 'space' to wait" << endl;
	cout << endl;
	int value = 0;
	for (int i = 0; i < 64; i++) {
		if (player.inventory[i].flag == true)
			value += player.inventory[i].value;
	}

	cout << "Name:" << player.name << "  |  All value:" << player.loan + value << endl;
	cout << "HP:" << player.hp << "/" << player.maxHp;
	cout << "  Weight:" << player.weight << "/" << player.maxWeight << endl;
	//cout << "X:" << player.roomX << "  Y:" << player.roomY << endl;
	//cout << "move count:" << playerMoveCounter << endl;
	cout << "[" << player.armor.name << "] def:+" << player.armor.def * 100 <<
		"%  durability:" << player.armor.hp << "/" << player.armor.maxHp << endl;
	cout << "[" << player.weapon.name << "]" << endl;
	cout << "----Inventory----" << endl;
	for (int i = 0; i < 64; i++) {
		if (player.inventory[i].flag == true) {
			cout << i + 1 << "." << player.inventory[i].name << "[" << player.inventory[i].value << "]" << endl;
		}
	}
}
/***************************************
*敵の状態を表示する
*作者：林
*寫法需要優化
***************************************/
void ShowEnemyStatus() {
	int roomX_min, roomX_max, roomY_min, roomY_max;
	int x = 50, y = 15;
	GotoXY(x, y++);
	//cout << "enemyPtr:" << enemyPtr + 1 << endl;
	GotoXY(x, y++);
	int basicY = y;
	//プレイヤーがダンジョンのどこにいるかを探す
	for (int i = 1; i < MAPRANGE; i++) {
		for (int j = 1; j < MAPRANGE; j++) {
			if (dangeon[i][j].playerPos == true) {
				//ダンジョンの座標を部屋の座標に転換する
				roomX_max = j * 5; roomX_min = roomX_max - 4;
				roomY_max = i * 5; roomY_min = roomY_max - 4;

				//部屋の敵を探す
				for (int i = roomY_min; i <= roomY_max; i++) {
					for (int j = roomX_min; j <= roomX_max; j++) {
						if (room[i][j].enemyPos == true) {
							for (int e = 0; e < ENEMYNUMBER; e++) {
								if ((enemy[e].roomX == j && enemy[e].roomY == i) && enemy[e].alive == true) {
									//sameMapEnemy[sameMapEnemyPtr] = e;
									y = basicY;
									GotoXY(x, y++);
									cout << "name:" << enemy[e].name << endl;
									GotoXY(x, y++);
									cout << "enemy(" << j % 5 << "," << i % 5 << ")" << endl;
									GotoXY(x, y++);
									cout << "enemy hp:" << enemy[e].hp << endl;
									GotoXY(x, y++);
									cout << "weapon:" << enemy[e].weapon.name << endl;
									GotoXY(x, y++);
									cout << "armor:" << enemy[e].armor.name << endl;
									GotoXY(x, y++);
									cout << "durability:" << enemy[e].armor.hp << "/" << enemy[e].armor.maxHp << endl;
									x += 25;
								}
								else {
								}

							}

						}
					}
				}
			}
		}
	}
}
/***************************************
*ルールを表示する
*作者：林
***************************************/
void ShowRule() {
	cout << "↑↓←→キーで移動と攻撃" << endl;
}

/***************************************
*ランダムの初期化
*作者：林
***************************************/
void StartRnd() {
	unsigned seed;
	seed = (unsigned)time(NULL);
	srand(seed);
}
/***************************************
*画面の座標を(x,y)に移動する
*作者：林
***************************************/
inline void GotoXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}