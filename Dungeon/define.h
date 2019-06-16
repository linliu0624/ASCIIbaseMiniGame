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
#define ENEMYNUMBER 64
#define RE_ENEMYNUMBER 20 //移動步數
#define ENEMY_SPAWN_PROBABILITY 20 //生成機率
#define MAX_INVENTORY 128
#define INIT_MAX_WEIGHT 50
#define GOAL_VALUE 250

//道具
#define NOTHING -1
#define WEAPON 0
#define ARMOR 1
#define ITEM 2

//武器攻擊類型
#define CUT 0
#define STAB 1
#define CUT_STAB 3
#define BEATEN 4
//護甲防禦類型
#define NORMAL_DEF 0
#define CNAT_DEF_STAB 1
//武器
#define FIST 0
//剣
#define LONG_SWORD 1
#define SHORT_SWORD 2
#define BANANA 3
#define GRADUATION_CERTIFICATE_TUBE 4
#define CUTLASS 5
//斧
#define BATTLE_AXE 6
#define KENDAMA 7
#define MARIUS 8
#define OBRIST 9
//槍
#define SPEAR 10
#define POCKY 11
#define GUNGNIR 12
#define GAE_BULG 13
#define SCORPION 14

//武器攻擊方式
#define ONE 1 //1格
#define TWO 2 //2格
#define BEVELED 3 //斜1格

//裝備
#define NO_ARMOR 0
#define LEATHER_ARMOR 1
#define HEAVY_LEATHE_RARMOR 2
#define CHAINMAIL 4
//消耗品或寶藏
#define SIMPLE_POTION 0
#define SUPER_POTION 1

#define GOLD 11
#define SILVER 12
#define IVORY 13
#define BROKEN_DIAMOND 14

//場景
#define INIT_SCEAN 0
#define UPDATE_SCEAN 1
//方向,72 77 80 75即表示方向键 上 右 下 左。
#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75
#define ENTER 13 // 定義按鍵值, 就是ASCII code 
#define ESC 27 
#define SPACE 32

