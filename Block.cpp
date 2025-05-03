#include "Block.h"
#include "DxLib.h"

Block::Block(float x, float y, float width, float height, int col):RectangleObject(x, y, width, height), color(col) {

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
		DrawBox(_position.GetterX(), _position.GetterY(), _position.GetterX() + width, _position.GetterY() + height, color, true);
	}
}

void Block::SetBlockFlag_Live(bool value) {
	WaveFlag((int)fBlock::_live, value);
}