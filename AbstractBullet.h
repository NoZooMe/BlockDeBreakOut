#pragma once
#include "CircleObject.h"
#include "Vector2.h"
#include "Player.h"

class AbstractBullet :
    public CircleObject
{
public:
    //場所、方向、早さ、パターン、色、半径
    AbstractBullet(const Vector2<float>& position, const Vector2<float>& direction, int speed, int pattern, int color, int r);
    ~AbstractBullet() = default;
    void Initialize() override = 0;
    void Finalize() override = 0;
    void Update() override;
    void Draw() const override = 0;
private:
    int _color;
    int _pattern;
    int _speed;

    Vector2<float> _direction;

    //パターンによる弾幕メソッド
    void ShotStraight();
    void ShotSin();
};

