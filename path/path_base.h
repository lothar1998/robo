#pragma once
#include <vector>
#include "coordinates.h"

using namespace std;

class path_base
{
public:
	path_base();
	path_base(int, int, int **);
	virtual ~path_base();

	virtual vector<coordinates> find_optimal_path(coordinates, coordinates) = 0;

protected:
	int sizeX;
	int sizeY;

	int **map;
};

