
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define FIELDSIZE 10
#define COUNTSHIP 4

#define FOURDECK 1
#define THREEDECK 2
#define TWODECK 3
#define ONEDECK 4


typedef struct map 
{
	int matrix_battle[FIELDSIZE][FIELDSIZE];	
	int count_ships;
} Map;

typedef struct battle_ship
{
	int coordinate[4][2];
	int health;
} BattleShip;

typedef struct cruiser
{
	int coordinate[3][2];
	int health;
} Cruiser;

typedef struct destroyer
{
	int coordinate[2][2];
	int health;
} Destroyer;

typedef struct torpedo_boat
{
	int coordinate[1][2];
	int health;
} TorpedoBoat;


char const rows[FIELDSIZE] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
int const index_rows[FIELDSIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

int PointerIsNull(const void *p)
{
	if(p == NULL)
	{
		printf("NULL pointer!");
		return 1;
	}
	else
		return 0;
}

void InitializeMap(Map *pmap)
{
	if(PointerIsNull(pmap))
		return;

	for(int i = 0; i < FIELDSIZE; ++i)
		for(int j = 0; j < FIELDSIZE; ++j)
			pmap->matrix_battle[i][j] = 0;
	
	pmap->count_ships = COUNTSHIP;
}


int CharToIndex(char c)
{
	for(int i = 0; i < FIELDSIZE; ++i)
		if(c == rows[i])
			return i;
}


void PrintMap(const Map * pmap)
{
	if(PointerIsNull(pmap))
		return;

	printf("  "); //two space for first index in top line
	for(int i = 0; i < FIELDSIZE; ++i)
		printf("%d ", index_rows[i]);
	printf("\n");

	for(int i = 0; i < FIELDSIZE; ++i)
	{
		printf("%c ", rows[i]);
		for(int j = 0; j < FIELDSIZE; ++j)
			printf("%d ", pmap->matrix_battle[i][j]);
		printf("\n");
	}
}



int main()
{
	Map user_map;
	InitializeMap(&user_map);
	PrintMap(&user_map);
	
	BattleShip battle_ship[1];
	Cruiser cruiser[2];
	Destroyer destroyer[3];
	TorpedoBoat torpedo_boat[4];
	
	printf("Each coorinates line entered with new lines\n");
	printf("Please enter four coordinates for one battle ship to formate A1A2A3A4:\n");
	
	
	for(int i = 0; i < 1; ++i)
	{
		battle_ship[i].health = FOURDECK;
		char col;
		int row;
	
		for(int j = 0; j < 4; ++j)
		{
			if(scanf("%c%d", &col, &row)!= 2)
			{
				printf("Error input!\n");
				return 0;
			}
			else
			{
				printf("[%c, %d]\n", col, row);
				battle_ship[i].coordinate[j][0] = CharToIndex(toupper(col));
				battle_ship[i].coordinate[j][1] = row;
			}
		}
		getchar();
	}
	
	printf("Please enter three coordinates for two cruisers to formate A1A2A3:\n");

	for(int i = 0; i < 2; ++i)
	{
		cruiser[i].health = THREEDECK;
		char col;
		int row;

		for(int j = 0; j < 3; ++j)
		{
			if(scanf("%c%d", &col, &row)!= 2)
			{
				printf("Error input!\n");
				return 0;
			}
			else
			{
				printf("[%c, %d]\n", col, row);
				cruiser[i].coordinate[j][0] = CharToIndex(toupper(col));
				cruiser[i].coordinate[j][1] = row;
			}
		}
		getchar();
	}

	printf("Please enter three coordinates for three destroyers to formate A1A2:\n");

	for(int i = 0; i < 3; ++i)
	{
		destroyer[i].health = TWODECK;
		char col;
		int row;

		for(int j = 0; j < 2; ++j)
		{
			if(scanf("%c%d", &col, &row)!= 2)
			{
				printf("Error input!\n");
				return 0;
			}
			else
			{
				printf("[%c, %d]\n", col, row);
				destroyer[i].coordinate[j][0] = CharToIndex(toupper(col));
				destroyer[i].coordinate[j][1] = row;
			}
		}
		getchar();
	}

	printf("Please enter one coordinates for four destroyers to formate A1:\n");

	for(int i = 0; i < 4; ++i)
	{
		torpedo_boat[i].health = TWODECK;
		char col;
		int row;

		for(int j = 0; j < 1; ++j)
		{
			if(scanf("%c%d", &col, &row)!= 2)
			{
				printf("Error input!\n");
				return 0;
			}
			else
			{
				printf("[%c, %d]\n", col, row);
				torpedo_boat[i].coordinate[j][0] = CharToIndex(toupper(col));
				torpedo_boat[i].coordinate[j][1] = row;
			}
		}
		getchar();
	}


	return 0;
}
