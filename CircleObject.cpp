#include "CircleObject.h"
#include "DxLib.h"
#include "Def.h"

CircleObject::CircleObject(float x, float y, int r) :ShapeObject::ShapeObject(x, y), r(r) {

}

void CircleObject::Draw() const {
	DrawCircle(position.GetterX(), position.GetterY(), r, WHITE);
}