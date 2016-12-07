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
	static void setCursor(int x, int y);
	static void getCursor(Point &pos);
	static void setColor(int color);
	static void clear();
	static void print(Block &block, int cmd);
	static void print(Block &block, Point &pos, int cmd);
	static void print(Block &erase, Block &write);
	static void print(const string &expr, Point &pos, int color);
	static void print(const string &expr);
	static bool key(AddX &x, AddY &y, AddR &r);
};