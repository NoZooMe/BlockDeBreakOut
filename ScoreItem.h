#pragma once
#include "AbstractItem.h"
class ScoreItem :
    public AbstractItem
{
public:
    ~ScoreItem() = default;
    ScoreItem(float x, float y);
    void Initialize() override;
    void Finalize() override;

    void Effect(ItemContext& ctx) override;

protected:
    int _valueScore;
};

