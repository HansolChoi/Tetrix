#include <string>
#include "Info.h"

Info::Info(Point Base)
{
	BaseCoor = Base;
	ScoreCoor = Base + Point(1, 1);
	BlockCoor = Base + Point(1, 3);

	EraseBlock.type = 0;
	EraseBlock.color = Block::Black;
}

void Info::printInfo(queue<Block> *qBlock)
{
	IO::print("[ Score ]", BaseCoor, IO::White);
	IO::print("0", ScoreCoor, IO::White);

	IO::print("[ Next Block ]", BaseCoor + Point(0, 2), IO::White);

	infoBlock(qBlock);
}

void Info::infoBlock(queue<Block> *qBlock)
{
	for (int i = 0; i < nBlockShow; ++i)
	{
		Block ViewBlock = qBlock->front();
		qBlock->pop();

		Point pos = BlockCoor + Point(0, i * (Block::Size + 1));
		IO::print(EraseBlock, pos, IO::ERASE);
		IO::print(ViewBlock, pos, IO::WRITE);

		qBlock->push(ViewBlock);
	}
}

void Info::infoScore(int score)
{
	string sscore = to_string(score);
	IO::print(sscore, ScoreCoor, IO::White);
}