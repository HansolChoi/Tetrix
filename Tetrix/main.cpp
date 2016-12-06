#include <iostream>
#include <thread>
#include "Player.h"
#include "Board.h"
#include "Block.h"
#include "Io.h"

using namespace std;

void MyPlayer(Player *my);
void OtherPlayer(Player *my);

int main()
{
	thread threads[2];
	Player my;
	IO::init();

	threads[0] = thread(MyPlayer, &my);
	threads[1] = thread(OtherPlayer, &my);

	for (auto& th : threads) th.join();

	Point pos(0, Board::HEIGHT + 2);
	IO::print("게임이 종료되었습니다.\n", pos, Block::White);

	return 0;
}

void MyPlayer(Player *my)
{
	Board &board = my->board;
	Block &CurBlock = my->block;
	Info &info = my->info;

	while (board.live)
	{
		CurBlock = board.takeBlock();
		info.renewBlock(&board.qBlock);
		board.chkLive(CurBlock);
		Block AutoPreBlock = CurBlock;
		Block Predict = CurBlock, PrePredic;

		do {
			PrePredic = Predict;
			Predict = board.predictBlock(CurBlock);
			IO::print(PrePredic, IO::ERASE);
			IO::print(Predict, IO::PREDICT);

			IO::print(AutoPreBlock, CurBlock);
			for (int TCount = 0; TCount < 10; ++TCount)
			{
				this_thread::sleep_for(10ms);
				int x = 0, y = 0, r = 0;
				if (IO::key(x, y, r) == false)
					continue;
				if (r == 1)
				{
					// 도형 회전 코드
					Block RotPreBlock = CurBlock;
					CurBlock.rotation();
					if (board.coll(CurBlock) == Board::COLL_NO)
					{
						PrePredic = Predict;
						Predict = board.predictBlock(CurBlock);
						IO::print(PrePredic, IO::ERASE);
						IO::print(Predict, IO::PREDICT);

						IO::print(RotPreBlock, CurBlock);
					}
					else
						CurBlock = RotPreBlock;
					continue;
				}
				Block CtlPreBlock = CurBlock;
				CurBlock.addMove(x, y);
				if (board.coll(CurBlock) == Board::COLL_NO)
				{
					PrePredic = Predict;
					Predict = board.predictBlock(CurBlock);
					IO::print(PrePredic, IO::ERASE);
					IO::print(Predict, IO::PREDICT);

					IO::print(CtlPreBlock, CurBlock);
				}
				else
					CurBlock = CtlPreBlock;
			}
			AutoPreBlock = CurBlock;
			CurBlock.addMove(0, 1);
		}while (board.coll(CurBlock) == Board::COLL_NO);

		CurBlock = AutoPreBlock;
		board.insert(CurBlock);
		board.lineClear(CurBlock);
		info.renewScore(board.score);
	}
}

void OtherPlayer(Player *my)
{
	Board &MyBoard = my->board;

	while (MyBoard.live)
	{

	}
}