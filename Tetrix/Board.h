#pragma once
#include <iostream>
#include <queue>
#include "Block.h"
#include "Io.h"
#include "Info.h"
using namespace std;

class Board
{
public:
	enum { WIDTH = 9, HEIGHT = 30 };
	enum { BOTTOM = -3, TOP = -2, GUARD = -1, EMPTY = 0 };
	enum { COLL_NO, COLL_OBJ};

	int data[HEIGHT + 2][WIDTH + 2];
	int lineCount[HEIGHT + 2];
	bool live;
	const int ClearBonus;
	int score, nTotalBlock;
	queue<Block> qBlock;

	Board();
	Block bkInit();
	Block takeBlock();
	Block predictBlock(Block &CurBlock);
	void chkLive(Block &block);
	void insert(Block block);
	int coll(Block &block);
	bool lineClear(Block &block);
	void DownLine(int y);

	const int getRandom(const int min, const int max) const;
};