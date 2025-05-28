#pragma once
#include "ShapeObject.h"
#include "Segment.h"

//���ۃN���X
class RectangleObject :
    public ShapeObject
{
protected:
    //���̓�̃p�����[�^�������`������Â���
    int width, height;
    //�e���_
    Vector2<float> vertex[4];

public:

    RectangleObject(float x, float y, int width, int height);
    virtual void Initialize() override = 0;
    virtual void Finalize() override = 0;
    void Update();
    void Draw() const override;

    int GetterWidth() const { return width; };
    int GetterHeight() const { return height; };

    Segment vertSide1, vertSide2, horiSide1, horiSide2;

};

