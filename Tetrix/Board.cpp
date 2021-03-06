#include <random>
#include <chrono>
#include "Board.h"

Board::Board() : ClearBonus(WIDTH * 5)
{
	for (int i = 0; i <= HEIGHT + 1; ++i)
	{
		lineCount[i] = 0;
		data[i][0] = data[i][WIDTH + 1] = GUARD;
	}

	for (int i = 1; i <= WIDTH; ++i)
	{
		data[0][i] = TOP;
		data[HEIGHT + 1][i] = BOTTOM;
	}

	for (int row = 1; row <= HEIGHT; ++row)
	{
		for (int col = 1; col <= WIDTH; ++col)
			data[row][col] = EMPTY;
	}
	live = true;
	score = nTotalBlock = 0;
	for (int i = 0; i < Info::getNblock(); ++i)
		qBlock.push(bkInit());
}

void Board::printBoard()
{
	for (int i = 0; i <= HEIGHT + 1; ++i)
	{
		IO::print("■", Point(0, i), Color::White());
		IO::print("■", Point(WIDTH + 1, i), Color::White());
	}

	for (int i = 1; i <= WIDTH; ++i)
	{
		IO::print("■", Point(i, 0), Color::White());
		IO::print("■", Point(i, HEIGHT + 1), Color::White());
	}
}

Block Board::bkInit()
{
	Block NewBlock;

	NewBlock.setPos(Point(WIDTH / 2, 1));
	NewBlock.setType(getRandom(0, Block::nBaseType - 1));
	NewBlock.setColor(Color(getRandom(1, Block::nColor)));

	return NewBlock;
}

Block Board::giveBlock()
{
	qBlock.push(bkInit());
	Block newBlock = qBlock.front();
	qBlock.pop();

	return newBlock;
}

Block Board::predictBlock(const Block &CurBlock)
{
	Block predict = CurBlock;
	do {
		predict.addMove(AddX::Zero(), AddY::Plus(), AddR::RoN());
	} while (coll(predict) == COLL_NO);
	predict.addMove(AddX::Zero(), AddY::Minus(), AddR::RoN());
	return predict;
}

void Board::chkLive(const Block &block) 
{
	for (int i = 0; i < Block::Size; ++i)
	{
		for (int j = 0; j < Block::Size; ++j)
		{
			int x = block.getPos().getX() + j;
			int y = block.getPos().getY() + i;
			if (Block::BlockType[i][j] && data[y][x])
			{
				live = false;
				return;
			}
		}
	}
}

void Board::insert(const Block &block)
{
	for (int h = 0; h < Block::Size; ++h)
	{
		for (int w = 0; w < Block::Size; ++w)
		{
			if (Block::BlockType[block.getType()][h][w])
			{
				int x = block.getPos().getX() + w;
				int y = block.getPos().getY() + h;

				data[y][x] = block.getColor().getColorNum();
				++lineCount[y];
				++nTotalBlock;
			}
		}
	}
}

int Board::coll(const Block &block)
{
	for (int i = 0; i < Block::Size; ++i)
	{
		for (int j = 0; j < Block::Size; ++j)
		{
			int x = block.getPos().getX() + j;
			int y = block.getPos().getY() + i;

			if (Block::BlockType[block.getType()][i][j] && data[y][x])
				return COLL_OBJ;
		}
	}
	return COLL_NO;
}

bool Board::lineClear(const Block &block)
{
	// 꽉찬 줄 삭제
	bool IsClear = false;
	for (int BlockOffset = 1; BlockOffset <= Block::Size; ++BlockOffset)
	{
		int y = block.getPos().getY() + Block::Size - BlockOffset;
		if (y > HEIGHT) continue;

		if (lineCount[y] == WIDTH)
		{
			lineCount[y] = 0;
			nTotalBlock -= WIDTH;
			score += WIDTH;
			if (nTotalBlock == 0)
			{
				score += ClearBonus;
				IsClear = true;
			}

			for (int x = 1; x <= WIDTH; ++x)
			{
				data[y][x] = EMPTY;
				IO::print("  ", Point(x, y), Color::Black());
			}
		}
	}

	// 지워진 줄, 아래로 내리기
	for (int BlockOffset = 1; BlockOffset <= Block::Size; ++BlockOffset)
	{
		int y = block.getPos().getY() + Block::Size - BlockOffset;
		if (y > HEIGHT) continue;

		for (int i = 0; i < Block::Size; ++i)
		{
			if (lineCount[y] == 0)
				DownLine(y);
		}
	}
	return IsClear;
}

void Board::DownLine(int y)
{
	for (int h = y; h > 1; --h)
	{
		lineCount[h] = lineCount[h - 1];
		lineCount[h - 1] = 0;
		for (int w = 1; w <= WIDTH; ++w)
		{
			data[h][w] = data[h - 1][w];
			data[h - 1][w] = EMPTY;
			if (data[h][w])
				IO::print("■", Point(w, h), Color(data[h][w]));
			else
				IO::print("  ", Point(w, h), Color(data[h][w]));
		}
	}
}

const int Board::getRandom(const int min, const int max) const
{
	static random_device rn;
	static mt19937_64 rnd(rn());

	uniform_int_distribution<int> range(min, max);

	return range(rnd);
}