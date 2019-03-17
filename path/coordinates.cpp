#include "coordinates.h"

coordinates::coordinates():x(0),y(0) {
}

coordinates::coordinates(unsigned int x, unsigned int y) : x(x), y(y) {
}


unsigned int coordinates::get_x() {
	return this->x;
}

unsigned int coordinates::get_y() {
	return this->y;
}

bool coordinates::operator==(const coordinates &A) {
	if (x == A.x && y == A.y)
		return true;
	else
		return false;
}

coordinates::coordinates(const coordinates &A) {
	this->x = A.x;
	this->y = A.y;
}

void coordinates::set_coordinates(unsigned int x, unsigned int y) {
	this->x = x;
	this->y = y;
}