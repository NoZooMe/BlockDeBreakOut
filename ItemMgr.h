#pragma once
#include "Player.h"
#include "AbstractItem.h"
#include "eItemName.h"
#include "BombItem.h"
#include "PowerItem.h"
#include "ScoreItem.h"
#include <vector>
#include <memory>

class ItemMgr
{
public:
	void Initialize();
	void Finalize();
	void Update();
	void Draw() const;

	void Generate(const eItemName& name, float x, float y);

	//�z�����Item�̐���Ԃ�
	int GetArrayNum();
	//num�Ԃ�Item�ɃA�N�Z�X
	AbstractItem* GetterItem(int num);
	//num�Ԃ�Item�̃G�t�F�N�g���R�[������Item������
	void CallEffect(int num, ItemContext& ctx);

private:
	void CheckOut();
	std::vector<std::shared_ptr<AbstractItem>> _itemArray;

};

