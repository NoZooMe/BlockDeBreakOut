#include "ItemMgr.h"
#include "Macro.h"
#include "BombItem.h"
#include "PowerItem.h"
#include "ScoreItem.h"
#include "ScoreItemToPlayer.h"
#include "eItemName.h"
#include <algorithm>

ItemMgr::ItemMgr() : _playerPosition(0, 0) , _cnt(0){

}

void ItemMgr::Initialize() {
	for (auto item : _itemArray) {
		item->Initialize();
	}
}

void ItemMgr::Finalize() {
	for (auto item : _itemArray) {
		item->Finalize();
	}
}

void ItemMgr::Update() {
	for (auto item : _itemArray) {
		if (!item) continue;	// nullptr防止
		item->SetVelocity(_playerPosition);
		item->Update();
	}
	CheckOut();

	for (const auto& target : _eraseQueue) {
		auto it = std::find(_itemArray.begin(), _itemArray.end(), target);
		if (it != _itemArray.end()) {
			_itemArray.erase(it);
		}
	}
	_eraseQueue.clear();
}

void ItemMgr::Draw() const {
	for (auto item : _itemArray) {
		item->Draw();
	}
	//DrawFormatString(200, 200, Define::WHITE, "%d", _cnt);
}

void ItemMgr::Generate(const eItemName& name, float x, float y) {
	switch (name) {
	case Bomb:
		_itemArray.emplace_back(std::make_shared<BombItem>(x, y));
		break;
	case PowerUp:
		_itemArray.emplace_back(std::make_shared<PowerItem>(x, y));
		break;
	case Score:
		_itemArray.emplace_back(std::make_shared<ScoreItem>(x, y));
		break;
	case ScoreToPlayer:
		_itemArray.emplace_back(std::make_shared <ScoreItemToPlayer>(x, y));
		break;
	default:	//ここエラー処理いれる。
		ERR("存在しないItemNameです");
		break;
	}
}

int ItemMgr::GetArrayNum() {
	return _itemArray.size();
}

AbstractItem* ItemMgr::GetterItem(int num) {
	return _itemArray[num].get();
}

void ItemMgr::CallEffect(int num, ItemContext& ctx) {
	if (num >= 0 && num < _itemArray.size()) {
		_itemArray[num]->Effect(ctx);
		//ポインタを直接追加する。
		_eraseQueue.push_back(_itemArray[num]);
	}
}

void ItemMgr::CheckOut() {
	for (auto it = _itemArray.begin(); it != _itemArray.end();) {
		if (it->get()->GetterPosition().GetterX() + it->get()->GetterWidth() / 2 < 0 || it->get()->GetterPosition().GetterX() - it->get()->GetterWidth() / 2 > Define::SCREEN_WIDTH
			|| it->get()->GetterPosition().GetterY() - it->get()->GetterHeight() / 2 > Define::SCREEN_HEIGHT) {
			//消去するならイテレーターが便利。
			it = _itemArray.erase(it);		//erase(it)は次のイテレーターを返すのでここでは加算しない。
			_cnt++;
		}
		else {
			++it;
		}
	}
}

void ItemMgr::SetPlayerPosition(const Vector2<float>& playerPosition) {
	_playerPosition = playerPosition;
}