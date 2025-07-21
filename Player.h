#pragma once
#include "RectangleObject.h"
#include "PlayerStatus.h"
#include "AfterImage.h"
#include <deque>

class Player :
    public RectangleObject
{
public:
    Player(float iniX, float iniY);
    void Initialize() override ;
    void Finalize() override {};
    void Update() override;
    void Draw() const override;

    //�t���O�̍\����
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
    
    //�A�N�Z�T
    Vector2<float> GetterPosition() const;

    //Status�֌W
    PlayerStatus Getter_Status() const { return _status; };
    //Life
    void CallDecLife();
    void CallIncLife();
    int Getter_PlayerLife() const { return _status._life; };
    //Bomb
    void CallDecBomb();
    void CallIncBomb();
    //Score
    void AddScore(int amount) { _status._score += amount; };
    int Getter_PlayerScore() const { return _status._score; };
    //Continue
    void Setter_PlayerContinue(int credit);
    int Getter_PlayerContinue() const { return _status._continue; }

    //�O���ďo���p��flag�Z�b�g�֐�
    void SetPlayerFlag_OutVertical(bool value);
    void SetPlayerFlag_OutHorizontal(bool value);
    void SetPlayerFlag_Move(bool value);
    void SetPlayerFlag_Death(bool value);

    //�_���[�W���󂯂����ɌĂяo�����֐�
    void DamagePlayer();
    bool isDamaged() const;

    bool TryUseBomb();

private:

    PlayerStatus _status;

    int _lastScore;

    int _speed;

    //Player�̕�����\���ϐ�.8����.
    int dirV, dirH;

    int _mutekiCnt;

    //�������`�F�b�N
    void Check_Direciton();
    //�����ɍ��킹��Velocity���Z�b�g
    void Set_Velocity();
    //��ʊO�ɂ��邩���`�F�b�N.
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

    void AdjustPosition();

    void DrawExtendGraph() const;

    int _animationCnt;

    //�c���p�L���[
    std::deque<AfterImage> _afterImages;

};

