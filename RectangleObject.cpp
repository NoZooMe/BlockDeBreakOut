#include "RectangleObject.h"
#include <DxLib.h>
#include "Define.h"

RectangleObject::RectangleObject(float x, float y, int width, int height) : ShapeObject(x, y), width(width), height(height), vertSide1(x, y, x, y+height), vertSide2(x+width, y, x+width, y+height), 
	horiSide1(x, y, x+width, y), horiSide2(x, y+height, x+width, y+height){

}

void RectangleObject::Update(){
	ShapeObject::Update();

	//Ç±Ç±ÇÁï”ÇÕÇ‡Ç§è≠Çµä»íPÇ…Ç≈Ç´Ç»Ç¢ÅH
	vertSide1.UpdateSegment(position.GetterX(), position.GetterY(), position.GetterX(), position.GetterY() + height);
	vertSide2.UpdateSegment(position.GetterX() + width, position.GetterY(), position.GetterX() + width, position.GetterY() + height);
	horiSide1.UpdateSegment(position.GetterX(), position.GetterY(), position.GetterX() + width, position.GetterY());
	horiSide2.UpdateSegment(position.GetterX(), position.GetterY() + height, position.GetterX() + width, position.GetterY() + height);

}

void RectangleObject::Draw() const {
	DrawBox(position.GetterX(), position.GetterY(), position.GetterX() + width, position.GetterY() + height, Define::WHITE, true);
}