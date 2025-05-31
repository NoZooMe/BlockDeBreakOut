#pragma once
#include "AbstractItem.h"
class BombItem :
    public AbstractItem
{
public:
    ~BombItem() = default;
    BombItem(float x, float y);
    void Initialize() override;
    void Finalize() override;

    void Effect(ItemContext& ctx) override;
};

