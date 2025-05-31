#include "ScoreItem.h"

ScoreItem::ScoreItem(float x, float y) : AbstractItem(x, y, StackableItem{}) {
	_color = Define::BLUE;
}

void ScoreItem::Initialize() {

}

void ScoreItem::Finalize() {

}

void ScoreItem::Effect(ItemContext& ctx) {
	ctx.player.AddScore(10);
}