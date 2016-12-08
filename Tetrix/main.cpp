#include <iostream>
#include <thread>
#include "Player.h"
#include "Board.h"
#include "Block.h"
#include "Io.h"
#include "Color.h"

using namespace std;

void MyPlayer(Player *pMy);
void OtherPlayer(Player *pMy);

int main()
{
	thread threads[2];
	Player my;

	my.Register();
	my.board.printBoard();
	my.info.printInfo(&my.board.qBlock);
	IO::init();

	threads[0] = thread(MyPlayer, &my);
	threads[1] = thread(OtherPlayer, &my);

	for (auto& th : threads) th.join();

	Point pos(0, Board::HEIGHT + 2);
	IO::print("The game has ended.\n", pos, Color::White());

	return 0;
}

void MyPlayer(Player *pMy)
{
	Board &board = pMy->board;
	Block &CurBlock = pMy->block;
	Info &info = pMy->info;

	while (board.live)
	{
		CurBlock = board.giveBlock();
		info.infoBlock(&board.qBlock);
		board.chkLive(CurBlock);
		Block AutoPreBlock = CurBlock;
		Block Predict = CurBlock;

		do {
			IO::print(Predict, CMD::Erase());
			Predict = board.predictBlock(CurBlock);
			IO::print(Predict, CMD::Predict());

			IO::print(AutoPreBlock, CurBlock);
			for (int TCount = 0; TCount < 10; ++TCount)
			{
				this_thread::sleep_for(10ms);
				AddX x; AddY y; AddR r;
				if (IO::key(x, y, r) == false)
					continue;

				Block CtlBlock = CurBlock;
				CtlBlock.addMove(x, y, r);
				if (board.coll(CtlBlock) == Board::COLL_NO)
				{
					IO::print(Predict, CMD::Erase());
					Predict = board.predictBlock(CtlBlock);
					IO::print(Predict, CMD::Predict());

					IO::print(CurBlock, CtlBlock);
					CurBlock = CtlBlock;
				}
			}
			AutoPreBlock = CurBlock;
			CurBlock.addMove(AddX::Zero(), AddY::Plus(), AddR::RoN());
		}while (board.coll(CurBlock) == Board::COLL_NO);

		CurBlock = AutoPreBlock;
		board.insert(CurBlock);
		board.lineClear(CurBlock);
		info.infoScore(board.score);
	}
}

void OtherPlayer(Player *pMy)
{
	Board &MyBoard = pMy->board;

	while (MyBoard.live)
	{

	}
}