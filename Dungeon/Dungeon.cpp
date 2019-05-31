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
///初期化
void Init();
///更新
void Update();
///古い画面を削除して、新しい画面を表示する。
void Refresh();
///指定されているさ表に移動（表示関連）
inline void GotoXY(int, int);
///ランダム機能の初期化
void StartRnd();
///ダンジョン初期化
void CreateMap();
///ダンジョン内容更新
void UpdateBigMap();
///ダンジョンを表示する
void ShowBigMap();
///部屋の初期化
void CreateRoom();
///部屋の表示
void ShowRoom();
///プレイヤーの初期化
unit CreatePlayer();
///プレイヤーの状態を表示する
void ShowPlayerStatus();
///敵の初期化
void CreateEnemy();
///敵の配置
void SpawnEnemy();
///敵の削除
void DeleteAllEnemy();
///プレイヤーと同じ部屋の敵を探す。
bool SearchEnemy();
///敵の状態を表示する
void ShowEnemyStatus();
///戦闘
void Battle();
///プレイヤーの攻撃
void PlayerAttack();
///プレイヤーの移動先は敵がいる
bool IsEnemy(int);
///敵の攻撃
int EnemyAttack();
///プレイヤーのタン
void PlayerMove();
///敵のタン
void EnemyMove();
///装備管理
void InventoryManage();

unit player;
unit enemy[ENEMYNUMBER];

int sameMapEnemy[MAXENEMYINONEROOM];
int playerMoveCounter = 0;
int enemyPtr = 0;
int sameMapEnemyPtr = 0;

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
	system("mode con cols=150 lines=30");
	char flag;
	clsFlag_Inventory = false;
	haveEnemyFlag = false;
	//武器の初期化
	WeaponOption();
	//アーマーの初期化
	ArmorOption();
	//空欄
	CreateVoid();
	//敵の初期化
	CreateEnemy();
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
	//敵配置
	SpawnEnemy();
}
/*更新*/
void Update() {
	//装備管理モードか？
	if (player.inventoryMode == false) {
		//int currentPlayerX = player.x, currentPlayerY = player.y;
		//int newPlayerX, newPlayerY;
		PlayerMove();
		EnemyMove();
		//敵を削除して。生成と配置をし直す。
		if (playerMoveCounter > RE_ENEMYNUMBER && SearchEnemy() == false) {
			DeleteAllEnemy();
			CreateEnemy();
			SpawnEnemy();
			playerMoveCounter = 0;
		}

		//newPlayerX = player.x; newPlayerY = player.y;
		//if (currentPlayerX != newPlayerX || currentPlayerY != newPlayerY) {
		UpdateBigMap();
		Refresh();
		//}
	}
	else {
		InventoryManage();
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
					dangeon[i][j].type = rand() % 5 + 1;//(1~5)
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
	tmpPlayer.inventory[0] = sword;
	tmpPlayer.inventory[1] = leatherArmor;
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
//void battle() {
//	int ch;
//	while (true) {
//		//同步地圖位置與單位座標
//		for (int i = 0; i < 10; i++) {
//			for (int j = 0; j < 10; j++) {
//				if (room1[i][j].type == PLAYER) {
//					player.x = j;
//					player.y = i;
//				}
//				if (room1[i][j].type == ENEMY) {
//					enemy.x = j;
//					enemy.y = i;
//				}
//			}
//		}
//		//顯示畫面
//		Showbattle();
//
//		//移動
//		ch = getch();
//		if (ch == UP || ch == LEFT || ch == DOWN || ch == RIGHT) {
//			switch (ch) {
//			case UP: {
//				if (player.y != 0 && room1[player.y - 1][player.x].type != ENEMY) {
//					room1[player.y][player.x].type = FLOOR;
//					room1[player.y - 1][player.x].type = PLAYER;
//				}
//				if (room1[player.y - 1][player.x].type == ENEMY) {
//					enemy.hp -= player.atk;
//					player.hp -= enemy.atk;
//				}
//				break;
//			}
//			case DOWN: {
//				if (player.y != 9 && room1[player.y + 1][player.x].type != ENEMY) {
//					room1[player.y][player.x].type = FLOOR;
//					room1[player.y + 1][player.x].type = PLAYER;
//				}
//				if (room1[player.y + 1][player.x].type == ENEMY) {
//					enemy.hp -= player.atk;
//					player.hp -= enemy.atk;
//				}
//				break;
//			}
//			case LEFT: {
//				if (player.x != 0 && room1[player.y][player.x - 1].type != ENEMY) {
//					room1[player.y][player.x].type = FLOOR;
//					room1[player.y][player.x - 1].type = PLAYER;
//				}
//				if (room1[player.y][player.x - 1].type == ENEMY) {
//					enemy.hp -= player.atk;
//					player.hp -= enemy.atk;
//				}
//				break;
//			}
//			case RIGHT: {
//				if (player.x != 9 && room1[player.y][player.x + 1].type != ENEMY) {
//					room1[player.y][player.x].type = FLOOR;
//					room1[player.y][player.x + 1].type = PLAYER;
//				}
//				if (room1[player.y][player.x + 1].type == ENEMY) {
//					enemy.hp -= player.atk;
//					player.hp -= enemy.atk;
//				}
//				break;
//			}
//			}
//		}
//		if (enemy.hp <= 0 && enemy.alive == true) {
//			room1[enemy.y][enemy.x].type = FLOOR;
//			enemy.hp = 0;
//			enemy.alive = false;
//		}
//
//	}
//}
/*enemyの生成*/
void CreateEnemy() {
	int weaponRnd;
	int armorRnd;
	for (int i = 0; i < ENEMYNUMBER; i++) {
		enemy[i].alive = true;
		enemy[i].maxHp = 10 + rand() % 5;
		enemy[i].hp = enemy[i].maxHp;
		enemy[i].type = ENEMY;
		weaponRnd = rand() % 100 + 1;
		armorRnd = rand() % 100 + 1;
		if (weaponRnd <= 10)
			enemy[i].weapon = fist;
		else if (weaponRnd >= 10 && weaponRnd < 30)
			enemy[i].weapon = axe;
		else if (weaponRnd >= 30 && weaponRnd < 45)
			enemy[i].weapon = spear;
		else
			enemy[i].weapon = sword;

		if (weaponRnd < 60)
			enemy[i].armor = noArmor;
		else
			enemy[i].armor = leatherArmor;
	}
}
/*enemyの配置*/
void SpawnEnemy() {
	//PlayerPos of map turn to room
	int enemyCount = 0;
	int roomX_min, roomY_min, roomX_max, roomY_max;
	enemyPtr = 0;

	for (int i = 1; i < MAPRANGE - 1; i++) {
		for (int j = 1; j < MAPRANGE - 1; j++) {
			if (dangeon[i][j].playerPos != true) {

				for (int roomY = i * 5 - 4; roomY <= i * 5; roomY++) {
					for (int roomX = j * 5 - 4; roomX <= j * 5; roomX++) {
						if (room[roomY][roomX].playerPos != true && room[roomY][roomX].type == FLOOR &&
							(roomY % 5 != 0 && roomY % 5 != 1) && (roomX % 5 != 0 && roomX % 5 != 1)) {
							room[roomY][roomX].enemyPos = true;
							enemyPtr++;
						}
					}
				}
			}
		}
	}
	/*for (int i = 1; i < MAPRANGE - 1; i++) {
		for (int j = 1; j < MAPRANGE - 1; j++) {
			if (dangeon[i][j].playerPos == true) {
				roomX_min = (j - 1) * 5; roomX_max = j * 5;
				roomY_min = (i - 1) * 5; roomY_max = i * 5;
			}
		}
	}*/

	//for (int i = 1; i < ROOMRANGE; i++) {
	//	for (int j = 1; j < ROOMRANGE; j++) {
	//		if (i >= roomY_min && i <= roomY_max && j <= roomX_max && j >= roomX_min) {}
	//		else if (room[i][j].playerPos != true && room[i][j].type == FLOOR &&
	//			(i % 5 != 0 && i % 5 != 1) && (j % 5 != 0 && j % 5 != 1)) {

	//			if (enemyCount < MAXENEMYINONEROOM) {
	//				int rnd = rand() % ENEMY_SPAWN_PROBABILITY;
	//				//if (rnd == 3 || rnd == 5) {
	//				enemyCount++;
	//				enemy[enemyPtr].alive = true;
	//				room[i][j].enemyPos = true;
	//				enemy[enemyPtr].roomX = j;
	//				enemy[enemyPtr].roomY = i;
	//				enemyPtr++;

	//				if (enemyPtr == ENEMYNUMBER - 1) {
	//					enemyPtr = 0;
	//				}
	//				//}
	//			}
	//		}
	//		if (j % 5 == 1 && i % 5 == 1) {
	//			enemyCount = 0;
	//		}
	//	}
	//}
}

/*尋找同房間的敵人*/
bool SearchEnemy() {
	//取得玩家大地圖座標
	int roomX_min, roomY_min, roomX_max, roomY_max;
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
			if (room[i][j].enemyPos == true) {
				return true;
			}
		}
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
	ch = _getch();
	int currentX, currentY, newX, newY;
	currentX = player.roomX; currentY = player.roomY;
	if (ch == UP || ch == LEFT || ch == DOWN || ch == RIGHT) {
		switch (ch) {
		case UP: {
			//武器の攻撃範囲で敵がいるかどうかを判定する
			//いれば戦闘に入る
			if (IsEnemy(UP) == true) {
				//戰鬥=>賦予武器攻擊力=>計算敵人防禦血量
				PlayerAttack();
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
			if (player.roomY + 1 != ROOMRANGE + 1 && room[player.roomY + 1][player.roomX].type != WALL && player.roomY < 25) {
				room[player.roomY][player.roomX].playerPos = false;
				room[player.roomY + 1][player.roomX].playerPos = true;
				player.roomY++;
			}
			break;
		}
		case LEFT: {
			if (player.roomX - 1 != 0 && room[player.roomY][player.roomX - 1].type != WALL) {
				room[player.roomY][player.roomX].playerPos = false;
				room[player.roomY][player.roomX - 1].playerPos = true;
				player.roomX--;
			}
			break;
		}
		case RIGHT: {
			if (player.roomX - 1 != ROOMRANGE + 1 && room[player.roomY][player.roomX + 1].type != WALL && player.roomX < 25) {
				room[player.roomY][player.roomX].playerPos = false;
				room[player.roomY][player.roomX + 1].playerPos = true;
				player.roomX++;
			}
			break;
		}
		}
		newX = player.roomX; newY = player.roomY;
		if (currentX != newX || currentY != newY) {
			playerMoveCounter++;
		}
	}
	else if (ch == 'r' || ch == 'R') {
		player.inventoryMode = !player.inventoryMode;
	}
}
/*敵の移動*/
void EnemyMove() {

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
/*プレイヤー攻撃*/
void PlayerAttack() {
	int dice4 = rand() % 4 + 1;
	int dice6 = rand() % 6 + 1;
	int dice8 = rand() % 8 + 1;
	int dice10 = rand() % 10 + 1;
	int dice20 = rand() % 20 + 1;

	if (player.weapon.weaponType == FIST) {
		for (int i = 0; i < MAXENEMYINONEROOM; i++) {
			if (enemy[sameMapEnemy[i]].roomX == enemyPosX && enemy[sameMapEnemy[i]].roomY == enemyPosY) {
				if (enemy[sameMapEnemy[i]].armor.armorType == NO_ARMOR)
					enemy[sameMapEnemy[i]].hp -= dice4;
			}
		}
	}

}
/*武器の攻撃範囲で敵を探す*/
bool IsEnemy(int dir) {

	if (player.weapon.weaponType == FIST || player.weapon.weaponType == SWORD || player.weapon.weaponType == AXE) {
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

		if (room[enemyPosY][enemyPosX].enemyPos == true) {
			return true;
		}
	}
	//else if (player.weapon.weaponType == SWORD) {

	//}
	//else if (player.weapon.weaponType == AXE) {

	//}
	//else if (player.weapon.weaponType == SPEAR) {

	//}
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
				cout << "O ";
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
	cout << "Armor:" << player.armor.name << endl;
	for (int i = 0; i < 64; i++) {
		if (player.inventory[i].flag == true) {
			cout << i + 1 << "." << player.inventory[i].name << " value:" << player.inventory[i].value << endl;
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
					player.inventory[a] = tmp;
				}
				player.armor = tmp;
			}
			else if (player.inventory[a].mateTag == WEAPON) {
				tmp = player.inventory[a];
				if (player.weapon.weaponType == FIST) {
					player.inventory[a] = nothing;
				}
				else {
					player.inventory[a] = tmp;
				}
				player.weapon = tmp;

			}
		}
	}
	player.inventoryMode = false;
	clsFlag_Inventory = false;
}
/*プレイヤーの状態を表示する*/
void ShowPlayerStatus() {
	cout << "press 'r' for twice time to manage inventory" << endl;
	cout << endl;
	for (int i = 0; i < MAXENEMYINONEROOM; i++) {
		if (enemy[sameMapEnemy[i]].roomX == enemyPosX && enemy[sameMapEnemy[i]].roomY == enemyPosY) {
			cout << "enemyPosX:" << enemy[sameMapEnemy[i]].roomX << " enemyPosY:" << enemy[sameMapEnemy[i]].roomY << endl;
			cout << i << endl;
		}
	}
	cout << "Name:" << player.name << endl;
	cout << "X:" << player.roomX << "  Y:" << player.roomY << endl;
	cout << "move count:" << playerMoveCounter << endl;
	cout << "HP:" << player.hp << "/" << player.maxHp;
	cout << "     [" << player.armor.name << "] def:-" << player.armor.def * 100 <<
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
								if (enemy[e].roomX == j && enemy[e].roomY == i) {
									enemy[e].samePosWithPlayer = true;
									sameMapEnemy[sameMapEnemyPtr] = e;
									y = basicY;
									GotoXY(x, y++);
									cout << "enemy(" << j % 5 << "," << i % 5 << ")" << endl;
									GotoXY(x, y++);
									cout << "enemy hp:" << enemy[e].hp << endl;
									GotoXY(x, y++);
									cout << "weapon:" << enemy[e].weapon.name << endl;
									GotoXY(x, y++);
									cout << "armor:" << enemy[e].armor.name << endl;
									x += 25;
								}
								else {
									enemy[e].samePosWithPlayer = false;
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