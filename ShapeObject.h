#pragma once
#include "Task.h"

#include "Vector2.h"

//�`�̂�����̂̒��ۃI�u�W�F�N�g�N���X
class ShapeObject :
    protected Task
{

public:
    ShapeObject(float posX, float posY);
    virtual void Initialize() override  = 0;
    void Finalize() override = 0;
    void Update() override;
    void Draw() const override = 0;
    void Draw(float x, float y, int handle) const;

    //position��Getter
    float GetterPosX() const { return _position.GetterX(); };
    float GetterPosY() const { return _position.GetterY(); };
    Vector2<float> GetterPosition() const { return _position; };

    //velocity��Getter
    float GetterVelX() const { return _velocity.GetterX(); };
    float GetterVelY() const { return _velocity.GetterY(); };
    Vector2<float> GetterVelocity() const { return _velocity; };

    float GetterAngle() const { return _angle; };

    //position��Setter�B
    void SetterPosition(Vector2<float>& temp) {
        _position.Setter(temp.GetterX(), temp.GetterY());
    }

    //velocity��Setter
    void SetterVelocity(Vector2<float> temp) {
        _velocity.Setter(temp.GetterX(), temp.GetterY());
    }
    //flag��enum��n�����Ƃł��̃t���O�������Ă��邩��bool�ŕԂ�.
    bool CheckFlag(const int tFlag) const;
    //flag�𗧂Ă�.
    void SetOnFlag(int tFlag);

    void WaveFlag(int tFlag, bool value);
protected:
    //���ݒn.�x�N�g���Ƃ��Ď���. 
    Vector2<float> _position;
    //���x�x�N�g��
    Vector2<float> _velocity;
    //�����x�x�N�g��
    Vector2<float> _acceleration;


    //�p�x.
    float _angle = 0;

    //��{�I��Move�֐�.���ݒn�ɑ��x�x�N�g���𑫂�
    void Move();

    int _flag;

    int _color;
};

