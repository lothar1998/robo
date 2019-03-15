#pragma once
#include "path_base.h"

class path : public path_base
{
public:
	path(int, int, int**,unsigned int);
	vector<coordinates> find_optimal_path(coordinates,coordinates) override;
private:
	vector<coordinates>* find_path(coordinates*, coordinates*,vector<coordinates>*);
	unsigned int forbidden_val;
	bool is_inside_map(unsigned int*, unsigned int*);
	short int directions[8][2];
};

