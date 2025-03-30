#include "Block.h"
#include "DxLib.h"

Block::Block(float x, float y, float width, float height, int col):RectangleObject(x, y, width, height), color(col) {

}

void Block::Init() {
	//å©Ç¶ÇÈèÛë‘Ç…Ç∑ÇÈ
	WaveFlag((int)fBlock::_live, true);
}

void Block::Fin() {

}

void Block::Update() {

}

void Block::Draw() const {
	if (CheckFlag((int)fBlock::_live)) {
		DrawBox(position.GetterX(), position.GetterY(), position.GetterX() + width, position.GetterY() + height, color, true);
	}
}

void Block::SetBlockFlag_Live(bool value) {
	WaveFlag((int)fBlock::_live, value);
}