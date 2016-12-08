#pragma once
#include <iostream>
#include <queue>
#include "Block.h"
#include "Io.h"
#include "Info.h"
#include "Color.h"
using namespace std;

class Board
{
public:
	enum { WIDTH = 9, HEIGHT = 30 };
	enum { BOTTOM = -3, TOP = -2, GUARD = -1, EMPTY = 0 };
	enum { COLL_NO, COLL_OBJ};

private:
	int data[HEIGHT + 2][WIDTH + 2];
	int lineCount[HEIGHT + 2];
	bool live;
	const int ClearBonus;
	int score, nTotalBlock;
	queue<Block> qBlock;

public:
	Board();
	void printBoard();
	Block bkInit();
	Block giveBlock();
	Block predictBlock(const Block &CurBlock);
	void chkLive(const Block &block);
	void insert(const Block &block);
	int coll(const Block &block);
	bool lineClear(const Block &block);
	void DownLine(int y);

	const int getRandom(const int min, const int max) const;
	const int getLive() const { return live; }
	const int getScore() const { return score; }
	queue<Block>* getQueueBlock() { return &qBlock; }
};