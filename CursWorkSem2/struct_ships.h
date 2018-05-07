#pragma once

#include "settings_ships.h"

typedef struct map 
{
	char matrix_battle[FIELDSIZE][FIELDSIZE];	
} Map;

typedef struct battle_ship
{
	int coordinate[4][2];
	int health[4];
} BattleShip;

typedef struct cruiser
{
	int coordinate[3][2];
	int health[3];
} Cruiser;

typedef struct destroyer
{
	int coordinate[2][2];
	int health[2];
} Destroyer;

typedef struct torpedo_boat
{
	int coordinate[1][2];
	int health[1];
} TorpedoBoat;


//struct for set orientation of enemy ships
typedef struct
{
	int horisontal;
	int right;
	int down;
} Orientation;


