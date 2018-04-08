
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
			pmap->matrix_battle[i][j] = '0';
}

void PrintMap(const Map * pmap)
{
	if(PointerIsNull(pmap))
		return;

	printf("  "); //two space for first index in top line
	for(int i = 0; i < FIELDSIZE; ++i)
		printf("%c ", index_rows[i]);
	printf("\n");

	for(int i = 0; i < FIELDSIZE; ++i)
	{
		printf("%c ", rows[i]);
		for(int j = 0; j < FIELDSIZE; ++j)
			printf("%c ", pmap->matrix_battle[i][j]);
		printf("\n");
	}
}


void ChangeMap(Map *pmap, BattleShip *pbattle_ship, Cruiser *pcruiser, Destroyer *pdestroyer, TorpedoBoat *ptorpedo_boat)
{
	for(int i = 0; i < 1; ++i)
		for(int j = 0; j < 4; ++j)
		{
			int x = pbattle_ship[i].coordinate[j][0];
			int y = pbattle_ship[i].coordinate[j][1];

			switch(pbattle_ship[i].health[j])
			{
				case 1:
					pmap->matrix_battle[x][y] = '+';
					break;
				case 0:
					pmap->matrix_battle[x][y] = 'X';
					break;
			}
		}

	for(int i = 0; i < 2; ++i)
		for(int j = 0; j < 3; ++j)
		{
			int x = pcruiser[i].coordinate[j][0];
			int y = pcruiser[i].coordinate[j][1];

			switch(pcruiser[i].health[j])
			{
				case 1:
					pmap->matrix_battle[x][y] = '+';
					break;
				case 0:
					pmap->matrix_battle[x][y] = 'X';
					break;
			}
		}

	for(int i = 0; i < 3; ++i)
		for(int j = 0; j < 2; ++j)
		{
			int x = pdestroyer[i].coordinate[j][0];
			int y = pdestroyer[i].coordinate[j][1];

			switch(pdestroyer[i].health[j])
			{
				case 1:
					pmap->matrix_battle[x][y] = '+';
					break;
				case 0:
					pmap->matrix_battle[x][y] = 'X';
					break;
			}
		}

	for(int i = 0; i < 4; ++i)
		for(int j = 0; j < 1; ++j)
		{
			int x = ptorpedo_boat[i].coordinate[j][0];
			int y = ptorpedo_boat[i].coordinate[j][1];

			switch(ptorpedo_boat[i].health[j])
			{
				case 1:
					pmap->matrix_battle[x][y] = '+';
					break;
				case 0:
					pmap->matrix_battle[x][y] = 'X';
					break;
			}
		}


}


int CharToIndex(char c)
{
	for(int i = 0; i < FIELDSIZE; ++i)
		if(c == rows[i])
			return i;
}


int OutOfRange(int x, int y)
{if(x < 0 || x > 9 || y < 0 | y > 9)
	{
		printf("Coordinate out of range!\n");
		return 1;
	}
	else
		return 0;
}

int main()
{
	Map user_map;
	InitializeMap(&user_map);
	PrintMap(&user_map);
	
	BattleShip user_battle_ship[1];
	Cruiser user_cruiser[2];
	Destroyer user_destroyer[3];
	TorpedoBoat user_torpedo_boat[4];
	
	printf("Each coorinates line entered with new line\n");
	printf("Please enter four coordinates for one battle ship to formate A1A2A3A4:\n");
		
	for(int i = 0; i < 1; ++i)
	{
		char col;
		int row;
	
		for(int j = 0; j < 4; ++j)
		{
			user_battle_ship[i].health[j] = 1;

			if(scanf("%c%d", &col, &row)!= 2)
			{
				printf("Error input!\n");
				return 0;
			}
			if(OutOfRange(CharToIndex(toupper(col)), row))
				return 0;
			else
			{
				printf("[%c, %d]\n", col, row);
				user_battle_ship[i].coordinate[j][0] = CharToIndex(toupper(col));
				user_battle_ship[i].coordinate[j][1] = row;
			}
		}
		getchar();
	}
	
	printf("Please enter three coordinates for two cruisers to formate A1A2A3:\n");

	for(int i = 0; i < 2; ++i)
	{
		char col;
		int row;

		for(int j = 0; j < 3; ++j)
		{
			user_cruiser[i].health[j] = 1;

			if(scanf("%c%d", &col, &row)!= 2)
			{
				printf("Error input!\n");
				return 0;
			}
			if(OutOfRange(CharToIndex(toupper(col)), row))
				return 0;
			else
			{
				printf("[%c, %d]\n", col, row);
				user_cruiser[i].coordinate[j][0] = CharToIndex(toupper(col));
				user_cruiser[i].coordinate[j][1] = row;
			}
		}
		getchar();
	}

	printf("Please enter three coordinates for three destroyers to formate A1A2:\n");

	for(int i = 0; i < 3; ++i)
	{
		char col;
		int row;

		for(int j = 0; j < 2; ++j)
		{
			user_destroyer[i].health[j] = 1;

			if(scanf("%c%d", &col, &row)!= 2)
			{
				printf("Error input!\n");
				return 0;
			}
			if(OutOfRange(CharToIndex(toupper(col)), row))
				return 0;
			else
			{
				printf("[%c, %d]\n", col, row);
				user_destroyer[i].coordinate[j][0] = CharToIndex(toupper(col));
				user_destroyer[i].coordinate[j][1] = row;
			}
		}
		getchar();
	}

	printf("Please enter one coordinates for four destroyers to formate A1:\n");

	for(int i = 0; i < 4; ++i)
	{
		char col;
		int row;

		for(int j = 0; j < 1; ++j)
		{
			user_torpedo_boat[i].health[j] = 1;

			if(scanf("%c%d", &col, &row)!= 2)
			{
				printf("Error input!\n");
				return 0;
			}
			if(OutOfRange(CharToIndex(toupper(col)), row))
				return 0;
			else
			{
				printf("[%c, %d]\n", col, row);
				user_torpedo_boat[i].coordinate[j][0] = CharToIndex(toupper(col));
				user_torpedo_boat[i].coordinate[j][1] = row;
			}
		}
		getchar();
	}
	

	ChangeMap(&user_map, &user_battle_ship[0], &user_cruiser[0], &user_destroyer[0], &user_torpedo_boat[0]);
	PrintMap(&user_map);

	return 0;
}
