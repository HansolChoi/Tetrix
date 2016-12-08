#pragma once
#include <iostream>
#include <string>
#include "Block.h"
#include "Point.h"
using namespace std;

class IO
{
public:
	enum {ERASE, WRITE, PREDICT};
	enum {
		Black, Blue, Green, Jade, Red, ReddishPurple, Yellow,
		White, Gray, SoftBlue, SoftGreen, SoftJade, SoftRed,
		SoftReddishPurple, SoftYellow, DeepWhite
	};
	static const char expr[3][3];

	static void init();
	static void setCursor(const Point &pos);
	static void getCursor(Point &pos);
	static void setColor(const int color);
	static void clear();
	static void print(const Block &block, const int cmd);
	static void print(const Block &block, const Point &pos, const int cmd);
	static void print(const Block &erase, const Block &write);
	static void print(const string &expr, const Point &pos, const int color);
	static void print(const string &expr);
	static bool key(AddX &x, AddY &y, AddR &r);
};