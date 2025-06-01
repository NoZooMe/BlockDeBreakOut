#pragma once
#include "Player.h"
#include "AbstractItem.h"
#include "eItemName.h"
#include "BombItem.h"
#include "PowerItem.h"
#include "ScoreItem.h"
#include "ScoreItemToPlayer.h"
#include <vector>
#include <memory>

class ItemMgr
{
public:
	ItemMgr();
	void Initialize();
	void Finalize();
	void Update();
	void Draw() const;

	void Generate(const eItemName& name, float x, float y);

	void SetPlayerPosition(const Vector2<float>& position);

	//配列内のItemの数を返す
	int GetArrayNum();
	//num番のItemにアクセス
	AbstractItem* GetterItem(int num);
	//num番のItemのエフェクトをコールしてItemを消去
	void CallEffect(int num, ItemContext& ctx);

private:
	void CheckOut();
	std::vector<std::shared_ptr<AbstractItem>> _itemArray;
	Vector2<float> _playerPosition;
	std::vector<int> _eraseQueue;	//削除予定のインデックス

};

