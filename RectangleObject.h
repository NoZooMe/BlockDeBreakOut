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
  

public:

    RectangleObject(float x, float y, int width, int height);
    virtual void Init() override = 0;
    virtual void Fin() override = 0;
    void Update();
    void Draw() const override;

    int GetterWidth() const { return width; };
    int GetterHeight() const { return height; };

    //����Public�Ŏ����Ă�̏����|��
    Segment vertSide1, vertSide2, horiSide1, horiSide2;

};

