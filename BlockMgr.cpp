#include "BlockMgr.h"
#include "Def.h"

using namespace std;

BlockMgr::BlockMgr() {
	for (int i = 0; i < NUM; i++) {
		_vector.emplace_back(make_shared<Block>(i%BLOCK_ROW*(BLOCK_WIDTH + BLOCK_GAPX) + BLOCK_GAPX, i/BLOCK_ROW*(BLOCK_HEIGHT + BLOCK_GAPY) + BLOCK_GAPY, BLOCK_WIDTH, BLOCK_HEIGHT, RED));
	}

	
}

void BlockMgr::Init() {
	for (auto block : _vector) {
		block->Init();
	}
}

void BlockMgr::Fin() {
	for (auto block : _vector) {
		block->Fin();
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