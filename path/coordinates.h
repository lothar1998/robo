#pragma once

using namespace std;

class coordinates {
public:
	coordinates();
	coordinates(unsigned int, unsigned int);
	coordinates(const coordinates&);
	bool operator==(const coordinates&);
	unsigned int get_x();
	unsigned int get_y();
	void set_coordinates(unsigned int, unsigned int);

private:
	unsigned int x, y;
};