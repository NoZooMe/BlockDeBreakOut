#pragma once
#include "ScoreItem.h"
class ScoreItemToPlayer :
    public ScoreItem
{
public:
    ~ScoreItemToPlayer() = default;
    ScoreItemToPlayer(float x, float y);

    void Update() override;

    void SetVelocity(const Vector2<float>& playerPosition) override;

private:
    int _cnt;
    Vector2<float> _toVelocity;
};

