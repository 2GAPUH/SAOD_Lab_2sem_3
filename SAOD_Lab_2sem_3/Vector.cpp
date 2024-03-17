#include "Vector.h"

Vector::Vector(const int x, const int y)
{
	this->x = x;
	this->y = y;
}

Vector Vector::operator+(const Vector& tmp)
{
	return Vector(x + tmp.x, y + tmp.y);
}

Vector Vector::operator-(const Vector& tmp)
{
	return Vector(x - tmp.x, y - tmp.y);
}

Vector Vector::operator+(const int& tmp)
{
	return Vector(x + tmp, y + tmp);
}

Vector Vector::operator-(const int& tmp)
{
	return Vector(x - tmp, y - tmp);
}
