#pragma once
#include <iostream>
using namespace std;

class Point
{
private:
	int x, y;
public:
	Point() : x(0), y(0) {}
	Point(int _x, int _y) : x(_x), y(_y) {}
	Point(const Point &ref) : x(ref.x), y(ref.y) {}

	inline const int getX() const { return x; }
	inline const int getY() const { return y; }
	inline void setX(const int _x) { x = _x; }
	inline void setY(const int _y) { y = _y; }

	Point& operator=(const Point &ref)
	{
		x = ref.x;
		y = ref.y;
		return *this;
	}

	Point operator+(const Point &ref)
	{
		Point pos(x + ref.x, y + ref.y);
		return pos;
	}
};
