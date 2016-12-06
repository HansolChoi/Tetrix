#pragma once
#include <iostream>
#include <queue>
#include "Block.h"
#include "Board.h"
#include "Info.h"
using namespace std;

class Player
{
public:
	Board board;
	Block block;
	Info  info;
	Player() :info(Point(Board::WIDTH + 3, 0), &board.qBlock)
	{}
};