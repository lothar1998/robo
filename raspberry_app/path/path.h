#pragma once
#include "path_base.h"
#include <random>

class path : public path_base {
public:
	path(int, int, int**,unsigned int);
	vector<coordinates> find_path(coordinates,coordinates) override;
private:
	/*---variables---*/
	std::knuth_b generator;
	short int directions[8][2];
	unsigned int forbidden_val;

	/*---methods---*/
	vector<coordinates>* draw_path(coordinates*, coordinates*,vector<coordinates>*);
	vector<coordinates> hybrid(vector<coordinates>*,vector<coordinates>*);
	bool is_inside_map(unsigned int*, unsigned int*);
	unsigned int calculate_cost(vector<coordinates> *);
	void sort_array(unsigned int *, unsigned int, unsigned int*);
	bool is_forbidden(unsigned int*, unsigned int*);
	void optimize(vector<coordinates>*);
};

