#pragma once
#include "ShapeObject.h"
//’ŠÛƒNƒ‰ƒX
class CircleObject :
    public ShapeObject
{
protected:
    //”¼Œa‚ª‰~‚ğ“Á’¥‚Ã‚¯‚é
    int r;
public:
    CircleObject(float x, float y, int r);
    virtual void Initialize() override = 0;
    virtual void Finalize() override = 0;
    virtual void Update() override = 0;
    void Draw() const override;

    int GetterR() const { return r; };
};

