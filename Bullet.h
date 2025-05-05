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
    //�ꏊ�A�����A�����A�p�^�[���A�F�A���a
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

    //�p�^�[���ɂ��e�����\�b�h

    void ShotStraight();
    void ShotSin();

    
};

