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
///初始化游戏
void Init();
/// 针对输入进行处理
void Update();
/// 清屏&将内容打印到屏幕上
void Refresh();
///移動到座標
inline void GotoXY(int, int);
///隨機種子
void StartRnd();
///大地圖生成
void CreateMap();
///大地圖更新
void UpdateBigMap();
///顯示大地圖
void ShowBigMap();
///小地圖生成
void CreateRoom();
///顯示小地圖
void ShowRoom();
///玩家生成
unit CreatePlayer();
///顯示玩家狀態
void ShowPlayerStatus();
///生成敵人
void SpawnEnemy();
///敵人行動
void EnemyMove();
///戰鬥
void Battle();
///玩家移動
void PlayerMove();
///裝備管理
void InventoryManage();

unit player;
unit enemy[128];

bool clsFlag_Inventory;

int main()
{
	StartRnd();

	Init();
	// ゲームの循環
	while (true)
	{
		Update();
	}
	return 0;
}

/*初始化*/
void Init() {
	char flag;
	clsFlag_Inventory = false;
	WeaponOption();
	ArmorOption();
	CreateVoid();
	//地圖生成
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
	//玩家命名
	player = CreatePlayer();
	CreateRoom();
}

/*操作*/
void Update() {
	if (player.inventoryMode == false) {
		Refresh();
		PlayerMove();
		UpdateBigMap();
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

}

/*生成大地圖*/
void CreateMap() {
	for (int i = 0; i < MAPRANGE; i++) {
		for (int j = 0; j < MAPRANGE; j++) {
			//如果不是邊框
			if (i != 0 && i != MAPRANGE - 1 && j != 0 && j != MAPRANGE - 1) {
				//最左上一定是房間+玩家
				if (i == 1 && j == 1) {
					map[i][j].type = ROOM;
					map[i][j].playerPos = true;
				}
				else {
					//生成隨機房間
					map[i][j].type = rand() % 5 + 1;//(1~5)
					if (map[i][j].type != WALL) {
						map[i][j].type = ROOM;
						map[i][j].playerPos = false;
					}
					else {
						map[i][j].type = WALL;
						map[i][j].playerPos = false;
					}
				}
			}
			else {
				map[i][j].type = WALL;
				map[i][j].playerPos = false;

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
void SpawnEnemy() {
	for (int i = 1; i < ROOMRANGE; i++) {
		for (int j = 1; j < ROOMRANGE; j++) {

		}
	}
}

/*プレーヤーのターン*/
void PlayerMove() {
	int ch;
	ch = _getch();
	if (ch == UP || ch == LEFT || ch == DOWN || ch == RIGHT) {
		switch (ch) {
		case UP: {
			if (player.y - 1 != 0 && room[player.y - 1][player.x].type != WALL) {
				room[player.y][player.x].playerPos = false;
				room[player.y - 1][player.x].playerPos = true;
				player.y--;
			}
			break;
		}
		case DOWN: {
			if (player.y + 1 != ROOMRANGE + 1 && room[player.y + 1][player.x].type != WALL && player.y < 25) {
				room[player.y][player.x].playerPos = false;
				room[player.y + 1][player.x].playerPos = true;
				player.y++;
			}
			break;
		}
		case LEFT: {
			if (player.x - 1 != 0 && room[player.y][player.x - 1].type != WALL) {
				room[player.y][player.x].playerPos = false;
				room[player.y][player.x - 1].playerPos = true;
				player.x--;
			}
			break;
		}
		case RIGHT: {
			if (player.x - 1 != ROOMRANGE + 1 && room[player.y][player.x + 1].type != WALL && player.x < 25) {
				room[player.y][player.x].playerPos = false;
				room[player.y][player.x + 1].playerPos = true;
				player.x++;
			}
			break;
		}
		}
	}

	if (ch == 'r' || ch == 'R') {
		player.inventoryMode = !player.inventoryMode;
	}
}
void CreateRoom() {
	int rnd;
	//生成陸地和牆壁
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
	//如果map的區域是牆壁的話，room也是牆壁
	cout << map[1][1].type << endl;
	for (int i = 1; i < MAPRANGE - 1; i++) {
		for (int j = 1; j < MAPRANGE - 1; j++) {
			if (map[i][j].type == WALL) {
				for (int y = i * 5 - 4; y <= i * 5; y++) {
					for (int x = j * 5 - 4; x <= j * 5; x++) {
						room[y][x].type = WALL;
					}
				}
			}
		}
	}

	//指定玩家出生點
	room[1][1].playerPos = true;
	player.x = 1;
	player.y = 1;
}


/*大地圖更新*/
void UpdateBigMap() {
	int mapX, mapY;
	mapX = (player.x - 1) / 5 + 1;
	mapY = (player.y - 1) / 5 + 1;

	for (int i = 0; i < MAPRANGE; i++) {
		for (int j = 0; j < MAPRANGE; j++) {
			if (i == mapY && j == mapX) {
				map[mapY][mapX].playerPos = true;
			}
			else
			{
				map[i][j].playerPos = false;
			}
		}
	}
}

/*顯示大地圖*/
void ShowBigMap() {
	for (int i = 0; i < MAPRANGE; i++) {
		for (int j = 0; j < MAPRANGE; j++) {
			if (map[i][j].type == WALL && map[i][j].playerPos != true) {
				cout << "X ";
			}
			if (map[i][j].type == ROOM && map[i][j].playerPos != true) {
				cout << "O ";
			}
			if (map[i][j].type == ROOM && map[i][j].playerPos == true) {
				cout << "P ";
			}
		}
		cout << endl;
	}
}
/*部屋を表示する*/
void ShowRoom() {
	cout << "---------------" << endl;
	for (int i = 1; i < MAPRANGE; i++) {
		for (int j = 1; j < MAPRANGE; j++) {
			if (map[i][j].playerPos == true)
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
						else if (room[y][x].type == ENEMY) {
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
			cout << i + 1 << "." << player.inventory[i].name << endl;
		}
	}
	cout << endl;
	cout << "Input a number that you want to change(twice time same number will equip):";
	cin >> a;
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

	player.inventoryMode = false;

}
/*顯示玩家狀態*/
void ShowPlayerStatus() {
	cout << "press 'r' to manage inventory" << endl;
	cout << endl;
	cout << "X:" << player.x;
	cout << "  Y:" << player.y << endl;

	cout << "HP:" << player.hp << "/" << player.maxHp;
	cout << "     [" << player.armor.name << "] def:-" << player.armor.def * 100 <<
		"%  HP:" << player.armor.hp << "/" << player.armor.maxHp << endl;
	cout << "             [" << player.weapon.name << "]" << endl;
	cout << "----Inventory----" << endl;
	for (int i = 0; i < 64; i++) {
		if (player.inventory[i].flag == true) {
			cout << i + 1 << "." << player.inventory[i].name << endl;
		}
	}
}
/*初始隨機*/
void StartRnd() {
	unsigned seed;
	seed = (unsigned)time(NULL);
	srand(seed);
}
/*螢幕座標移動到(x,y)*/
inline void GotoXY(int x, int y) //移动坐标
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}