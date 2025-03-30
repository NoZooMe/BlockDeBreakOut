#pragma once
#include "Task.h"

#include "Vector2.h"

//抽象オブジェクトクラス
//当たり判定のためにここから図形クラスを分ける.関数はMove関数のみ実装
class ShapeObject :
    protected Task
{
protected:
    //現在地.ベクトルとして実装
    Vector2<float> position;
    //速度ベクトル
    Vector2<float> velocity;


    //角度.Velocityに三角関数を用いて入れたりする.
    int angle = 0;

    //基本的なMove関数.現在地に速度ベクトルを足す
    void Move();

    //4byteまでのflag
    int flag;

    //tFlagのTFをvalueにする
    void WaveFlag(int tFlag, bool value);

public:
    ShapeObject(float posX, float posY);
    virtual void Initialize() override  = 0;
    void Finalize() override = 0;
    void Update() override;
    void Draw() const override = 0;

    //positionのGetter
    float GetterPosX() const { return position.GetterX(); };
    float GetterPosY() const { return position.GetterY(); };
    Vector2<float> GetterPosition() const { return position; };

    //velocityのGetter
    float GetterVelX() const { return velocity.GetterX(); };
    float GetterVelY() const { return velocity.GetterY(); };

    //positionのSetter.遠回りな気もするけどこれでいいのか.そもそも二段階でSetterを参照するプログラムではいけない気がする
    void SetterPosition(Vector2<float>& temp) {
        position.Setter(temp.GetterX(), temp.GetterY());
    }

    //flagのenumを渡すことでそのフラグが立っているかをboolで返す.外部呼出し可.
    bool CheckFlag(const int tFlag) const;

};

