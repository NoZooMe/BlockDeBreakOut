#include "ScoreItem.h"
#include "SoundManager.h"
#include "ResourceID.h"

ScoreItem::ScoreItem(float x, float y) : AbstractItem(x, y, StackableItem{}) , _valueScore(Define::ITEM_SCORE_VALUE){
	_color = Define::BLUE;
}

void ScoreItem::Initialize() {

}

void ScoreItem::Finalize() {

}

void ScoreItem::Effect(ItemContext& ctx) {
	ctx.player.AddScore(_valueScore);
	SoundManager::getIns()->play(toString(ResourceID::ScoreUpSE));
}