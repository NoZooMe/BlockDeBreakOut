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

    //�t���O�\����
    enum class fBall {
        _move,
        _out, 
        _wait
    };

    Ball(int x, int y);

    void Init() override ;
    void Fin() override ;
    void Update() override;
    //�{�[�����v���C���[��Ǐ]����Ƃ���Update
    void Update(float playerX, float playerY);
    void Draw() const override;

    //�Փˊ֐��B�����ɏՓ˂��鑊���position��velocity�����
    void ReflectBlock_Vertical(std::shared_ptr<RectangleObject> obj);
    void ReflectBlock_Horizontal(std::shared_ptr<RectangleObject> obj);
};

