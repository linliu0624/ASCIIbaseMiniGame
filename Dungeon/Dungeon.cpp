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
void CreateEnemy();
///放置敵人
void SpawnEnemy();
///敵人行動
void EnemyMove();
///顯示敵人狀態
void ShowEnemyStatus();
///戰鬥
void Battle();
///玩家移動
void PlayerMove();
///裝備管理
void InventoryManage();

unit player;
unit enemy[128];
int enemyPtr = 0;
int enemyCount = 0;
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
	//設置螢幕寬高
	system("mode con cols=150 lines=30");
	char flag;
	clsFlag_Inventory = false;
	WeaponOption();
	ArmorOption();
	CreateVoid();
	CreateEnemy();
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
	SpawnEnemy();
	Refresh();
}

/*操作*/
void Update() {
	if (player.inventoryMode == false) {
		//int currentPlayerX = player.x, currentPlayerY = player.y;
		//int newPlayerX, newPlayerY;
		PlayerMove();
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
void CreateEnemy() {
	for (int i = 0; i < 128; i++) {
		//enemy[i].alive = true;
		enemy[i].maxHp = 10 + rand() % 5;
		enemy[i].hp = enemy[i].maxHp;
		enemy[i].type = ENEMY;
		enemy[i].weapon = sword;
		enemy[i].armor = leatherArmor;
	}
}
/*enemyの配置*/
void SpawnEnemy() {
	//PlayerPos of map turn to room
	int roomX_min, roomY_min, roomX_max, roomY_max;

	for (int i = 1; i < MAPRANGE - 1; i++) {
		for (int j = 1; j < MAPRANGE - 1; j++) {
			if (map[i][j].playerPos == true) {
				roomX_min = (j - 1) * 5; roomX_max = j * 5;
				roomY_min = (i - 1) * 5; roomY_max = i * 5;
			}
		}
	}
	for (int i = 1; i < ROOMRANGE; i++) {
		for (int j = 1; j < ROOMRANGE; j++) {
			if (i >= roomY_min && i <= roomY_max && j <= roomX_max && j >= roomX_min) {

			}
			else if (room[i][j].playerPos != true && room[i][j].type == FLOOR &&
				(i != 5 && i != 6 && i != 10 && i != 11 && i != 15 && i != 16 && i != 20 && i != 21) &&
				(j != 5 && j != 6 && j != 10 && j != 11 && j != 15 && j != 16 && j != 20 && j != 21)) {
				int rnd = rand() % 20;
				if (rnd == 3 || rnd == 5) {
					if (enemyCount < 2) {
						enemy[enemyPtr].alive = true;
						room[i][j].enemyPos = true;
						enemy[enemyPtr].x = j;
						enemy[enemyPtr].y = i;
						enemyPtr++;
						enemyCount++;
						if (enemyPtr == 127) {
							enemyPtr = 0;
						}
					}
				}
			}
			if ((j % 5 == 0 || i % 5 == 0) && enemyCount >= 2) {
				enemyCount = 0;
			}
		}
	}
}

/*プレーヤーのターン*/
void PlayerMove() {
	int ch;
	ch = _getch();
	//int currentX, currentY, newX, newY;
	//currentX = player.x; currentY = player.y;
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
		//newX = player.x; newY = player.y;
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
/*顯示敵人狀態*/ //寫法需要優化
void ShowEnemyStatus() {
	int roomX_min, roomX_max, roomY_min, roomY_max;
	int x = 50, y = 14;
	GotoXY(x, y++);
	cout << "enemyPtr:" << enemyPtr + 1 << endl;
	GotoXY(x, y++);
	int basicY = y;
	cout << "The enemy from left to right is the top left to bottom right of the picture." << endl;
	//找到玩家在大地圖中的位置
	for (int i = 1; i < MAPRANGE; i++) {
		for (int j = 1; j < MAPRANGE; j++) {
			if (map[i][j].playerPos == true) {
				//大地圖座標轉換為房間座標
				roomX_max = j * 5; roomX_min = roomX_max - 4;
				roomY_max = i * 5; roomY_min = roomY_max - 4;

				//搜尋房間座標中的敵人
				for (int i = roomY_min; i <= roomY_max; i++) {
					for (int j = roomX_min; j <= roomX_max; j++) {
						if (room[i][j].enemyPos == true) {
							for (int e = 0; e < 128; e++) {
								if (enemy[e].x == j && enemy[e].y == i) {
									y = basicY;
									GotoXY(x, y++);
									cout << "enemy hp:" << enemy[e].hp << endl;
									GotoXY(x, y++);
									cout << "weapon:" << enemy[e].weapon.name << endl;
									GotoXY(x, y++);
									cout << "armor:" << enemy[e].armor.name << endl;
									x += 25;
								}

							}

						}
					}
				}
			}
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