#include "coordinates.h"

coordinates::coordinates():x(0),y(0) {
}

coordinates::coordinates(const unsigned int x,const unsigned int y) : x(x), y(y) {
}


unsigned int coordinates::get_x() {
	return this->x;
}

unsigned int coordinates::get_y() {
	return this->y;
}

bool coordinates::operator==(const coordinates &A) const {
	if (x == A.x && y == A.y)
		return true;
	else
		return false;
}


void coordinates::set_coordinates(const unsigned int x,const unsigned int y) {
	this->x = x;
	this->y = y;
}