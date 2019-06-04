#pragma once
//地圖大小
#define MAPRANGE 7
#define ROOMRANGE 5*5+1

//地圖單位格類別
#define FLOOR 0
#define ROOM 1
#define WALL 2
#define ENEMY 8
#define PLAYER 9

//參數
#define MAX_ENEMY_IN_ONEROOM 3
#define ENEMYNUMBER 128
#define RE_ENEMYNUMBER 20 //移動步數
#define ENEMY_SPAWN_PROBABILITY 20 //生成機率
#define MAX_INVENTORY 64

//道具
#define NOTHING -1
#define WEAPON 0
#define ARMOR 1
#define ITEM 2

//武器
#define FIST 0
#define LONG_SWORD 1
#define AXE 2
#define SPEAR 3

//武器攻擊方式
#define ONE 1 //1格
#define TWO 2 //2格
#define BEVELED 3 //斜1格

//裝備
#define NO_ARMOR 0
#define LEATHER_ARMOR 1
#define HEAVY_LEATHE_RARMOR 2

//消耗品或寶藏
#define SIMPLE_POTION 0

//方向,72 77 80 75即表示方向键 上 右 下 左。
#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75
#define ENTER 13 // 定義按鍵值, 就是ASCII code 
#define ESC 27 
#define SPACE 32

