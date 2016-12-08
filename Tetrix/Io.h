#pragma once
#include <iostream>
#include <string>
#include "Block.h"
#include "Point.h"
#include "Color.h"
using namespace std;

class CMD
{
private:
	int cmd;
	explicit CMD(int _cmd = 0) : cmd(_cmd) {}
public:
	inline const int getCmd() const { return cmd; }
	static CMD Erase() { return CMD(0); }
	static CMD Write() { return CMD(1); }
	static CMD Predict() { return CMD(2); }
};

class IO
{
private:
	static const char expr[3][3];
public:
	static void init();
	static void setCursor(const Point &pos);
	static void getCursor(Point &pos);
	static void setColor(const Color &color);
	static void clear();
	static void print(const Block &block, const CMD &cmd);
	static void print(const Block &block, const Point &pos, const CMD &cmd);
	static void print(const Block &erase, const Block &write);
	static void print(const string &expr, const Point &pos, const Color &color);
	static void print(const string &expr);
	static bool key(AddX &x, AddY &y, AddR &r);
};