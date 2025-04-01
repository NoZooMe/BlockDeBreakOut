#pragma once
#include "CircleObject.h"
#include "Vector2.h"
#include "Player.h"

class AbstractBullet :
    public CircleObject
{
public:
    //今後のことも考えて引数にはPlayer型を渡す
    AbstractBullet(const Vector2<float>& position, int speed, int r, int color, int patter, const Player& player);
    ~AbstractBullet() = default;
    void Initialize() override = 0;
    void Finalize() override = 0;
    void Update() override;
    void Draw() const override = 0;
private:
    int _color;
    int _pattern;
    int _speed;

    Vector2<float> _playerPosition;

    //パターンによる弾幕メソッド
    void SetAngleToPlayer();
};

