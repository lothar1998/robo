#pragma once
#include "path_base.h"
class path : public path_base
{
public:
	path();
	path(int, int, int**,unsigned int);
	~path();
	vector<coordinates> find_optimal_path(coordinates,coordinates);
private:
	vector<coordinates>* find_path(coordinates*, coordinates*,vector<coordinates>*);
	unsigned int forbidden_val;
	bool is_inside_map(int*, int*);
	int ile;//temporary
	short int directions[8][2];
	
	
};

