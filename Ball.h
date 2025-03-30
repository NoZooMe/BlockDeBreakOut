#pragma once
#include "CircleObject.h"
#include "RectangleObject.h"
#include <memory>
class Ball :
    public CircleObject
{
private:    

    const static int SPEED = 5;

    void ReflectWall_Vertical();
    void ReflectWall_Horizontal();

    //
    void Check_Out();

public:

    //フラグ構造体
    enum class fBall {
        _move,
        _out, 
        _wait
    };

    Ball(int x, int y);

    void Init() override ;
    void Fin() override ;
    void Update() override;
    //ボールがプレイヤーを追従するときのUpdate
    void Update(float playerX, float playerY);
    void Draw() const override;

    //衝突関数。引数に衝突する相手のpositionとvelocityを取る
    void ReflectBlock_Vertical(std::shared_ptr<RectangleObject> obj);
    void ReflectBlock_Horizontal(std::shared_ptr<RectangleObject> obj);
};

