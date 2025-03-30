#pragma once
#include "RectangleObject.h"

class Player :
    public RectangleObject
{
private:
    //定数宣言部
    int life;

    static const int speed = 10;

    //IDethPlayer* listener;

    //Playerの方向を表す変数.8方向.
    int dirV, dirH;


    //方向をチェック
    void Check_Direciton();
    //方向に合わせてVelocityをセット
    void Set_Velocity();
    //画面外にいるかをチェック.いれば修正.
    void Check_Out();

public:
    //Player(float iniX, float iniY, IDethPlayer* iListner);
    Player(float iniX, float iniY);
    void Initialize() override ;
    void Finalize() override {};
    void Update() override;
    void Draw() const override;

    //具体的なフラグの構造体
    enum class fPlayer {
        _outVertical,
        _outHorizontal,
        _move,
        _death,
    };

    //PlayerのLifeを減らす
    void CallDecLife();

    int Getter_PlayerLife() const { return life; };

    //外部呼出し用のflagセット関数
    void SetPlayerFlag_OutVertical(bool value);
    void SetPlayerFlag_OutHorizontal(bool value);
    void SetPlayerFlag_Move(bool value);
    void SetPlayerFlag_Death(bool value);
};

