#pragma once
#include "Task.h"

#include "Vector2.h"

//抽象オブジェクトクラス
//当たり判定のためにここから図形クラスを分ける.関数はMove関数のみ実装
class ShapeObject :
    protected Task
{
protected:
    //現在地.ベクトルとして実装. RectangleObjectは左上がposition座標
    Vector2<float> _position;
    //速度ベクトル
    Vector2<float> _velocity;


    //角度.Velocityに三角関数を用いて入れたりする.
    float _angle = 0;

    //基本的なMove関数.現在地に速度ベクトルを足す
    void Move();

    //4byteまでのflag
    int _flag;

    //tFlagのTFをvalueにする
    void WaveFlag(int tFlag, bool value);

public:
    ShapeObject(float posX, float posY);
    virtual void Initialize() override  = 0;
    void Finalize() override = 0;
    void Update() override;
    void Draw() const override = 0;
    void Draw(float x, float y, int handle) const;

    //positionのGetter
    float GetterPosX() const { return _position.GetterX(); };
    float GetterPosY() const { return _position.GetterY(); };
    Vector2<float> GetterPosition() const { return _position; };

    //velocityのGetter
    float GetterVelX() const { return _velocity.GetterX(); };
    float GetterVelY() const { return _velocity.GetterY(); };

    //positionのSetter.遠回りな気もするけどこれでいいのか.そもそも二段階でSetterを参照するプログラムではいけない気がする
    void SetterPosition(Vector2<float>& temp) {
        _position.Setter(temp.GetterX(), temp.GetterY());
    }

    //flagのenumを渡すことでそのフラグが立っているかをboolで返す.外部呼出し可.
    bool CheckFlag(const int tFlag) const;
    //flagを立てる。外部呼出し可。
    void SetOnFlag(int tFlag);

};

