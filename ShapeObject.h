#pragma once
#include "Task.h"

#include "Vector2.h"

//形のあるものの抽象オブジェクトクラス
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

    //positionのGetter
    float GetterPosX() const { return _position.GetterX(); };
    float GetterPosY() const { return _position.GetterY(); };
    Vector2<float> GetterPosition() const { return _position; };

    //velocityのGetter
    float GetterVelX() const { return _velocity.GetterX(); };
    float GetterVelY() const { return _velocity.GetterY(); };
    Vector2<float> GetterVelocity() const { return _velocity; };

    float GetterAngle() const { return _angle; };

    //positionのSetter。
    void SetterPosition(Vector2<float>& temp) {
        _position.Setter(temp.GetterX(), temp.GetterY());
    }

    //velocityのSetter
    void SetterVelocity(Vector2<float> temp) {
        _velocity.Setter(temp.GetterX(), temp.GetterY());
    }
    //flagのenumを渡すことでそのフラグが立っているかをboolで返す.
    bool CheckFlag(const int tFlag) const;
    //flagを立てる.
    void SetOnFlag(int tFlag);

    void WaveFlag(int tFlag, bool value);
protected:
    //現在地.ベクトルとして実装. 
    Vector2<float> _position;
    //速度ベクトル
    Vector2<float> _velocity;
    //加速度ベクトル
    Vector2<float> _acceleration;


    //角度.
    float _angle = 0;

    //基本的なMove関数.現在地に速度ベクトルを足す
    void Move();

    int _flag;

    int _color;
};

