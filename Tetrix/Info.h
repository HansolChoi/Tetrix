#pragma once
#include <iostream>
#include <queue>
#include "Point.h"
#include "Io.h"
#include "Block.h"

using namespace std;

class Info
{
public:
	enum { nBlockShow = 3 };
	Point BaseCoor;
	Point BlockCoor;
	Point ScoreCoor;
	Block EraseBlock;
	Info(Point Base, queue<Block> *qBlock);
	void infoBlock(queue<Block> *qBlock);
	void infoScore(int score);
};