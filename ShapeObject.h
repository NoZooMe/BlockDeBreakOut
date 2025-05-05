#pragma once
#include "Task.h"

#include "Vector2.h"

//���ۃI�u�W�F�N�g�N���X
//�����蔻��̂��߂ɂ�������}�`�N���X�𕪂���.�֐���Move�֐��̂ݎ���
class ShapeObject :
    protected Task
{
protected:
    //���ݒn.�x�N�g���Ƃ��Ď���. RectangleObject�͍��オposition���W
    Vector2<float> _position;
    //���x�x�N�g��
    Vector2<float> _velocity;


    //�p�x.Velocity�ɎO�p�֐���p���ē��ꂽ�肷��.
    float _angle = 0;

    //��{�I��Move�֐�.���ݒn�ɑ��x�x�N�g���𑫂�
    void Move();

    //4byte�܂ł�flag
    int _flag;

    //tFlag��TF��value�ɂ���
    void WaveFlag(int tFlag, bool value);

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

    //position��Setter.�����ȋC�����邯�ǂ���ł����̂�.����������i�K��Setter���Q�Ƃ���v���O�����ł͂����Ȃ��C������
    void SetterPosition(Vector2<float>& temp) {
        _position.Setter(temp.GetterX(), temp.GetterY());
    }

    //flag��enum��n�����Ƃł��̃t���O�������Ă��邩��bool�ŕԂ�.�O���ďo����.
    bool CheckFlag(const int tFlag) const;
    //flag�𗧂Ă�B�O���ďo���B
    void SetOnFlag(int tFlag);

};

