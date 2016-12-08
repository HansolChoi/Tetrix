#include <mutex>
#include "Block.h"

bool Block::addMove(const AddX &x, const AddY &y, const AddR &r)
{
	pos.x += x.getAddX();
	pos.y += y.getAddY();
	if(r.getAddR())
		type = NextBlock[type];
	return true;
}

Block& Block::operator=(const Block &ref)
{	
	static mutex mtx;
	mtx.lock();
	type = ref.type;
	color = ref.color;
	pos = ref.pos;
	mtx.unlock();
	return *this;
}

// 0번 Block은 Block제거 기능을 갖고 있음. 순서변경 금지.
const int Block::BlockType[Block::nType][Block::Size][Block::Size] = {
	{ { 1, 1, 1 },{ 1, 1, 1 },{ 1, 1, 1 } }, // 0
	{ { 1, 1, 1 },{ 0, 0, 1 },{ 0, 0, 1 } }, // 1
	{ { 1, 1, 1 },{ 0, 0, 0 },{ 0, 0, 0 } }, // 2
	{ { 1, 1, 0 },{ 0, 1, 0 },{ 0, 1, 1 } }, // 3
	{ { 0, 0, 1 },{ 0, 0, 1 },{ 1, 1, 1 } }, // 4
	{ { 1, 0, 0 },{ 1, 0, 0 },{ 1, 1, 1 } }, // 5
	{ { 1, 1, 1 },{ 1, 0, 0 },{ 1, 0, 0 } }, // 6
	{ { 1, 0, 0 },{ 1, 0, 0 },{ 1, 0, 0 } }, // 7
	{ { 0, 0, 1 },{ 0, 1, 1 },{ 0, 1, 0 } }  // 8
};

const int Block::NextBlock[Block::nType] =
	{ 0, 4, 7, 8, 5, 6, 1, 2, 3};
//idx 0, 1, 2, 3, 4, 5, 6, 7, 8