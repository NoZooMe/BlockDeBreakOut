#pragma once
#include "CircleObject.h"
#include "Vector2.h"
#include "Player.h"

class AbstractBullet :
    public CircleObject
{
public:
    //�ꏊ�A�����A�����A�p�^�[���A�F�A���a
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

    //�p�^�[���ɂ��e�����\�b�h
    void ShotStraight();
    void ShotSin();
};

