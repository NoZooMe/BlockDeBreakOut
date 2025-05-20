#pragma once
#include "RectangleObject.h"

class Player :
    public RectangleObject
{
private:

    struct Playerstatus {
        int life = 5;
        int score = 0;
        int lastScore = 0;

    } _status;

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

    //Life関係
    void CallDecLife();
    void CallIncLife();
    int Getter_PlayerLife() const { return _status.life; };


    Vector2<float> GetterPosition() const;

    //PlayerのScoreを追加
    void AddScore(int amount) { _status.score += amount; };
    int Getter_PlayerScore() const { return _status.score; };

    //外部呼出し用のflagセット関数
    void SetPlayerFlag_OutVertical(bool value);
    void SetPlayerFlag_OutHorizontal(bool value);
    void SetPlayerFlag_Move(bool value);
    void SetPlayerFlag_Death(bool value);

    //ダメージを受けた時に呼び出される関数
    void DamagePlayer();
    bool isDamaged() const;

};

