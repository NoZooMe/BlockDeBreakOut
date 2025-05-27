#pragma once
#include "CircleObject.h"
#include "Vector2.h"
#include "Player.h"
#include <memory>
#include "eBulletSize.h"
#include "IBulletBehavior.h"

class Bullet :
    public CircleObject
{
public:
    //�ꏊ�A�����A�����A�p�^�[���A�F�A���a
    Bullet(const Vector2<float>& position, float angle, int speed, std::shared_ptr<IBulletBehavior> b, int color, eBulletSize size);
    ~Bullet() = default;
    void Initialize() override;
    void Finalize() override;
    void Update() override;
    void Draw() const override;
    

    bool CheckOut();

    int GetterSpeed() const { return _speed; };
    int GetterCnt() const { return _cnt; };
    //Behavior�Z�b�g�֐�
    void SetBehavior(std::shared_ptr<IBulletBehavior> b) { _behavior = b; };
private:
    int _color;
    int _speed;
    float _cnt;

    std::shared_ptr<IBulletBehavior> _behavior;
    Vector2<float> _euclidPosition;  //�{���̈ʒu

    

};

