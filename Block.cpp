#include "Block.h"
#include "DxLib.h"

Block::Block(float x, float y, float _width, float _height, int col):RectangleObject(x, y, _width, _height), color(col) {

}

void Block::Initialize() {
	//å©Ç¶ÇÈèÛë‘Ç…Ç∑ÇÈ
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