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

	virtual void Effect(ItemContext& ctx) = 0;

	//Šî’êƒNƒ‰ƒX‚ÌŠÖ”‚ğoverride
	void Update() override;
	void Draw() const override;

	ItemDataVariant GetterVariant() const { return _type; };


protected:
	ItemDataVariant _type;
};