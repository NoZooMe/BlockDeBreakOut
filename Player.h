#pragma once
#include "RectangleObject.h"
#include "PlayerStatus.h"

class Player :
    public RectangleObject
{
private:

    struct PlayerStatus _status;

    int _lastScore;

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

    float _t;
    const float _dt;

    void Set_VelocityODE(float t, float dt);
    // dx/dt = ��(y - x)
    // dy/dt = x(�� - x) - y
    void Set_VelocityLorenzA(float t, float dt);

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
        _onODE, 
    };
    
    Vector2<float> GetterPosition() const;

    //Status�֌W
    PlayerStatus Getter_Status() const { return _status; };
    //Life�֌W
    void CallDecLife();
    void CallIncLife();
    int Getter_PlayerLife() const { return _status._life; };
    //Player��Score��ǉ�
    void AddScore(int amount) { _status._score += amount; };
    int Getter_PlayerScore() const { return _status._score; };

    //�O���ďo���p��flag�Z�b�g�֐�
    void SetPlayerFlag_OutVertical(bool value);
    void SetPlayerFlag_OutHorizontal(bool value);
    void SetPlayerFlag_Move(bool value);
    void SetPlayerFlag_Death(bool value);

    //�_���[�W���󂯂����ɌĂяo�����֐�
    void DamagePlayer();
    bool isDamaged() const;

};

