#include "CircleObject.h"
#include "DxLib.h"
#include "Define.h"

CircleObject::CircleObject(float x, float y, int r) :ShapeObject::ShapeObject(x, y), _r(r) {

}

void CircleObject::Draw() const {
	DrawCircle(_position.GetterX(), _position.GetterY(), _r, _color);
}