#include "PowerItem.h"

PowerItem::PowerItem(float x, float y) : AbstractItem(x, y, ImmidiateItem{Define::ITEM_POWER_TIME}) {
	_color = Define::RED;
}

void PowerItem::Initialize() {

}

void PowerItem::Finalize() {

}

void PowerItem::Effect(ItemContext& ctx) {
	ctx.ball.WaveFlag(static_cast<int>(Ball::fBall::_power), true);
}