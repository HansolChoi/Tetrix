#include <iostream>
#include <thread>
#include "Player.h"
#include "Board.h"
#include "Block.h"
#include "Io.h"

using namespace std;

void MyPlayer(Player *pMy);
void OtherPlayer(Player *pMy);

int main()
{
	thread threads[2];
	Player my;
	IO::init();

	threads[0] = thread(MyPlayer, &my);
	threads[1] = thread(OtherPlayer, &my);

	for (auto& th : threads) th.join();

	Point pos(0, Board::HEIGHT + 2);
	IO::print("The game has ended.\n", pos, Block::White);

	return 0;
}

void MyPlayer(Player *pMy)
{
	Board &board = pMy->board;
	Block &CurBlock = pMy->block;
	Info &info = pMy->info;

	while (board.live)
	{
		CurBlock = board.takeBlock();
		info.renewBlock(&board.qBlock);
		board.chkLive(CurBlock);
		Block AutoPreBlock = CurBlock;
		Block Predict = CurBlock;

		do {
			IO::print(Predict, IO::ERASE);
			Predict = board.predictBlock(CurBlock);
			IO::print(Predict, IO::PREDICT);

			IO::print(AutoPreBlock, CurBlock);
			for (int TCount = 0; TCount < 10; ++TCount)
			{
				this_thread::sleep_for(10ms);
				int x = 0, y = 0, r = 0;
				if (IO::key(x, y, r) == false)
					continue;

				Block CtlBlock = CurBlock;
				CtlBlock.addMove(x, y, r);
				if (board.coll(CtlBlock) == Board::COLL_NO)
				{
					IO::print(Predict, IO::ERASE);
					Predict = board.predictBlock(CtlBlock);
					IO::print(Predict, IO::PREDICT);

					IO::print(CurBlock, CtlBlock);
					CurBlock = CtlBlock;
				}
			}
			AutoPreBlock = CurBlock;
			CurBlock.addMove(0, 1, 0);
		}while (board.coll(CurBlock) == Board::COLL_NO);

		CurBlock = AutoPreBlock;
		board.insert(CurBlock);
		board.lineClear(CurBlock);
		info.renewScore(board.score);
	}
}

void OtherPlayer(Player *pMy)
{
	Board &MyBoard = pMy->board;

	while (MyBoard.live)
	{

	}
}