#include "coordinates.h"



coordinates::coordinates():x(0),y(0)
{
}

coordinates::coordinates(unsigned int x, unsigned int y) : x(x), y(y)
{
}

coordinates::~coordinates()
{
}


unsigned int coordinates::get_x()
{
	return this->x;
}

unsigned int coordinates::get_y()
{
	return this->y;
}