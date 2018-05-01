
#include "settings_ships.h"
#include "ships_flags.h"

int CompleteTraversal(char **matrix_field)
{
	for(int i = 0; i < FIELDSIZE; ++i)
		for(int j = 0; j < FIELDSIZE; ++j)
			if(matrix_field[i][j] == FIGURE)
				return 0;
	
	return 1;
}


void GetStartPoint(char **matrix_field, int start_point[2])
{
	for(int i = 0; i < FIELDSIZE; ++i)
		for(int j = 0; j < FIELDSIZE; ++j)
			if(matrix_field[i][j] == FIGURE)
			{
				start_point[0] = i;
				start_point[1] = j;
				return;
			}
}


//Find scale of ship on battle field for check to correct arrangement
void FindCurScale(char **matrix_field, int cur_point[2], int *cur_scale)
{
	int x = cur_point[0];
	int y = cur_point[1];

	if(x + 1 < FIELDSIZE  && matrix_field[x + 1][y] == FIGURE)
	{
		++*cur_scale;
		matrix_field[x + 1][y] = MARK;
		cur_point[0] = x + 1;
		cur_point[1] = y;
		FindCurScale(matrix_field, cur_point, cur_scale);
	}
	if(x - 1 >= 0 && matrix_field[x - 1][y] == FIGURE)
	{
		++*cur_scale;
		matrix_field[x - 1][y] = MARK;
		cur_point[0] = x - 1;
		cur_point[1] = y;
		FindCurScale(matrix_field, cur_point, cur_scale);
	}
	if(y + 1 < FIELDSIZE && matrix_field[x][y + 1] == FIGURE)
	{
		++*cur_scale;
		matrix_field[x][y + 1] = MARK;
		cur_point[0] = x;
		cur_point[1] = y + 1;
		FindCurScale(matrix_field, cur_point, cur_scale);
	}
	if(y - 1 >= 0 && matrix_field[x][y - 1] == FIGURE)
	{
		++*cur_scale;
		matrix_field[x][y - 1] = MARK;
		cur_point[0] = x;
		cur_point[1] = y - 1;
		FindCurScale(matrix_field, cur_point, cur_scale);
	}
}


