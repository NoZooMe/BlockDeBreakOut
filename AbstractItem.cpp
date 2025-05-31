#include "AbstractItem.h"

AbstractItem::AbstractItem(float x, float y, const ItemDataVariant& type) : RectangleObject(x, y, Define::ITEM_WIDTH, Define::ITEM_HEIGHT), _type(type){
	SetterVelocity(Define::ITEM_SPEED);
}

void AbstractItem::Update() {
	RectangleObject::Update();
}

void AbstractItem::Draw() const {
	RectangleObject::Draw();
}