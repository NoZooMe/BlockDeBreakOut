#pragma once
#include "ShapeObject.h"
//���ۃN���X
class CircleObject :
    public ShapeObject
{
protected:
    //���a���~������Â���
    int r;
public:
    CircleObject(float x, float y, int r);
    virtual void Initialize() override = 0;
    virtual void Finalize() override = 0;
    virtual void Update() override = 0;
    void Draw() const override;

    int GetterR() const { return r; };
};

