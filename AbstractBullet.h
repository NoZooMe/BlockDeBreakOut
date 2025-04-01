#pragma once
#include "CircleObject.h"
#include "Vector2.h"
#include "Player.h"

class AbstractBullet :
    public CircleObject
{
public:
    //����̂��Ƃ��l���Ĉ����ɂ�Player�^��n��
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

    //�p�^�[���ɂ��e�����\�b�h
    void SetAngleToPlayer();
};

