#pragma once
#include "CircleObject.h"
#include <memory>

class RectangleObject;
class Segment;
template <typename T> class Vector2;

class Ball :
    public CircleObject
{

public:
    //�t���O�\����
    enum class fBall {
        _move,
        _out, 
        _wait,
        _power
    };

    Ball(float x, float y);

    void Initialize() override ;
    void Finalize() override ;
    void Update() override;
    //�{�[�����v���C���[��Ǐ]����Ƃ���Update
    void Update(float playerX, float playerY);
    void Draw() const override;

    //�Փˊ֐��B�����ɏՓ˂��鑊���position��velocity�����
    void ReflectBlock_Vertical(std::shared_ptr<RectangleObject> obj);
    void ReflectBlock_Horizontal(std::shared_ptr<RectangleObject> obj);

    void ReflectFromSurface(const Segment& surface, const Vector2<float>& surfaceVelocity);



private:   

    const static int SPEED = 5;

    void ReflectWall_Vertical();
    void ReflectWall_Horizontal();

    void Check_Out();

    float rand;
    int _powerCnt;
};

