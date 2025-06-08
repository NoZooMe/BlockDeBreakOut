#pragma once
#include "ShapeObject.h"
#include "Segment.h"
#include <vector>

//���ۃN���X
class RectangleObject :
    public ShapeObject
{

public:

    RectangleObject(float x, float y, int width, int height);
    virtual void Initialize() override = 0;
    virtual void Finalize() override = 0;
    void Update();
    void Draw() const override;

    int GetterWidth() const { return _width; };
    int GetterHeight() const { return _height; };

    std::vector<Vector2<float>> GetterVertexs() { 
        std::vector<Vector2<float>> temp;
        for (auto vert : vertex)
            { temp.push_back(vert); 
        } return temp; 
    };

    Segment vertSide1, vertSide2, horiSide1, horiSide2;

protected:
    //���̓�̃p�����[�^�������`������Â���
    int _width, _height;
    //�e���_
    Vector2<float> vertex[4];

};

