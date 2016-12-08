#pragma once
#include <iostream>
#include "Point.h"

using namespace std;

class AddX
{
private:
	int var;
public:
	explicit AddX(int x = 0) : var(x) {}
	static AddX Zero() { return AddX(0); }
	static AddX Plus() { return AddX(1); }
	static AddX Minus() { return AddX(-1); }
	int getAddX() const { return var; }
};

class AddY
{
private:
	int var;
public:
	explicit AddY(int y = 0) : var(y) {}
	static AddY Zero() { return AddY(0); }
	static AddY Plus() { return AddY(1); }
	static AddY Minus() { return AddY(-1); }
	int getAddY() const { return var; }
};

class AddR
{
private:
	bool var;
public:
	explicit AddR(bool r = false) : var(r) {}
	static AddR RoY() { return AddR(true); }
	static AddR RoN() { return AddR(false); }
	bool getAddR() const { return var; }
};

class Block
{
public:
	static const int nBaseType = 4, nChangeType = 5;
	static const int Size = 3, nType = nBaseType + nChangeType, nColor = 15;
	static const int BlockType[nType][Size][Size];
	static const int NextBlock[nType];
	enum{Black, Blue, Green, Jade, Red, ReddishPurple, Yellow, 
		White, Gray, SoftBlue, SoftGreen, SoftJade, SoftRed, 
		SoftReddishPurple, SoftYellow, DeepWhite};
	int type, color;
	Point pos;

	bool addMove(const AddX &x, const AddY &y, const AddR &r);
	Block& operator=(const Block &ref);
};