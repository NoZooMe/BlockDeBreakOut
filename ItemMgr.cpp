#include "ItemMgr.h"
#include "Macro.h"

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
		item->Update();
	}
	CheckOut();
}

void ItemMgr::Draw() const {
	for (auto item : _itemArray) {
		item->Draw();
	}
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
		_itemArray.erase(_itemArray.begin() + num);
	}
}

void ItemMgr::CheckOut() {
	for (auto it = _itemArray.begin(); it != _itemArray.end();) {
		if (it->get()->GetterPosition().GetterX() + Define::PLAYER_WIDTH / 2 < 0 || it->get()->GetterPosition().GetterX() - it->get()->GetterWidth() / 2 > Define::SCREEN_WIDTH
			|| it->get()->GetterPosition().GetterY() - it->get()->GetterHeight() / 2 > Define::SCREEN_HEIGHT) {
			//消去するならイテレーターが便利。
			it = _itemArray.erase(it);		//erase(it)は次のイテレーターを返すのでここでは加算しない。
		}
		else {
			++it;
		}
	}
}