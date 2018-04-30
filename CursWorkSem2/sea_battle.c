
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "coordinate_enemy_ships.h"
#include "struct_ships.h"
#include "settings_ships.h"
#include "game_flags_and_matrix.h"


typedef struct
{
	int horisontal;
	int right;
	int down;
} Orientation;


void PrintMap(const Map * pmap)
{
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




void InitializeMap(Map *pmap)
{
	for(int i = 0; i < FIELDSIZE; ++i)
		for(int j = 0; j < FIELDSIZE; ++j)
			pmap->matrix_battle[i][j] = '0';
}

void InitializeMatrixHits(int matrix_hits[FIELDSIZE][FIELDSIZE])
{
	for(int i = 0; i < FIELDSIZE; ++i)
		for(int j = 0; j < FIELDSIZE; ++j)
			matrix_hits[i][j] = 0;
}



//Select orientation and next point of ship in map
void SetEnemyOrientation(Orientation *orientation, int x, int y, int deck)
{
	if(rand() % 2 == 1)
		orientation->horisontal = 1;
	if(y + deck - 1 < FIELDSIZE)
		orientation->right = 1;
	if(x + deck - 1 < FIELDSIZE)
		orientation->down = 1;	
}


void InitializeEnemyShips(BattleShip *pbattle_ship, Cruiser *pcruiser, Destroyer *pdestroyer, TorpedoBoat *ptorpedo_boat)
{
	srand(time(NULL));
	int x;
	int y;
	int matrix_coordinate[FIELDSIZE][FIELDSIZE];
	for(int i = 0; i < FIELDSIZE; ++i)
		for(int j = 0; j < FIELDSIZE; ++j)
			matrix_coordinate[i][j] = 0;

	for(int i = 0; i < COUNTFOURDECK; ++i)
	{
		while(1)
		{
			x = rand() % FIELDSIZE;
			y = rand() % FIELDSIZE;
			if(matrix_coordinate[x][y] == 0)
				break;
		}
		Orientation orientation = {0, 0, 0};
		SetEnemyOrientation(&orientation, x, y, 4);

		for(int j = 0; j < 4; ++j)
		{
			pbattle_ship[i].health[j] = 1;
			pbattle_ship[i].coordinate[j][0] = x;
			pbattle_ship[i].coordinate[j][1] = y;
			matrix_coordinate[x][y] = 1;
			if(orientation.horisontal)
			{
				if(orientation.right)
					++y;
				else
					--y;
			}
			else
			{
				if(orientation.down)
					++x;
				else
					--x;
			}
		}
	}
	for(int i = 0; i < COUNTTHREEDECK; ++i)
	{
		while(1)
		{
			x = rand() % FIELDSIZE;
			y = rand() % FIELDSIZE;
			if(matrix_coordinate[x][y] == 0)
				break;
		}
		Orientation orientation = {0, 0, 0};
		SetEnemyOrientation(&orientation, x, y, 4);

		for(int j = 0; j < 3; ++j)
		{
			pcruiser[i].health[j] = 1;
			pcruiser[i].coordinate[j][0] = x;
			pcruiser[i].coordinate[j][1] = y;
			matrix_coordinate[x][y] = 1;
			if(orientation.horisontal)
			{
				if(orientation.right)
					++y;
				else
					--y;
			}
			else
			{
				if(orientation.down)
					++x;
				else
					--x;
			}
		}
	}
	for(int i = 0; i < COUNTTWODECK; ++i)
	{
		while(1)
		{
			x = rand() % FIELDSIZE;
			y = rand() % FIELDSIZE;
			if(matrix_coordinate[x][y] == 0)
				break;
		}
		Orientation orientation = {0, 0, 0};
		SetEnemyOrientation(&orientation, x, y, 2);

		for(int j = 0; j < 2; ++j)
		{
			pdestroyer[i].health[j] = 1;
			pdestroyer[i].coordinate[j][0] = x;
			pdestroyer[i].coordinate[j][1] = y;
			matrix_coordinate[x][y] = 1;
			if(orientation.horisontal)
			{
				if(orientation.right)
					++y;
				else
					--y;
			}
			else
			{
				if(orientation.down)
					++x;
				else
					--x;
			}
		}
	}	
	for(int i = 0; i < COUNTONEDECK; ++i)
	{
		while(1)
		{
			x = rand() % FIELDSIZE;
			y = rand() % FIELDSIZE;
			if(matrix_coordinate[x][y] == 0)
				break;
		}
		Orientation orientation = {0, 0, 0};
		SetEnemyOrientation(&orientation, x, y, 1);

		for(int j = 0; j < 1; ++j)
		{
			ptorpedo_boat[i].health[j] = 1;
			ptorpedo_boat[i].coordinate[j][0] = x;
			ptorpedo_boat[i].coordinate[j][1] = y;
			matrix_coordinate[x][y] = 1;
			if(orientation.horisontal)
			{
				if(orientation.right)
					++y;
				else
					--y;
			}
			else
			{
				if(orientation.down)
					++x;
				else
					--x;
			}
		}
	}	
}




void CleanMap(Map *pmap)
{
	for(int i = 0; i < FIELDSIZE; ++i)
		for(int j = 0; j < FIELDSIZE; ++j)
			pmap->matrix_battle[i][j] = '0';
}

//Mark ships coordinate by + on map
void ChangeMap(Map *pmap, BattleShip *pbattle_ship, Cruiser *pcruiser, Destroyer *pdestroyer, TorpedoBoat *ptorpedo_boat)
{
	CleanMap(pmap);
	for(int i = 0; i < COUNTFOURDECK; ++i)
		for(int j = 0; j < 4; ++j)
		{
			int x = pbattle_ship[i].coordinate[j][0];
			int y = pbattle_ship[i].coordinate[j][1];
			pmap->matrix_battle[x][y] = '+';
		}

	for(int i = 0; i < COUNTTHREEDECK; ++i)
		for(int j = 0; j < 3; ++j)
		{
			int x = pcruiser[i].coordinate[j][0];
			int y = pcruiser[i].coordinate[j][1];
			pmap->matrix_battle[x][y] = '+';
		}

	for(int i = 0; i < COUNTTWODECK; ++i)
		for(int j = 0; j < 2; ++j)
		{
			int x = pdestroyer[i].coordinate[j][0];
			int y = pdestroyer[i].coordinate[j][1];
			pmap->matrix_battle[x][y] = '+';
		}

	for(int i = 0; i < COUNTONEDECK; ++i)
		for(int j = 0; j < 1; ++j)
		{
			int x = ptorpedo_boat[i].coordinate[j][0];
			int y = ptorpedo_boat[i].coordinate[j][1];
			pmap->matrix_battle[x][y] = '+';
		}
}



int VoidSpaceAroundShips(BattleShip *pbattle_ship, Cruiser *pcruiser, Destroyer *pdestroyer, TorpedoBoat *ptorpedo_boat) 
{	
	for(int i = 0; i < 4; ++i)
	{
		int x = pbattle_ship[0].coordinate[i][0];
		int y = pbattle_ship[0].coordinate[i][1];

		for(int j = 0; j < 2; ++j)
			for(int k = 0; k < 3; ++k)
				if(abs(x - pcruiser[j].coordinate[k][0]) < 2 && abs(y - pcruiser[j].coordinate[k][1]) < 2)
					return 0;
		for(int j = 0; j < 3; ++j)
			for(int k = 0; k < 2; ++k)
				if(abs(x - pdestroyer[j].coordinate[k][0]) < 2 && abs(y - pdestroyer[j].coordinate[k][1]) < 2)
					return 0;
		for(int j = 0; j < 4; ++j)
			for(int k = 0; k < 1; ++k)
				if(abs(x - ptorpedo_boat[j].coordinate[k][0]) < 2 && abs(y - ptorpedo_boat[j].coordinate[k][1]) < 2)
					return 0;
	}
	for(int i_s = 0; i_s < COUNTTHREEDECK; ++i_s)
	{
		for(int i = 0; i < 3; ++i)
		{
			int x = pcruiser[i_s].coordinate[i][0];
			int y = pcruiser[i_s].coordinate[i][1];
			
			//Check first three deck ship with second three deck ship
			for(int j = 1; j < 2 && i_s!= 1; ++j)
				for(int k = 0; k < 3; ++k)
					if(abs(x - pcruiser[j].coordinate[k][0]) < 2 && abs(y - pcruiser[j].coordinate[k][1]) < 2)
						return 0;
						
			for(int j = 0; j < 3; ++j)
				for(int k = 0; k < 2; ++k)
					if(abs(x - pdestroyer[j].coordinate[k][0]) < 2 && abs(y-pdestroyer[j].coordinate[k][1]) < 2)
						return 0;
			for(int j = 0; j < 4; ++j)
				for(int k = 0; k < 1; ++k)
					if(abs(x - ptorpedo_boat[j].coordinate[k][0]) < 2 && abs(y - ptorpedo_boat[j].coordinate[k][1]) < 2)
						return 0;
		}
	}
	for(int i_s = 0; i_s < COUNTTWODECK; ++i_s)
	{
		for(int i = 0; i < COUNTTWODECK; ++i)
		{
			int x = pdestroyer[i_s].coordinate[i][0];
			int y = pdestroyer[i_s].coordinate[i][1];
		
			for(int j = 1; j < 3 && i_s!= j; ++j)
				for(int k = 0; k < 2; ++k)
					if(abs(x - pdestroyer[j].coordinate[k][0]) < 2 && abs(y-pdestroyer[j].coordinate[k][1]) < 2)
						return 0;
			for(int j = 0; j < 4; ++j)
				for(int k = 0; k < 1; ++k)
					if(abs(x - ptorpedo_boat[j].coordinate[k][0]) < 2 && abs(y - ptorpedo_boat[j].coordinate[k][1]) < 2)
						return 0;
		}
	}

	
	return 1;
}


//Check coordinates of ship for diagonal and horisontal correct
int CorrectCoordinates(int coordinate[2][2], int deck)
{	
	int horisontal_flag;
	int vertical_flag = 0;
	if(coordinate[0][0] == coordinate[1][0])
		horisontal_flag = 1;
	if(coordinate[0][0] == coordinate[1][0])
		vertical_flag = 1;

	if(horisontal_flag && vertical_flag)
		return 0;
	
	//Check coordinates to vertical/diagonal coorect
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
	for(int i = 0; i < COUNTFOURDECK; ++i)
		if(!CorrectCoordinates(pbattle_ship[i].coordinate, 4))
			return 0;

	for(int i = 0; i < COUNTTHREEDECK; ++i)
		if(!CorrectCoordinates(pcruiser[i].coordinate, 3))
			return 0;
	
	for(int i = 0; i < COUNTTWODECK; ++i)
		if(!CorrectCoordinates(pdestroyer[i].coordinate, 2))
			return 0;

	return 1;
}

//Counting points + on map. Correct is 20
int CorrectInsert(Map *pmap)
{
	int count_cell = 0;

	for(int i = 0; i < FIELDSIZE; ++i)
		for(int j = 0; j < FIELDSIZE; ++j)
			if(pmap->matrix_battle[i][j] == '+')
				++count_cell;
		
	if(count_cell == COUNTCELLOFSHIPS)
	{
		return 1;
	}
	else
		return 0;
}



//Check ship for destroy
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

	for(int i = 0; i < COUNTFOURDECK; ++i)
		for(int j = 0; j < 4; ++j)
			if(pbattle_ship[i].coordinate[j][0] == x && pbattle_ship[i].coordinate[j][1] == y)
			{
				pbattle_ship[i].health[j] = 0;
				if(DestroyedShip(pbattle_ship[i].health, 4))
					return DESTROYED;
				else 
					return HIJACKING;
			}

	for(int i = 0; i < COUNTTHREEDECK; ++i)
		for(int j = 0; j < 3; ++j)
			if(pcruiser[i].coordinate[j][0] == x && pcruiser[i].coordinate[j][1] == y)
			{
				pcruiser[i].health[j] = 0;
				if(DestroyedShip(pcruiser[i].health, 3))
					return DESTROYED;
				else 
					return HIJACKING;
			}

	for(int i = 0; i < COUNTTWODECK; ++i)
		for(int j = 0; j < 2; ++j)
			if(pdestroyer[i].coordinate[j][0] == x && pdestroyer[i].coordinate[j][1] == y)
			{
				pdestroyer[i].health[j] = 0;
				if(DestroyedShip(pdestroyer[i].health, 2))
					return DESTROYED;
				else 
					return HIJACKING;
			}

	for(int i = 0; i < COUNTONEDECK; ++i)
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



//Trancfer char to index for matrix of battle
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

	InitializeEnemyShips(&enemy_battle_ship[0], &enemy_cruiser[0], &enemy_destroyer[0], &enemy_torpedo_boat[0]);
	ChangeMap(&enemy_map, &enemy_battle_ship[0], &enemy_cruiser[0], &enemy_destroyer[0], &enemy_torpedo_boat[0]);
	//because function of random dot't check ships for insert(only horisonatal and vertical corrects)
	while(!CorrectInsert(&enemy_map))
	{
		InitializeEnemyShips(&enemy_battle_ship[0], &enemy_cruiser[0], &enemy_destroyer[0], &enemy_torpedo_boat[0]);
		ChangeMap(&enemy_map, &enemy_battle_ship[0], &enemy_cruiser[0], &enemy_destroyer[0], &enemy_torpedo_boat[0]);
	}
	PrintMap(&enemy_map);

/*	
	printf("Each coorinates line enter with new line\n");
	printf("Please enter four coordinates for one battle ship to formate A1A2A3A4:\n");
		
	for(int i = 0; i < COUNTFOURDECK; ++i)
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
				//printf("[%c, %d]\n", col, row);
				user_battle_ship[i].coordinate[j][0] = CharToIndex(toupper(col));
				user_battle_ship[i].coordinate[j][1] = row;
			}
		}
		getchar(); //for \n
	}
	
	printf("Please enter three coordinates for two cruisers to formate A1A2A3:\n");

	for(int i = 0; i < COUNTTHREEDECK; ++i)
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
				//printf("[%c, %d]\n", col, row);
				user_cruiser[i].coordinate[j][0] = CharToIndex(toupper(col));
				user_cruiser[i].coordinate[j][1] = row;
			}
		}
		getchar();
	}

	printf("Please enter three coordinates for three destroyers to formate A1A2:\n");

	for(int i = 0; i < COUNTTWODECK; ++i)
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
				//printf("[%c, %d]\n", col, row);
				user_destroyer[i].coordinate[j][0] = CharToIndex(toupper(col));
				user_destroyer[i].coordinate[j][1] = row;
			}
		}
		getchar();
	}

	printf("Please enter one coordinates for four destroyers to formate A1:\n");

	for(int i = 0; i < COUNTONEDECK; ++i)
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
				//printf("[%c, %d]\n", col, row);
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
	{
		printf("Ships insert between each other!\n");
		return 0;	
	}
	if(CorrectShips(&user_battle_ship[0], &user_cruiser[0], &user_destroyer[0]))
		printf("Correct coordinates of ships\n");
	else
	{
		printf("Incorrect coordinates of ships!\n");
		return 0;
	}
	
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
				printf("Count of enemy ships = %d\n", count_enemy_ships);
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
		printf("--------\nYou win!\n---------");
	else if(!count_user_ships)
		printf("--------\nYou lose\n---------");

*/	
	return 0;
}
