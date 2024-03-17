#pragma once


class Vector
{
public:
	int x = 0, y = 0;
	Vector(const int x, const int y);
	Vector operator +(const Vector& tmp);
	Vector operator -(const Vector& tmp);
	Vector operator +(const int& tmp);
	Vector operator -(const int& tmp);
};

