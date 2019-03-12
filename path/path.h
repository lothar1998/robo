#pragma once
#include "path_base.h"
class path : public path_base
{
public:
	path();
	path(int, int, int**,unsigned int);
	~path();

	vector<coordinates> find_path(coordinates,coordinates);

private:
	unsigned int forbidden_val;
	coordinates draw_nearby_coordinate(unsigned int, unsigned int);
	bool is_exist(int,int);
};

