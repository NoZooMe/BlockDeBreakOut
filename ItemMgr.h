#pragma once
#include "AbstractItem.h"
#include <vector>
#include <memory>
enum eItemName;
template<typename T> class Vector2;

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

	//�z�����Item�̐���Ԃ�
	int GetArrayNum();
	//num�Ԃ�Item�ɃA�N�Z�X
	AbstractItem* GetterItem(int num);
	//num�Ԃ�Item�̃G�t�F�N�g���R�[������Item������
	void CallEffect(int num, ItemContext& ctx);

private:
	void CheckOut();
	std::vector<std::shared_ptr<AbstractItem>> _itemArray;
	Vector2<float> _playerPosition;
	std::vector<int> _eraseQueue;	//�폜�\��̃C���f�b�N�X

};

