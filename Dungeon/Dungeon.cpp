#include "pch.h"
#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <malloc.h>
#include <time.h>
#include "item.h"
#include "conio.h"
#include "define.h"
#include "map.h"
#include "unit.h"
using namespace std;
/*************待解決問題***************
3.攻擊距離超過1的情況
4.包包滿了的情況與重做
5.逃出
6.玩家死
7.地圖生成重做
8.敵人尋找路徑
9.起始畫面
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
unit CreatePlayer();
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
//戦闘
void Battle();
//プレイヤーの攻撃
void PlayerAttack();
//プレイヤーの移動先は敵がいる
bool IsEnemy(int);
//敵の攻撃
void EnemyAttack(int);
//プレイヤーのタン
void PlayerMove();
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
void Attack(int, bool);
//玩家死亡
void PlayerDie();

unit player;
unit enemy[ENEMYNUMBER];

//int sameMapEnemy[MAX_ENEMY_IN_ONEROOM];
int playerMoveCounter = 0;
//玩家裝備的武器與護甲價值
int playerWAVAlue = 0;
int enemyPtr = 0;
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
	system("mode con cols=150");
	char flag;
	clsFlag_Inventory = false;
	haveEnemyFlag = false;
	//武器の初期化
	WeaponOption();
	//アーマーの初期化
	ArmorOption();
	//アイテムの初期化
	ItemOption();
	//空欄
	CreateVoid();
	//ダンジョン生成
	while (true) {
		CreateMap();
		ShowBigMap();
		cout << "Do you want this dungeon?(y/n):";
		cin >> flag;
		if (flag == 'y' || flag == 'Y') {
			break;
		}
		system("cls");
	}
	//プレイヤー生成
	player = CreatePlayer();
	//部屋生成
	CreateRoom();
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
		//int currentPlayerX = player.x, currentPlayerY = player.y;
		//int newPlayerX, newPlayerY;
		haveEnemy = SearchEnemy();
		PlayerMove();
		UpdateBigMap();
		Refresh();
		if (player.inventoryMode == false) {
			haveEnemy = SearchEnemy();
			EnemyTurn();
			//敵を削除して。生成と配置をし直す。
			if (playerMoveCounter > RE_ENEMYNUMBER && !haveEnemy) {
				DeleteAllEnemy();
				CreateEnemy();
				SpawnEnemy();
				playerMoveCounter = 0;
			}
			//newPlayerX = player.x; newPlayerY = player.y;
			//if (currentPlayerX != newPlayerX || currentPlayerY != newPlayerY) {
			Refresh();
		}
		//}
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

/*生成大地圖*/
void CreateMap() {
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
					dangeon[i][j].type = rand() % 10 + 1;//(1~5)
					if (dangeon[i][j].type != WALL) {
						dangeon[i][j].type = ROOM;
						dangeon[i][j].playerPos = false;
					}
					else {
						dangeon[i][j].type = WALL;
						dangeon[i][j].playerPos = false;
					}
				}
			}
			else {
				dangeon[i][j].type = WALL;
				dangeon[i][j].playerPos = false;

			}
		}
	}
}

/*玩家生成*/
unit CreatePlayer() {
	char flag;
	unit tmpPlayer;
	tmpPlayer.alive = true;
	tmpPlayer.inventoryMode = false;
	tmpPlayer.maxHp = 30;
	tmpPlayer.hp = tmpPlayer.maxHp;
	tmpPlayer.type = PLAYER;
	tmpPlayer.weapon = fist;
	tmpPlayer.armor = noArmor;
	for (int i = 2; i < 64; i++) {
		tmpPlayer.inventory[i] = nothing;
	}
	tmpPlayer.inventory[0] = simplePotion;
	tmpPlayer.inventory[1] = simplePotion;
	tmpPlayer.inventory[2] = simplePotion;
	while (true) {
		system("cls");
		cout << "Please input name:";
		cin >> tmpPlayer.name;
		cout << "Your name is [" << tmpPlayer.name << "], are you sure?(y/n):";
		cin >> flag;
		if (flag == 'Y' || flag == 'y') {
			return tmpPlayer;
		}
	}
}
/*enemyの生成*/
void CreateEnemy() {
	//未來可以依照玩家的武器和護甲來決定敵人裝備物品
	playerWAVAlue = player.weapon.value + player.armor.value;
	int weaponRnd;
	int armorRnd;
	int itemRnd;
	for (int i = 0; i < ENEMYNUMBER; i++) {
		enemy[i].alive = true;
		enemy[i].maxHp = 30;
		enemy[i].hp = 10 + rand() % 10 + rand() % 10;
		enemy[i].type = ENEMY;
		weaponRnd = rand() % 100 + 1;
		armorRnd = rand() % 100 + 1;
		itemRnd = rand() % 100 + 1;
		//武器を装備する
		if (weaponRnd <= 20)
			enemy[i].weapon = fist;
		else if (weaponRnd >= 20 && weaponRnd < 40)
			enemy[i].weapon = axe;
		else if (weaponRnd >= 40 && weaponRnd < 50)
			enemy[i].weapon = spear;
		else
			enemy[i].weapon = sword;
		//防具を装備する
		if (armorRnd < 60)
			enemy[i].armor = noArmor;
		else if (armorRnd >= 60 && armorRnd < 90) {
			enemy[i].armor = leatherArmor;
			enemy[i].armor.hp = rand() % 20 + 20;
		}
		else {
			enemy[i].armor = heavyLeatherArmor;
			enemy[i].armor.hp = rand() % 15 + 15;
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
/*enemyの配置*/
void SpawnEnemy() {
	//PlayerPos of map turn to room
	int enemyCount = 0;
	//int roomX_min, roomY_min, roomX_max, roomY_max;
	enemyPtr = 0;
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

/*尋找同房間的敵人*/
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
void DeleteAllEnemy() {
	for (int i = 0; i < ROOMRANGE; i++) {
		for (int j = 0; j < ROOMRANGE; j++) {
			room[i][j].enemyPos = false;
		}
	}
}
/*プレーヤーのターン*/
void PlayerMove() {
	int ch;
	ch = _getch();
	//基於技術上的原因(因為方向鍵為驅動鍵，所以需要讀取兩次)
	if (ch == 224) {
		ch = _getch();
	}
	int currentX, currentY, newX, newY;
	currentX = player.roomX; currentY = player.roomY;
	if (ch == UP || ch == LEFT || ch == DOWN || ch == RIGHT) {
		switch (ch) {
		case UP: {
			//武器の攻撃範囲で敵がいるかどうかを判定する
			//いれば戦闘に入る
			if (IsEnemy(UP) == true) {
				//戰鬥=>賦予武器攻擊力=>計算敵人防禦血量
				Attack(player.weapon.weaponType, true);
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
				Attack(player.weapon.weaponType, true);
			}
			else {
				if (player.roomY + 1 != ROOMRANGE + 1 && room[player.roomY + 1][player.roomX].type != WALL && player.roomY < 25) {
					room[player.roomY][player.roomX].playerPos = false;
					room[player.roomY + 1][player.roomX].playerPos = true;
					player.roomY++;
				}
			}
			break;
		}
		case LEFT: {
			if (IsEnemy(LEFT) == true) {
				Attack(player.weapon.weaponType, true);
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
				Attack(player.weapon.weaponType, true);
			}
			else {
				if (player.roomX - 1 != ROOMRANGE + 1 && room[player.roomY][player.roomX + 1].type != WALL && player.roomX < 25) {
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
	}
	else if (ch == SPACE) {

	}
	else if (ch == 'r' || ch == 'R') {
		player.inventoryMode = !player.inventoryMode;
	}
}
/*敵のターン*/
void EnemyTurn() {

	for (int i = 0; i < ENEMYNUMBER; i++) {
		if (enemy[i].samePosWithPlayer == true && enemy[i].alive == true) {
			int enemyWeapon = enemy[i].weapon.weaponType;
			//攻擊距離1的武器
			if (enemyWeapon == FIST || enemyWeapon == LONG_SWORD || enemyWeapon == AXE) {
				EnemyMove(i);
				//以上兩者都不會就移動
			}
		}
	}
}
/*
*敵の移動
*int enemyNumber 敵が配列にいる番号
*/
void EnemyMove(int enemyNumber) {
	int enemyX, enemyY;

	enemyX = enemy[enemyNumber].roomX;
	enemyY = enemy[enemyNumber].roomY;
	//是否會碰到玩家--------------------------------------------------------
	//下
	if (room[enemyY + 1][enemyX].playerPos == true) {
		//攻擊
		Attack(enemy[enemyNumber].weapon.weaponType, false);
	}
	//上
	else if (room[enemyY - 1][enemyX].playerPos == true) {
		//攻擊
		Attack(enemy[enemyNumber].weapon.weaponType, false);
	}
	//右
	else if (room[enemyY][enemyX + 1].playerPos == true) {
		//攻擊
		Attack(enemy[enemyNumber].weapon.weaponType, false);
	}
	//左
	else if (room[enemyY][enemyX - 1].playerPos == true) {
		//攻擊
		Attack(enemy[enemyNumber].weapon.weaponType, false);
	}
	//是否會碰到隊友--------------------------------------------------------
	else {
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
				//if (room[enemyY + 1][enemyX].enemyPos != true || room[enemyY + 1][enemyX].type != WALL) {
				//	if (enemy[enemyNumber].roomY != player.roomY) {
				//		if (enemy[enemyNumber].roomY > player.roomY) {
				//			room[enemyY][enemyX].enemyPos = false;
				//			enemy[enemyNumber].roomY--;
				//			enemyY = enemy[enemyNumber].roomY;
				//			room[enemyY][enemyX].enemyPos = true;
				//		}
				//		else if (enemyY < player.roomY) {
				//			room[enemy[enemyNumber].roomY][enemyX].enemyPos = false;
				//			enemy[enemyNumber].roomY++;
				//			enemyY = enemy[enemyNumber].roomY;
				//			room[enemy[enemyNumber].roomY][enemyX].enemyPos = true;
				//		}
				//	}
				//	else if (enemyX != player.roomX) {
				//		if (enemy[enemyNumber].roomX > player.roomX) {
				//			room[enemyY][enemyX].enemyPos = false;
				//			enemy[enemyNumber].roomX--;
				//			enemyX = enemy[enemyNumber].roomX;
				//			room[enemyY][enemyX].enemyPos = true;
				//		}
				//		else if (enemyX < player.roomX) {
				//			room[enemyY][enemyX].enemyPos = false;
				//			enemy[enemyNumber].roomX++;
				//			enemyX = enemy[enemyNumber].roomX;
				//			room[enemyY][enemyX].enemyPos = true;
				//		}
				//	}
				//}
				////もし、enemy[i]の上は仲間がいなければ。
				//else if (room[enemyY - 1][enemyX].enemyPos != true || room[enemyY + 1][enemyX].type != WALL) {
				//	if (enemy[enemyNumber].roomY != player.roomY) {
				//		if (enemy[enemyNumber].roomY > player.roomY) {
				//			room[enemyY][enemyX].enemyPos = false;
				//			enemy[enemyNumber].roomY--;
				//			enemyY = enemy[enemyNumber].roomY;
				//			room[enemyY][enemyX].enemyPos = true;
				//		}
				//		else if (enemyY < player.roomY) {
				//			room[enemy[enemyNumber].roomY][enemyX].enemyPos = false;
				//			enemy[enemyNumber].roomY++;
				//			enemyY = enemy[enemyNumber].roomY;
				//			room[enemy[enemyNumber].roomY][enemyX].enemyPos = true;
				//		}
				//	}
				//	else if (enemyX != player.roomX) {
				//		if (enemy[enemyNumber].roomX > player.roomX) {
				//			room[enemyY][enemyX].enemyPos = false;
				//			enemy[enemyNumber].roomX--;
				//			enemyX = enemy[enemyNumber].roomX;
				//			room[enemyY][enemyX].enemyPos = true;
				//		}
				//		else if (enemyX < player.roomX) {
				//			room[enemyY][enemyX].enemyPos = false;
				//			enemy[enemyNumber].roomX++;
				//			enemyX = enemy[enemyNumber].roomX;
				//			room[enemyY][enemyX].enemyPos = true;
				//		}
				//	}
				//}
				////もし、enemy[i]の右は仲間がいなければ。
				//else if (room[enemyY][enemyX + 1].enemyPos != true || room[enemyY + 1][enemyX].type != WALL) {
				//	if (enemy[enemyNumber].roomY != player.roomY) {
				//		if (enemy[enemyNumber].roomY > player.roomY) {
				//			room[enemyY][enemyX].enemyPos = false;
				//			enemy[enemyNumber].roomY--;
				//			enemyY = enemy[enemyNumber].roomY;
				//			room[enemyY][enemyX].enemyPos = true;
				//		}
				//		else if (enemyY < player.roomY) {
				//			room[enemy[enemyNumber].roomY][enemyX].enemyPos = false;
				//			enemy[enemyNumber].roomY++;
				//			enemyY = enemy[enemyNumber].roomY;
				//			room[enemy[enemyNumber].roomY][enemyX].enemyPos = true;
				//		}
				//	}
				//	else if (enemyX != player.roomX) {
				//		if (enemy[enemyNumber].roomX > player.roomX) {
				//			room[enemyY][enemyX].enemyPos = false;
				//			enemy[enemyNumber].roomX--;
				//			enemyX = enemy[enemyNumber].roomX;
				//			room[enemyY][enemyX].enemyPos = true;
				//		}
				//		else if (enemyX < player.roomX) {
				//			room[enemyY][enemyX].enemyPos = false;
				//			enemy[enemyNumber].roomX++;
				//			enemyX = enemy[enemyNumber].roomX;
				//			room[enemyY][enemyX].enemyPos = true;
				//		}
				//	}
				//}
				////もし、enemy[i]の左は仲間がいなければ。
				//else if (room[enemyY + 1][enemyX].enemyPos!=true ||room[enemyY + 1][enemyX].type != WALL) {
				//	if (enemy[enemyNumber].roomY != player.roomY) {
				//		if (enemy[enemyNumber].roomY > player.roomY) {
				//			room[enemyY][enemyX].enemyPos = false;
				//			enemy[enemyNumber].roomY--;
				//			enemyY = enemy[enemyNumber].roomY;
				//			room[enemyY][enemyX].enemyPos = true;
				//		}
				//		else if (enemyY < player.roomY) {
				//			room[enemy[enemyNumber].roomY][enemyX].enemyPos = false;
				//			enemy[enemyNumber].roomY++;
				//			enemyY = enemy[enemyNumber].roomY;
				//			room[enemy[enemyNumber].roomY][enemyX].enemyPos = true;
				//		}
				//	}
				//	else if (enemyX != player.roomX) {
				//		if (enemy[enemyNumber].roomX > player.roomX) {
				//			room[enemyY][enemyX].enemyPos = false;
				//			enemy[enemyNumber].roomX--;
				//			enemyX = enemy[enemyNumber].roomX;
				//			room[enemyY][enemyX].enemyPos = true;
				//		}
				//		else if (enemyX < player.roomX) {
				//			room[enemyY][enemyX].enemyPos = false;
				//			enemy[enemyNumber].roomX++;
				//			enemyX = enemy[enemyNumber].roomX;
				//			room[enemyY][enemyX].enemyPos = true;
				//		}
				//	}
				//}
			}
		}
		else {
			if (enemyX != player.roomX && room[enemyY][enemyX - 1].enemyPos != true && room[enemyY][enemyX - 1].type != WALL) {
				if (enemy[enemyNumber].roomX > player.roomX) {
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
}
void CreateRoom() {
	int rnd;
	//歩けるマスと壁の生成
	for (int i = 1; i < ROOMRANGE; i++) {
		for (int j = 1; j < ROOMRANGE; j++) {
			rnd = rand() % 8;
			if (rnd == 5 && i > 5 && j > 5) {
				room[i][j].type = WALL;
			}
			else {
				room[i][j].type = FLOOR;
			}
			room[i][j].playerPos = false;
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

	//プレイヤーの生成位置を決める
	room[1][1].playerPos = true;
	player.roomX = 1;
	player.roomY = 1;
}
/***************************************
*ダメージの計算
*int damage1 ダメージ量1
*int damage2 ダメージ量2
*int bonus   ダメージボーナス
*bool playerToEnemy プレイヤーの攻撃か
****************************************/
//void Damage(int damage1, int damage2, int bonus, bool playerToEnemy) {
//
//	int totalDamage;
//	int armorDamage;
//	int bodyDamage;
//	if (playerToEnemy) {
//		for (int i = 0; i < ENEMYNUMBER; i++) {
//			if (enemy[i].roomX == enemyPosX && enemy[i].roomY == enemyPosY) {
//				totalDamage = damage1 + damage2 + bonus;
//				armorDamage = enemy[i].armor.def*totalDamage;
//
//				//armorDamage少なくても1
//				if (armorDamage < 1) {
//					armorDamage = 1;
//				}
//				//armorDamageが壊れた時
//				if (enemy[i].armor.hp <= 0) {
//					enemy[i].armor.hp = 0;
//					enemy[i].armor = noArmor;
//					armorDamage = 0;
//				}
//				enemy[i].armor.hp -= armorDamage;
//				bodyDamage = totalDamage - armorDamage;
//				if (bodyDamage <= 0) {
//					bodyDamage = 0;
//				}
//				enemy[i].hp -= bodyDamage;
//				//敵が死んだ時
//				if (enemy[i].hp <= 0) {
//					EnemyDieAndDrop(i);
//				}
//				break;
//			}
//		}
//	}
//	else {
//
//	}
//}
/***************************************
*攻撃
*int weaponType 武器のタイプ
*bool playerToEnemy プレイヤーの攻撃か
****************************************/
void Attack(int weaponType, bool playerToEnemy) {

	int totalDamage;
	int armorDamage;
	int bodyDamage;

	totalDamage = Damage(weaponType);

	if (playerToEnemy) {
		for (int i = 0; i < ENEMYNUMBER; i++) {
			if (enemy[i].roomX == enemyPosX && enemy[i].roomY == enemyPosY) {
				armorDamage = enemy[i].armor.def * totalDamage;

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
					EnemyDieAndDrop(i);
				}
				break;
			}
		}
	}
	else {
		armorDamage = player.armor.def * totalDamage;

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
		return dice4; //1~4
	else if (weaponType == LONG_SWORD)
		return dice4 + 1; //2~5
	else if (weaponType == AXE)
		return dice6 + 2; //3~8
	else
		return dice4;
}
/*
*敵がぬ
*number:敵配列の番号
*/
void EnemyDieAndDrop(int number) {
	enemy[number].hp = 0;
	enemy[number].alive = false;
	room[enemy[number].roomY][enemy[number].roomX].enemyPos = false;

	for (int i = 0; i < MAX_INVENTORY; i++) {
		if (player.inventory[i].mateTag != WEAPON && player.inventory[i].mateTag != ARMOR &&
			player.inventory[i].mateTag != ITEM) {
			if (enemy[number].weapon.weaponType != FIST) {
				player.inventory[i] = enemy[number].weapon;
				enemy[number].weapon = fist;
				continue;
			}
			else if (enemy[number].armor.armorType != NO_ARMOR) {
				player.inventory[i] = enemy[number].armor;
				enemy[number].armor = noArmor;
				continue;
			}
			else if (enemy[number].inventory[0].mateTag != NOTHING) {
				player.inventory[i] = enemy[number].inventory[0];
				enemy[number].inventory[0] = nothing;
				continue;
			}
		}
	}
}
/*武器の攻撃範囲で敵を探す*/
bool IsEnemy(int dir) {

	if (player.weapon.weaponType == FIST || player.weapon.weaponType == LONG_SWORD || player.weapon.weaponType == AXE) {
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
	//else if (player.weapon.weaponType == SPEAR) {

	//}
	return false;
}
/*ダンジョン更新*/
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
/*ダンジョンの表示*/
void ShowBigMap() {
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
/*部屋の表示*/
void ShowRoom() {
	cout << "---------------" << endl;
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
							cout << "e ";
						}
						else if (room[y][x].type == FLOOR && room[y][x].playerPos != true) {
							cout << "  ";
						}
					}
					cout << "|" << endl;
				}
			}
		}
	}
	cout << "===============================================================================" << endl;

	/*cout << "---------------" << endl;
	for (int y = 1; y < ROOMRANGE; y++) {
		cout << "|";
		for (int x = 1; x < ROOMRANGE; x++) {
			if (room[y][x].type == FLOOR && room[y][x].playerPos == true) {
				cout << "P";
			}
			else if (room[y][x].type == WALL) {
				cout << "X";
			}
			else if (room[y][x].type == ENEMY) {
				cout << "e";
			}
			else if (room[y][x].type == FLOOR && room[y][x].playerPos != true) {
				cout << "O";
			}
		}
		cout << "|" << endl;
	}
	cout << "===============================================================================" << endl;
	*/
}
/*装備管理*/
void InventoryManage() {
	if (clsFlag_Inventory == false) {
		system("CLS");
		clsFlag_Inventory = !clsFlag_Inventory;
	}
	int a, b;
	cout << "Weapon:" << player.weapon.name << endl;
	cout << "Armor:" << player.armor.name << endl << endl;
	for (int i = 0; i < 64; i++) {
		if (player.inventory[i].flag == true) {
			cout << i + 1 << "." << player.inventory[i].name << " [" << player.inventory[i].value << "]:" << player.inventory[i].text << endl;
		}
	}

	cout << endl;
	cout << "Input a number that you want to change(twice time same number will equip , '888' to back ,'999' to discard):";
	cin >> a;
	if (a == 888) {
	}
	else if (a == 999) {
		while (true) {
			cout << "Discard:";
			cin >> b;
			b--;
			cout << "If you discard, your item will never back. Are you sure?(y/n):";
			char ch;
			cin >> ch;
			if (ch == 'y' || ch == 'Y') {
				player.inventory[b] = nothing;
				break;
			}
			else {
				break;
			}
		}
	}
	else {
		cout << "Change to:";
		cin >> b;
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
				if (player.inventory[a].itemType == SIMPLE_POTION) {
					if (player.hp + simplePotion.hp >= player.maxHp) {
						player.hp = player.maxHp;
					}
					else {
						player.hp += simplePotion.hp;
					}
					player.inventory[a] = nothing;
				}
			}
		}
	}
	player.inventoryMode = false;
	clsFlag_Inventory = false;
}
/*プレイヤーの状態を表示する*/
void ShowPlayerStatus() {
	cout << "press 'r' to manage inventory, 'space' to wait" << endl;
	cout << endl;

	int value = 0;
	for (int i = 0; i < 64; i++) {
		if (player.inventory[i].flag == true)
			value += player.inventory[i].value;
	}

	cout << "Name:" << player.name << "  |  All value:" << value << endl;
	cout << "X:" << player.roomX << "  Y:" << player.roomY << endl;
	cout << "move count:" << playerMoveCounter << endl;
	cout << "HP:" << player.hp << "/" << player.maxHp;
	cout << "     [" << player.armor.name << "] def:+" << player.armor.def * 100 <<
		"%  HP:" << player.armor.hp << "/" << player.armor.maxHp << endl;
	cout << "             [" << player.weapon.name << "]" << endl;

	cout << "----Inventory----" << endl;
	for (int i = 0; i < 64; i++) {
		if (player.inventory[i].flag == true) {
			cout << i + 1 << "." << player.inventory[i].name << "[" << player.inventory[i].value << "]" << endl;
		}
	}
}
/*敵の状態を表示する*/ //寫法需要優化
void ShowEnemyStatus() {
	int roomX_min, roomX_max, roomY_min, roomY_max;
	int x = 50, y = 14;
	GotoXY(x, y++);
	cout << "enemyPtr:" << enemyPtr + 1 << endl;
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
									cout << e << " enemy(" << j % 5 << "," << i % 5 << ")" << enemy[e].firstRoomX % 5 << "," << enemy[e].firstRoomY % 5 << endl;
									GotoXY(x, y++);
									cout << " enemy hp:" << enemy[e].hp << endl;
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

/*ランダムの初期化*/
void StartRnd() {
	unsigned seed;
	seed = (unsigned)time(NULL);
	srand(seed);
}
/*画面の座標を(x,y)に移動する*/
inline void GotoXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}