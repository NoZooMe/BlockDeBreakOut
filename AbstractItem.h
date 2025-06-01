#pragma once
#include "RectangleObject.h"
#include "ItemVariant.h"
#include "ItemContext.h"

class AbstractItem : public RectangleObject {
public:
	virtual ~AbstractItem() = default;
	AbstractItem(float x, float y, const ItemDataVariant& type);
	//純粋仮想関数群
	void Initialize() override = 0;
	void Finalize() override = 0;

	virtual void Effect(ItemContext& ctx) = 0;

	//基底クラスの関数をoverride
	void Update() override;
	void Draw() const override;

	ItemDataVariant GetterVariant() const { return _type; };

	//速度を変更したいアイテムが出てきたので仮想関数を実装
	virtual void SetVelocity(const Vector2<float>& playerPosition) {};

protected:
	ItemDataVariant _type;
};