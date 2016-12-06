#include <cstdio>
#include <mutex>
#include <Windows.h>
#include <conio.h>
#include "Io.h"

void IO::init()
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void IO::gotoXY(int x, int y)
{
	COORD pos = { (short)(2 * x), (short)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void IO::setColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void IO::print(Block &block, int cmd)
{
	for (int i = 0; i < Block::Size; ++i)
	{
		for (int j = 0; j < Block::Size; ++j)
		{
			if (Block::BlockType[block.type][i][j])
			{
				int x = block.pos.x + j;
				int y = block.pos.y + i;

				IO::print(expr[cmd], Point(x, y), block.color);
			}
		}
	}
}

void IO::print(Block &block, Point &pos, int cmd)
{
	setColor(block.color);
	for (int i = 0; i < Block::Size; ++i)
	{
		for (int j = 0; j < Block::Size; ++j)
		{
			if (Block::BlockType[block.type][i][j])
			{
				int x = pos.x + j;
				int y = pos.y + i;

				IO::print(expr[cmd], Point(x, y), block.color);
			}
		}
	}
}

void IO::print(Block &erase, Block &write)
{
	static mutex mtx;
	mtx.lock();

	print(erase, IO::ERASE);
	print(write, IO::WRITE);
	mtx.unlock();
}

void IO::print(const string &expr, Point &pos, int color)
{
	static mutex mtx;
	mtx.lock();

	setColor(color);
	gotoXY(pos.x, pos.y);
	printf("%s", expr.data());
	mtx.unlock();
}

bool IO::key(int &x, int &y, int &r)
{
	unsigned char KeyNum;
	static const char left = 75, right = 77, down = 80, up = 72;

	if (_kbhit() == 0)
		return false;
	KeyNum = _getch();
	if (KeyNum == 0 || KeyNum == 0xe0)
	{
		KeyNum = _getch();
		if (KeyNum == left)
			--x;
		else if (KeyNum == right)
			++x;
		else if (KeyNum == down)
			++y;
		else if (KeyNum == up)
			r = 1;
	}
	return true;
}

const char IO::expr[3][3] = { "  ", "бс", "бр" };