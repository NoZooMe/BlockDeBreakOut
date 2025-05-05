#include "BlockMgr.h"
#include "Define.h"

using namespace std;

const int BlockMgr::NUM = Define::BLOCK_NUM;

BlockMgr::BlockMgr() {
	for (int i = 0; i < NUM; i++) {
		_vector.emplace_back(make_shared<Block>(i%Define::BLOCK_ROW*(Define::BLOCK_WIDTH + Define::BLOCK_GAPX)+(i%Define::BLOCK_ROW + 1)*Define::BLOCK_GAPX, 
			i/Define::BLOCK_ROW*(Define::BLOCK_HEIGHT + Define::BLOCK_GAPY) + Define::BLOCK_GAPY, 
			Define::BLOCK_WIDTH, Define::BLOCK_HEIGHT, Define::RED));
	}
}

void BlockMgr::Initialize() {
	for (auto block : _vector) {
		block->Initialize();
	}
}

void BlockMgr::Finalize() {
	for (auto block : _vector) {
		block->Finalize();
	}
}

void BlockMgr::Update() {
	for (auto block : _vector) {
		block->Update();
	}
}

void BlockMgr::Draw() const {
	for (auto block : _vector) {
		block->Draw();
	}
}

shared_ptr<RectangleObject> BlockMgr::Getter_LiveBlock(int num) const {
	if (_vector[num]->CheckFlag((int)Block::fBlock::_live)) {
		return _vector[num];
	}
	else {
		return nullptr;
	}
}

void BlockMgr::SetBlockFlag_Live(int num, bool value) {
	_vector[num]->SetBlockFlag_Live(value);
}

int BlockMgr::Getter_LiveNum() const {
	int numLive = 0;
	for (auto block : _vector) {
		if (block->CheckFlag((int)Block::fBlock::_live)) {
			numLive++;
		}
	}
	return numLive++;
}