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

    //Playerの方向を表す変数.8方向.
    int dirV, dirH;

    int _mutekiCnt;

    //方向をチェック
    void Check_Direciton();
    //方向に合わせてVelocityをセット
    void Set_Velocity();
    //画面外にいるかをチェック.いれば修正.
    void Check_Out();
    //自分を回転させる
    void RotateLeft();
    void RotateRight();

    float _t;
    const float _dt;

    void Set_VelocityODE(float t, float dt);
    // dx/dt = σ(y - x)
    // dy/dt = x(ρ - x) - y
    void Set_VelocityLorenzA(float t, float dt);

public:
    Player(float iniX, float iniY);
    void Initialize() override ;
    void Finalize() override {};
    void Update() override;
    void Draw() const override;

    //具体的なフラグの構造体
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

    //Status関係
    PlayerStatus Getter_Status() const { return _status; };
    //Life関係
    void CallDecLife();
    void CallIncLife();
    int Getter_PlayerLife() const { return _status._life; };
    //PlayerのScoreを追加
    void AddScore(int amount) { _status._score += amount; };
    int Getter_PlayerScore() const { return _status._score; };

    //外部呼出し用のflagセット関数
    void SetPlayerFlag_OutVertical(bool value);
    void SetPlayerFlag_OutHorizontal(bool value);
    void SetPlayerFlag_Move(bool value);
    void SetPlayerFlag_Death(bool value);

    //ダメージを受けた時に呼び出される関数
    void DamagePlayer();
    bool isDamaged() const;

};

