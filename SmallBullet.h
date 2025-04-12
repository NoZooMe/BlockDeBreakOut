#pragma once
#include "AbstractBullet.h"
class SmallBullet :
    public AbstractBullet
{
public:
    SmallBullet(const Vector2<float>& position, const Vector2<float>& direction, int speed, int pattern, int color);
    ~SmallBullet() = default;
    void Initialize() override;
    void Finalize() override;
    void Update() override;
    void Draw() const override;
};

