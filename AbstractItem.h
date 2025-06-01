#pragma once
#include "RectangleObject.h"
#include "ItemVariant.h"
#include "ItemContext.h"

class AbstractItem : public RectangleObject {
public:
	virtual ~AbstractItem() = default;
	AbstractItem(float x, float y, const ItemDataVariant& type);
	//�������z�֐��Q
	void Initialize() override = 0;
	void Finalize() override = 0;

	virtual void Effect(ItemContext& ctx) = 0;

	//���N���X�̊֐���override
	void Update() override;
	void Draw() const override;

	ItemDataVariant GetterVariant() const { return _type; };

	//���x��ύX�������A�C�e�����o�Ă����̂ŉ��z�֐�������
	virtual void SetVelocity(const Vector2<float>& playerPosition) {};

protected:
	ItemDataVariant _type;
};