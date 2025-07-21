#pragma once
#include "RectangleObject.h"
#include "ItemVariant.h"
#include "ItemContext.h"

class AbstractItem : public RectangleObject {
public:
	virtual ~AbstractItem() = default;
	AbstractItem(float x, float y, const ItemDataVariant& type);
	//ƒˆ‰¼‘zŠÖ”ŒQ
	void Initialize() override = 0;
	void Finalize() override = 0;
	void Update() override;
	void Draw() const override;

	virtual void Effect(ItemContext& ctx) = 0;
	virtual void SetVelocity(const Vector2<float>& playerPosition) {};


	ItemDataVariant GetterVariant() const { return _type; };


protected:
	ItemDataVariant _type;
};