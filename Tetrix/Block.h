#pragma once
#include <iostream>
#include "Point.h"

using namespace std;

class Block
{
public:
	static const int nBaseType = 4, nChangeType = 5;
	static const int Size = 3, nType = nBaseType + nChangeType, nColor = 15;
	static const int BlockType[nType][Size][Size];
	static const int NextBlock[nType];
	enum{Black, Blue, Green, Jade, Red, ReddishPurple, Yellow, 
		White, Gray, SoftBlue, SoftGreen, SoftJade, SoftRed, 
		SoftReddishPurple, SoftYellow, DeepWhite};
	int type, color;
	Point pos;

	bool addMove(int addX, int addY, int addR);
	Block& operator=(const Block &ref);
};