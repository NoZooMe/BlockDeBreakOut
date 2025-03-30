#pragma once
#include "ShapeObject.h"
#include "Segment.h"

//抽象クラス
class RectangleObject :
    public ShapeObject
{
protected:
    //この二つのパラメータが長方形を特徴づける
    int width, height;
  

public:

    RectangleObject(float x, float y, int width, int height);
    virtual void Initialize() override = 0;
    virtual void Finalize() override = 0;
    void Update();
    void Draw() const override;

    int GetterWidth() const { return width; };
    int GetterHeight() const { return height; };

    //これPublicで持ってるの少し怖い
    Segment vertSide1, vertSide2, horiSide1, horiSide2;

};

