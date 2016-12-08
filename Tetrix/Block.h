#pragma once
#include <iostream>
#include "Point.h"
#include "Color.h"

using namespace std;

class AddX
{
private:
	int var;
public:
	explicit AddX(int x = 0) : var(x) {}
	inline static AddX Zero() { return AddX(0); }
	inline static AddX Plus() { return AddX(1); }
	inline static AddX Minus() { return AddX(-1); }
	inline int getAddX() const { return var; }
};

class AddY
{
private:
	int var;
public:
	explicit AddY(int y = 0) : var(y) {}
	inline static AddY Zero() { return AddY(0); }
	inline static AddY Plus() { return AddY(1); }
	inline static AddY Minus() { return AddY(-1); }
	inline int getAddY() const { return var; }
};

class AddR
{
private:
	bool var;
public:
	explicit AddR(bool r = false) : var(r) {}
	inline static AddR RoY() { return AddR(true); }
	inline static AddR RoN() { return AddR(false); }
	inline bool getAddR() const { return var; }
};

class Block
{
private:
	int type;
	Point pos;
	Color color;

public:
	static const int nBaseType = 4, nChangeType = 5;
	static const int Size = 3, nType = nBaseType + nChangeType, nColor = 15;
	static const int BlockType[nType][Size][Size];
	static const int NextBlock[nType];
	
	Block() : type(0), pos(Point(0, 0)), color(Color::White()){}

	bool addMove(const AddX &x, const AddY &y, const AddR &r);
	Block& operator=(const Block &ref);

	inline const int getType() const { return type; }
	inline void setType(const int _type) { type = _type; }
	inline const Point& getPos() const { return pos; }
	inline void setPos(const Point &_pos) { pos = _pos; }
	inline const Color& getColor() const { return color; }
	inline void setColor(const Color & _color) { color = _color; }
};