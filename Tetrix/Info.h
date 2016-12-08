#pragma once
#include <iostream>
#include <queue>
#include "Point.h"
#include "Io.h"
#include "Block.h"

using namespace std;

class Info
{
private:
	static const int nBlockShow = 3;
	Point BaseCoor;
	Point BlockCoor;
	Point ScoreCoor;
	Block EraseBlock;

public:
	Info(Point Base);
	void printInfo(queue<Block> *qBlock);
	void infoBlock(queue<Block> *qBlock);
	void infoScore(int score);

	inline static const int getNblock() { return nBlockShow; }
};