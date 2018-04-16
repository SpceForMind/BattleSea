
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "enemy_ships.h"

#define FIELDSIZE 10
#define COUNTSHIP 4

#define FOURDECK 1
#define THREEDECK 2
#define TWODECK 3
#define ONEDECK 4

#define COUNTCELLOFSHIPS 20

#define HIJACKING 1
#define DESTROYED 2


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
		printf("%d ", index_rows[i]);
	printf("\n");

	for(int i = 0; i < FIELDSIZE; ++i)
	{
		printf("%c ", rows[i]);
		for(int j = 0; j < FIELDSIZE; ++j)
			printf("%c ", pmap->matrix_battle[i][j]);
		printf("\n");
	}
}


void InitializeEnemyShips(BattleShip *pbattle_ship, Cruiser *pcruiser, Destroyer *pdestroyer, TorpedoBoat *ptorpedo_boat)
{
	srand(time(NULL));
//	int index = ((unsigned int)rand()) % 3;
	int index = 1;

	for(int i = 0; i < 1; i++)
	{
		for(int j = 0; j < 4; ++j)
		{
			pbattle_ship[i].health[j] = 1;
			pbattle_ship[i].coordinate[j][0] = coordinate_battle_ships[index][j][0];
			pbattle_ship[i].coordinate[j][1] = coordinate_battle_ships[index][j][1];
		}	
	}	
	
	for(int i = 0; i < 2; i++)
		for(int j = 0; j < 3; ++j)
		{
			pcruiser[i].health[j] = 1;
			pcruiser[i].coordinate[j][0] = coordinate_cruiser[index][i][j][0];
			pcruiser[i].coordinate[j][1] = coordinate_cruiser[index][i][j][1];
		}

	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 2; ++j)
		{
			pdestroyer[i].health[j] = 1;
			pdestroyer[i].coordinate[j][0] = coordinate_destroyer[index][i][j][0];
			pdestroyer[i].coordinate[j][1] = coordinate_destroyer[index][i][j][1];
		}

	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 1; ++j)
		{
			ptorpedo_boat[i].health[j] = 1;
			ptorpedo_boat[i].coordinate[j][0] = coordinate_torpedo_boat[index][i][j][0];
			ptorpedo_boat[i].coordinate[j][1] = coordinate_torpedo_boat[index][i][j][1];
		}	
}


//Mark ships coordinate by + on map
void ChangeMap(Map *pmap, BattleShip *pbattle_ship, Cruiser *pcruiser, Destroyer *pdestroyer, TorpedoBoat *ptorpedo_boat)
{
	for(int i = 0; i < 1; ++i)
		for(int j = 0; j < 4; ++j)
		{
			int x = pbattle_ship[i].coordinate[j][0];
			int y = pbattle_ship[i].coordinate[j][1];
			pmap->matrix_battle[x][y] = '+';
		}

	for(int i = 0; i < 2; ++i)
		for(int j = 0; j < 3; ++j)
		{
			int x = pcruiser[i].coordinate[j][0];
			int y = pcruiser[i].coordinate[j][1];
			pmap->matrix_battle[x][y] = '+';
		}

	for(int i = 0; i < 3; ++i)
		for(int j = 0; j < 2; ++j)
		{
			int x = pdestroyer[i].coordinate[j][0];
			int y = pdestroyer[i].coordinate[j][1];
			pmap->matrix_battle[x][y] = '+';
		}

	for(int i = 0; i < 4; ++i)
		for(int j = 0; j < 1; ++j)
		{
			int x = ptorpedo_boat[i].coordinate[j][0];
			int y = ptorpedo_boat[i].coordinate[j][1];
			pmap->matrix_battle[x][y] = '+';
		}


}


int CorrectCoordinates(int coordinate[2][2], int deck)
{	
	int vertical_flag = 0;
	int horisontal_flag = 0;

	if(coordinate[0][0] == coordinate[1][0])
		horisontal_flag = 1;
	else if(coordinate[0][1] == coordinate[1][1])
		vertical_flag = 1;
	if(horisontal_flag && vertical_flag)
		return 0;
	
	if(vertical_flag)
		for(int i = 0; i < deck - 1; ++i)
		{
			int dx = coordinate[i][0] - coordinate[i + 1][0];
			if(coordinate[i][1]!= coordinate[i + 1][1] || (dx!= 1 && dx!= -1))
				return 0;
		}
	if(horisontal_flag)
		for(int i = 0; i < deck - 1; ++i)
		{
			int dy = coordinate[i][1] - coordinate[i + 1][1];
			if(coordinate[i][0]!= coordinate[i + 1][0] || (dy!= 1 && dy!= -1))
				return 0;
		}
	
	return 1;
}




int CorrectShips(BattleShip *pbattle_ship, Cruiser *pcruiser, Destroyer *pdestroyer)
{
	for(int i = 0; i < 1; ++i)
		if(!CorrectCoordinates(pbattle_ship[i].coordinate, 4))
			return 0;

	for(int i = 0; i < 2; ++i)
		if(!CorrectCoordinates(pcruiser[i].coordinate, 3))
			return 0;
	
	for(int i = 0; i < 3; ++i)
		if(!CorrectCoordinates(pdestroyer[i].coordinate, 2))
			return 0;

	return 1;
}


int CorrectInsert(Map *pmap)
{
	int count_cell = 0;

	for(int i = 0; i < FIELDSIZE; ++i)
		for(int j = 0; j < FIELDSIZE; ++j)
			if(pmap->matrix_battle[i][j] == '+')
				++count_cell;
		
	if(count_cell == COUNTCELLOFSHIPS)
		return 1;
	else
		return 0;
}


int DestroyedShip(int health[1], int deck)
{
	int destroy_flag = 0;

	for(int i = 0; i < deck; ++i)
		destroy_flag += health[i];
	if(!destroy_flag)
		return 1;
	else
		return 0;
}

int ChangeHealthShip(BattleShip *pbattle_ship, Cruiser *pcruiser, Destroyer *pdestroyer, TorpedoBoat *ptorpedo_boat, 
		     int shot[2])
{
	int x = shot[0];
	int y = shot[1];

	for(int i = 0; i < 1; ++i)
		for(int j = 0; j < 4; ++j)
			if(pbattle_ship[i].coordinate[j][0] == x && pbattle_ship[i].coordinate[j][1] == y)
			{
				pbattle_ship[i].health[j] = 0;
				if(DestroyedShip(pbattle_ship[i].health, 4))
					return DESTROYED;
				else 
					return HIJACKING;
			}

	for(int i = 0; i < 2; ++i)
		for(int j = 0; j < 3; ++j)
			if(pcruiser[i].coordinate[j][0] == x && pcruiser[i].coordinate[j][1] == y)
			{
				pcruiser[i].health[j] = 0;
				if(DestroyedShip(pcruiser[i].health, 3))
					return DESTROYED;
				else 
					return HIJACKING;
			}

	for(int i = 0; i < 3; ++i)
		for(int j = 0; j < 2; ++j)
			if(pdestroyer[i].coordinate[j][0] == x && pdestroyer[i].coordinate[j][1] == y)
			{
				pdestroyer[i].health[j] = 0;
				if(DestroyedShip(pdestroyer[i].health, 2))
					return DESTROYED;
				else 
					return HIJACKING;
			}

	for(int i = 0; i < 4; ++i)
		for(int j = 0; j < 1; ++j)
			if(ptorpedo_boat[i].coordinate[j][0] == x && ptorpedo_boat[i].coordinate[j][1] == y)
			{
				ptorpedo_boat[i].health[j] = 0;
				if(DestroyedShip(ptorpedo_boat[i].health, 1))
					return DESTROYED;
				else
					return HIJACKING;
			}
	return 0;
}


void MarkShotOnMap(Map *pmap, int shot[2])
{
	int x = shot[0];
	int y = shot[1];

	if(pmap->matrix_battle[x][y] == '+')
		pmap->matrix_battle[x][y] = 'X'; 
	else if(pmap->matrix_battle[x][y] == '0')
		pmap->matrix_battle[x][y] = 'x';
}


void MarkShotOnEnemyMap(Map *pmap, Map *pvisual_map, int shot[2])
{
	int x = shot[0];
	int y = shot[1];
	
	if(pmap->matrix_battle[x][y] == '+')
		pvisual_map->matrix_battle[x][y] = 'X';
	else
		pvisual_map->matrix_battle[x][y] = 'x';
}


int CharToIndex(char c)
{
	for(int i = 0; i < FIELDSIZE; ++i)
		if(c == rows[i])
			return i;
	
	printf("Coordinate out of range A-J!\n");
	exit(1);
}


int OutOfRange(int x, int y)
{
	if(x < 0 || x > 9 || y < 0 | y > 9)
	{
		printf("Coordinate out of range!\n");
		return 1;
	}
	else
		return 0;
}


// Choise new hit for computer
int RandomOffset()
{
	int r_num = (unsigned int)rand() % 10;
	
	if(r_num < 3 )
		return 1;
	else if(r_num >= 3 && r_num < 6 )
		return 0;
	else	
		return 1;
}

void InitializeMatrixHits(int matrix_hits[FIELDSIZE][FIELDSIZE])
{
	for(int i = 0; i < FIELDSIZE; ++i)
		for(int j = 0; j < FIELDSIZE; ++j)
			matrix_hits[i][j] = 0;
}

void EnemyHit(int shot[2], int matrix_hits[FIELDSIZE][FIELDSIZE], int hijacking_flag)
{
	int x = shot[0];
	int y = shot[1];
	int new_hit_flag = 0;

	if(!hijacking_flag)
	{
		while(!new_hit_flag)
		{
			x = ((unsigned int)rand()) % 10;
			y = ((unsigned int)rand()) % 10;

			if(matrix_hits[x][y] == 0)
			{
				matrix_hits[x][y] = 1;
				new_hit_flag = 1;
			}
		}
	}
	else
	{
		int time_x = x;
		int time_y = y;
		int count_try = 40; //except, when around shot point look points yet

		while(!new_hit_flag && count_try)
		{
			time_x = x + RandomOffset();
			time_y = y + RandomOffset();
			
			if(!OutOfRange(time_x, time_y) && matrix_hits[time_x][time_y] == 0 &&(abs(x-time_x)!= abs(y-time_y)))
			{
				matrix_hits[time_x][time_y] = 1;
				new_hit_flag = 1;
				x = time_x;
				y = time_y;
				break;
			}
			--count_try;
		}
		if(!count_try)
		{
			x = ((unsigned int)rand()) % 10;
			y = ((unsigned int)rand()) % 10;
		}
	}

	shot[0] = x;
	shot[1] = y;
}





int main()
{
	Map user_map;
	InitializeMap(&user_map);
//	PrintMap(&user_map);
	
	BattleShip user_battle_ship[1];
	Cruiser user_cruiser[2];
	Destroyer user_destroyer[3];
	TorpedoBoat user_torpedo_boat[4];


	Map enemy_map;
	Map enemy_visual_map; //for incapsulation data of position the enemy ships
	InitializeMap(&enemy_map);
	InitializeMap(&enemy_visual_map);

	BattleShip enemy_battle_ship[1];
	Cruiser enemy_cruiser[2];
	Destroyer enemy_destroyer[3];
	TorpedoBoat enemy_torpedo_boat[4];
	
	//Initialize by one of three random pack in file enemy_ship.h and change enemy map
	InitializeEnemyShips(&enemy_battle_ship[0], &enemy_cruiser[0], &enemy_destroyer[0], &enemy_torpedo_boat[0]);
	ChangeMap(&enemy_map, &enemy_battle_ship[0], &enemy_cruiser[0], &enemy_destroyer[0], &enemy_torpedo_boat[0]);

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
	printf("Start user map:\n");
	PrintMap(&user_map);

	//Check for correct coordinate of ships
	if(CorrectInsert(&user_map))
		printf("Ships no insert between each other\n");
	else
		printf("Ships insert between each other!\n");	
	if(CorrectShips(&user_battle_ship[0], &user_cruiser[0], &user_destroyer[0]))
		printf("Correct coordinates of ships\n");
	else
		printf("Incorrect coordinates of ships!\n");
	
	//Battle progress
	int count_user_ships = 10;
	int count_enemy_ships = 10;
	int user_hit = 1; 
	int enemy_hit = 0; 
	int matrix_hits[FIELDSIZE][FIELDSIZE]; //matrix for coordinates, which computer already select
	int hijacking_flag = 0; //flag for next enemy hit(random point or around with some point)

	InitializeMatrixHits(&matrix_hits[0]);
	srand(time(NULL));

	while(count_user_ships && count_enemy_ships)
	{
		int row;
		char col;
		int shot[2];

		if(enemy_hit)
		{
			EnemyHit(shot, &matrix_hits[0], hijacking_flag);
			printf("Enemy shot:%c%u\n", rows[shot[0]], shot[1]);
			MarkShotOnMap(&user_map, shot);
			printf("User map:\n");
			PrintMap(&user_map);

			int course_res = ChangeHealthShip(&user_battle_ship[0], &user_cruiser[0], &user_destroyer[0], &user_torpedo_boat[0],shot);
			if(course_res == DESTROYED)
				--count_user_ships;
			else if(course_res == HIJACKING)
				hijacking_flag = 1;
			else 
			{
				hijacking_flag = 0;
				enemy_hit = 0; 
				user_hit = 1;
			}
			
			
		}
	
		if(user_hit)
		{
			printf("Enter coordinate of hit in format A1\n");
			if(scanf("%c%d", &col, &row)!= 2)
			{	
				printf("%c%d\n", col, row);
				printf("Incorrect coordinate!\n");
				return 0;
			}
			getchar();
		
			shot[0] = CharToIndex(toupper(col));
			shot[1] = row;
			if(OutOfRange(shot[0], shot[1]))
			{
				printf("(%d, %d)\n", shot[0], shot[1]);
				return 0;
			}
		
			MarkShotOnEnemyMap(&enemy_map, &enemy_visual_map, shot); 
			printf("Enemy map:\n");
			PrintMap(&enemy_visual_map);

			//variable for check shot to hikacking to ship or destroyed to ship
			int course_res = ChangeHealthShip(&enemy_battle_ship[0], &enemy_cruiser[0], &enemy_destroyer[0], &enemy_torpedo_boat[0],shot);
			if(course_res == DESTROYED)
			{
				--count_enemy_ships;
				printf("--------\nDestroyed!\n---------\n");
				printf("count_enemy_ships = %d\n", count_enemy_ships);
			}
			else if(course_res == HIJACKING)
				printf("--------\nHijackig!\n---------\n");
			else
			{
				user_hit = 0;
				enemy_hit = 1;
			}
		}
	}
	
	if(!count_enemy_ships)
		printf("--------\nYou win!\n----------");
	else if(!count_user_ships)
		printf("--------\nYou lose\n----------");
	

	return 0;
}
