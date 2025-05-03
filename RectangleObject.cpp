#include "RectangleObject.h"
#include <DxLib.h>
#include "Define.h"

RectangleObject::RectangleObject(float x, float y, int width, int height) : ShapeObject(x, y), width(width), height(height), vertSide1(x, y, x, y+height), vertSide2(x+width, y, x+width, y+height), 
	horiSide1(x, y, x+width, y), horiSide2(x, y+height, x+width, y+height){

}

void RectangleObject::Update(){
	ShapeObject::Update();

	//Ç±Ç±ÇÁï”ÇÕÇ‡Ç§è≠Çµä»íPÇ…Ç≈Ç´Ç»Ç¢ÅH
	vertSide1.UpdateSegment(_position.GetterX(), _position.GetterY(), _position.GetterX(), _position.GetterY() + height);
	vertSide2.UpdateSegment(_position.GetterX() + width, _position.GetterY(), _position.GetterX() + width, _position.GetterY() + height);
	horiSide1.UpdateSegment(_position.GetterX(), _position.GetterY(), _position.GetterX() + width, _position.GetterY());
	horiSide2.UpdateSegment(_position.GetterX(), _position.GetterY() + height, _position.GetterX() + width, _position.GetterY() + height);

}

void RectangleObject::Draw() const {
	DrawBox(_position.GetterX(), _position.GetterY(), _position.GetterX() + width, _position.GetterY() + height, Define::WHITE, true);
}
