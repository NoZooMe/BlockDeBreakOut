#pragma once
#include "ShapeObject.h"

//円形オブジェクトの抽象クラス
class CircleObject :
    public ShapeObject
{
protected:
    int _r;
public:
    CircleObject(float x, float y, int r);
    virtual void Initialize() override = 0;
    virtual void Finalize() override = 0;
    virtual void Update() override = 0;
    void Draw() const override;

    int GetterR() const { return _r; };
};

