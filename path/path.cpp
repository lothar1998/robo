#include "path.h"
#include <cstdlib>
#include <time.h>


path::path()
{
}

path::path(int sizeX, int sizeY, int** map, unsigned int forbidden_value) :path_base(sizeX, sizeY, map),forbidden_val(forbidden_value)
{
}

path::~path()
{
}

vector<coordinates> path::find_path(coordinates start, coordinates stop)
{
	const unsigned int start_x = start.get_x;
	const unsigned int start_y = start.get_y;
	const unsigned int stop_x = stop.get_x;
	const unsigned int stop_y = stop.get_y;

	vector<coordinates> path_coord;

	if (this->map[start_x][start_y] == this->forbidden_val || this->map[stop_x][stop_y] == this->forbidden_val)
		return path_coord;



	
}


coordinates path::draw_nearby_coordinate(unsigned int x, unsigned int y)
{
	srand(time(NULL));

	int draw_x, draw_y;

	do {
		draw_x = rand() % 3 - 1;
		draw_y = rand() % 3 - 1;
	} while (!((draw_x == 0 & draw_y == 0) || !is_exist(x + draw_x, y + draw_y)));


	
}

bool path::is_exist(int x, int y)
{
	if ((x >= 0 && x <= this->sizeX - 1) && (y >= 0 && y <= this->sizeY - 1))
		return true;
	else
		return false;
}