#pragma once
#include "AbstractItem.h"
class PowerItem :
    public AbstractItem
{
public:
    ~PowerItem() = default;
    PowerItem(float x, float y);
    void Initialize() override;
    void Finalize() override;

    void Effect(ItemContext& cts) override;

};

