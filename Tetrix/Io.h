#pragma once
#include <iostream>
#include <string>
#include "Block.h"
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
	static void gotoXY(int x, int y);
	static void setColor(int color);
	static void print(Block &block, int cmd);
	static void print(Block &block, Point &pos, int cmd);
	static void print(const string &expr, Point &pos, int color);
	static void print(Block &erase, Block &write);
	static bool key(int &x, int &y, int &r);
};