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
    //フラグ構造体
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
    //ボールがプレイヤーを追従するときのUpdate
    void Update(float playerX, float playerY);
    void Draw() const override;

    //衝突関数。引数に衝突する相手のpositionとvelocityを取る
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

