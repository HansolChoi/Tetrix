#include <mutex>
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
	for (int i = 0; i < Info::nBlockShow; ++i)
		qBlock.push(bkInit());
}

void Board::printBoard()
{
	for (int i = 0; i <= HEIGHT + 1; ++i)
	{
		IO::print("■", Point(0, i), Block::White);
		IO::print("■", Point(WIDTH + 1, i), Block::White);
	}

	for (int i = 1; i <= WIDTH; ++i)
	{
		IO::print("■", Point(i, 0), Block::White);
		IO::print("■", Point(i, HEIGHT + 1), Block::White);
	}
}

Block Board::bkInit()
{
	Block NewBlock;

	NewBlock.pos = Point(WIDTH / 2, 1);
	NewBlock.type = getRandom(0, Block::nBaseType - 1);
	NewBlock.color = getRandom(1, Block::nColor);

	return NewBlock;
}

Block Board::giveBlock()
{
	qBlock.push(bkInit());
	Block newBlock = qBlock.front();
	qBlock.pop();

	return newBlock;
}

Block Board::predictBlock(Block &CurBlock)
{
	Block predict = CurBlock;
	do {
		predict.addMove(0, 1, 0);
	} while (coll(predict) == COLL_NO);
	predict.addMove(0, -1, 0);
	return predict;
}

void Board::chkLive(Block &block)
{
	for (int i = 0; i < Block::Size; ++i)
	{
		for (int j = 0; j < Block::Size; ++j)
		{
			int x = block.pos.x + j;
			int y = block.pos.y + i;
			if (Block::BlockType[i][j] && data[y][x])
			{
				live = false;
				return;
			}
		}
	}
}

void Board::insert(Block block)
{
	for (int h = 0; h < Block::Size; ++h)
	{
		for (int w = 0; w < Block::Size; ++w)
		{
			if (Block::BlockType[block.type][h][w])
			{
				int x = block.pos.x + w;
				int y = block.pos.y + h;

				data[y][x] = block.color;
				++lineCount[y];
				++nTotalBlock;
			}
		}
	}
}

int Board::coll(Block &block)
{
	static mutex mtx;
	mtx.lock();
	for (int i = 0; i < Block::Size; ++i)
	{
		for (int j = 0; j < Block::Size; ++j)
		{
			int x = block.pos.x + j;
			int y = block.pos.y + i;

			if (Block::BlockType[block.type][i][j] && data[y][x])
			{
				mtx.unlock();
				return COLL_OBJ;
			}
		}
	}
	mtx.unlock();
	return COLL_NO;
}

bool Board::lineClear(Block &block)
{
	// 꽉찬 줄 삭제
	bool IsClear = false;
	for (int BlockOffset = 1; BlockOffset <= Block::Size; ++BlockOffset)
	{
		int y = block.pos.y + Block::Size - BlockOffset;
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
				IO::print("  ", Point(x, y), Block::Black);
			}
		}
	}

	// 지워진 줄, 아래로 내리기
	for (int BlockOffset = 1; BlockOffset <= Block::Size; ++BlockOffset)
	{
		int y = block.pos.y + Block::Size - BlockOffset;
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
				IO::print("■", Point(w, h), data[h][w]);
			else
				IO::print("  ", Point(w, h), data[h][w]);
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