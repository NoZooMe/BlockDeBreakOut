#include "Block.h"
#include "DxLib.h"

Block::Block(float x, float y, float width, float height, int col):RectangleObject(x, y, width, height), color(col) {

}

void Block::Initialize() {
	//�������Ԃɂ���
	WaveFlag((int)fBlock::_live, true);
}

void Block::Finalize() {

}

void Block::Update() {

}

void Block::Draw() const {
	if (CheckFlag((int)fBlock::_live)) {
		RectangleObject::Draw();
	}
}

void Block::SetBlockFlag_Live(bool value) {
	WaveFlag((int)fBlock::_live, value);
}