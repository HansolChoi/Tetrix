#pragma once
#include <iostream>
using namespace std;

class Point
{
public:
	int x, y;
	Point() : x(0), y(0) {}
	Point(int _x, int _y) : x(_x), y(_y) {}
	Point operator+(const Point &ref)
	{
		Point pos(x + ref.x, y + ref.y);
		return pos;
	}
};
