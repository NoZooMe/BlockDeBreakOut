#include "BombItem.h"

BombItem::BombItem(float x, float y) : AbstractItem(x, y, StackableItem{}){
	_color = Define::GREEN;
}

void BombItem::Initialize() {

}

void BombItem::Finalize() {

}

void BombItem::Effect(ItemContext& ctx) {
	ctx.player.CallIncBomb();
}