#pragma once
#include <iostream>
#include <queue>
#include <string>
#include "Block.h"
#include "Board.h"
#include "Info.h"
#include "Io.h"
using namespace std;

class Player
{
public:
	string name;
	int GameType;
	Board board;
	Block block;
	Info  info;
	Player() :info(Point(Board::WIDTH + 3, 0)){}
	void logo() const;
	void Register();
};