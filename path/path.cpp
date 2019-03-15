#include "path.h"
#include <random>
#include <iostream>//delete

using namespace std;

path::path()
{
}

path::path(int sizeX, int sizeY, int** map, unsigned int forbidden_value) :path_base(sizeX, sizeY, map),forbidden_val(forbidden_value)
{
	/*
	set directions[n][XY]

	0 - 1 - 2
	| \ | / |
	3 - x - 4
	| / | \ |
	5 - 6 - 7
	*/


	directions[0][0] = -1;
	directions[0][1] = -1;

	directions[1][0] = 0;
	directions[1][1] = -1;

	directions[2][0] = 1;
	directions[2][1] = -1;

	directions[3][0] = -1;
	directions[3][1] = 0;

	directions[4][0] = 1;
	directions[4][1] = 0;

	directions[5][0] = -1;
	directions[5][1] = 1;

	directions[6][0] = 0;
	directions[6][1] = 1;

	directions[7][0] = 1;
	directions[7][1] = 1;
}

path::~path()
{
}

vector<coordinates> path::find_optimal_path(coordinates start, coordinates stop)
{
	vector<coordinates> path_coord;

	/*---check start&stop coordinates correctness---*/

	if (this->map[start.get_x()][start.get_y()] == this->forbidden_val || this->map[stop.get_x()][stop.get_y()] == this->forbidden_val)
		return path_coord;

	find_path(&start, &stop, &path_coord);

	return path_coord;

}

vector<coordinates>* path::find_path(coordinates *start, coordinates *stop, vector<coordinates> *path_coordinates)
{
	/*----set random generator----*/

	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0,7);
	
	ile = 0;//delete

	coordinates temp(start->get_x(),start->get_y());

	path_coordinates->push_back(temp);

	int draw_x, draw_y;
	unsigned short int r;


	do
	{
		do {
			r = distribution(generator);
			draw_x = temp.get_x() + directions[r][1];
			draw_y = temp.get_y() + directions[r][2];
			ile += 2;
		} while ((draw_x == temp.get_x() && draw_y == temp.get_y()) || !is_inside_map(&draw_x, &draw_y));

		temp.set_coordinates(draw_x, draw_y);

		path_coordinates->push_back(temp);

	} while (temp.get_x() != stop->get_x() || temp.get_y() != stop->get_y());

	cout << "percentage: " << (double)((double)(path_coordinates->size()) / (double)ile) << endl;//delete

	return path_coordinates;
}


bool path::is_inside_map(int *x, int *y)
{
	if ((*x >= 0 && *x <= this->sizeX - 1) && (*y >= 0 && *y <= this->sizeY - 1))
		return true;
	else
		return false;
}

