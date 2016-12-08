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
	COORD _pos = { (short)(2 * pos.getX()), (short)pos.getY() };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), _pos);
}

void IO::getCursor(Point &pos)
{
	CONSOLE_SCREEN_BUFFER_INFO cs;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cs);
	pos.setX((int)cs.dwCursorPosition.X);
	pos.setY((int)cs.dwCursorPosition.Y);
}

void IO::setColor(const Color &color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color.getColorNum());
}

void IO::clear()
{
	system("cls");
}

void IO::print(const Block &block, const CMD &cmd)
{
	for (int i = 0; i < Block::Size; ++i)
	{
		for (int j = 0; j < Block::Size; ++j)
		{
			if (Block::BlockType[block.getType()][i][j])
			{
				int x = block.getPos().getX() + j;
				int y = block.getPos().getY() + i;

				IO::print(expr[cmd.getCmd()], Point(x, y), block.getColor());
			}
		}
	}
}

void IO::print(const Block &block, const Point &pos, const CMD &cmd)
{
	setColor(block.getColor());
	for (int i = 0; i < Block::Size; ++i)
	{
		for (int j = 0; j < Block::Size; ++j)
		{
			if (Block::BlockType[block.getType()][i][j])
			{
				int x = pos.getX() + j;
				int y = pos.getY() + i;

				IO::print(expr[cmd.getCmd()], Point(x, y), block.getColor());
			}
		}
	}
}

void IO::print(const Block &erase, const Block &write)
{
	static mutex mtx;
	mtx.lock();

	print(erase, CMD::Erase());
	print(write, CMD::Write());
	mtx.unlock();
}

void IO::print(const string &expr, const Point &pos, const Color &color)
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