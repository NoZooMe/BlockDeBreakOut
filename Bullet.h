#pragma once
#include "CircleObject.h"
#include "Vector2.h"
#include "Player.h"
#include <memory>
#include "eBulletSize.h"

class Bullet :
    public CircleObject
{
public:
    //場所、方向、早さ、パターン、色、半径
    Bullet(const Vector2<float>& position, float angle, int speed, int pattern, int color, eBulletSize size);
    ~Bullet() = default;
    void Initialize() override;
    void Finalize() override;
    void Update() override;
    void Draw() const override;

    bool CheckOut();
private:
    int _color;
    int _pattern;
    int _speed;
    float _cnt;

    //パターンによる弾幕メソッド

    void ShotStraight();
    void ShotSin();

    
};

