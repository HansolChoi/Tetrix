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

void IO::setCursor(const Point &pos)
{
	COORD _pos = { (short)(2 * pos.x), (short)pos.y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), _pos);
}

void IO::getCursor(Point &pos)
{
	CONSOLE_SCREEN_BUFFER_INFO cs;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cs);
	pos.x = (int)cs.dwCursorPosition.X;
	pos.y = (int)cs.dwCursorPosition.Y;
}

void IO::setColor(const int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void IO::clear()
{
	system("cls");
}

void IO::print(const Block &block, const int cmd)
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

void IO::print(const Block &block, const Point &pos, const int cmd)
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

void IO::print(const Block &erase, const Block &write)
{
	static mutex mtx;
	mtx.lock();

	print(erase, IO::ERASE);
	print(write, IO::WRITE);
	mtx.unlock();
}

void IO::print(const string &expr, const Point &pos, const int color)
{
	static mutex mtx;
	mtx.lock();

	setColor(color);
	setCursor(pos);
	printf("%s", expr.data());
	mtx.unlock();
}

void IO::print(const string &expr)
{
	cout << expr;
}

bool IO::key(AddX &x, AddY &y, AddR &r)
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
			x = AddX::Minus();
		else if (KeyNum == right)
			x = AddX::Plus();
		else if (KeyNum == down)
			y = AddY::Plus();
		else if (KeyNum == up)
			r = AddR::RoY();
	}
	return true;
}

const char IO::expr[3][3] = { "  ", "бс", "бр" };