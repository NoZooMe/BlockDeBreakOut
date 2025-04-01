#pragma once
#include "AbstractBullet.h"
class SmallBullet :
    public AbstractBullet
{
public:
    SmallBullet(const Vector2<float>& position, int speed, int color, int pattern, const Player& player);
    ~SmallBullet() = default;
    void Initialize() override;
    void Finalize() override;
    void Update() override;
    void Draw() const override;
};

