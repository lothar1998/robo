#pragma once
class coordinates
{
public:
	coordinates();
	coordinates(unsigned int, unsigned int);
	~coordinates();

	unsigned int get_x();
	unsigned int get_y();

private:
	unsigned int x, y;
};

