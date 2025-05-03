#pragma once
#include "RectangleObject.h"

class Player :
    public RectangleObject
{
private:
    //�萔�錾��
    int life;

    static const int speed = 10;

    //Player�̕�����\���ϐ�.8����.
    int dirV, dirH;

    int _mutekiCnt;

    //�������`�F�b�N
    void Check_Direciton();
    //�����ɍ��킹��Velocity���Z�b�g
    void Set_Velocity();
    //��ʊO�ɂ��邩���`�F�b�N.����ΏC��.
    void Check_Out();
    //��������]������
    void RotateLeft();
    void RotateRight();

public:
    Player(float iniX, float iniY);
    void Initialize() override ;
    void Finalize() override {};
    void Update() override;
    void Draw() const override;

    //��̓I�ȃt���O�̍\����
    enum fPlayer {
        _outVertical,
        _outHorizontal,
        _move,
        _death,
        _muteki, 
        _rotateR,
        _rotateL, 
    };

    //Player��Life�����炷
    void CallDecLife();

    int Getter_PlayerLife() const { return life; };
    Vector2<float> GetterPosition() const;

    //�O���ďo���p��flag�Z�b�g�֐�
    void SetPlayerFlag_OutVertical(bool value);
    void SetPlayerFlag_OutHorizontal(bool value);
    void SetPlayerFlag_Move(bool value);
    void SetPlayerFlag_Death(bool value);

    //�_���[�W���󂯂����ɌĂяo�����֐�
    void DamagePlayer();
    bool isDamaged() const;

};

