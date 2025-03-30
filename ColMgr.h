#pragma once
#include "Task.h"
#include "RectangleObject.h"
#include "CircleObject.h"


class ColMgr :
    public Task
{

private:
    bool Col_SegmentAndBall(const Segment& segment, const CircleObject& circle) const;
   

    int Check_DistPointAndLine(const Vector2<float>& point, const Vector2<float>& lineBegin, const Vector2<float>& lineEnd) const;

public:
    void Initialize() override {};
    void Finalize() override {};
    void Update() override {};
    void Draw() const override {};

    //�����̕ǁA�����̕ǂւ̏Փ˔���.�{����2���K�v���H
    bool ColVert_RectAndBall(const RectangleObject& rect, const CircleObject& circle) const;
    bool ColHori_RectAndBall(const RectangleObject& rect, const CircleObject& circle) const;
};

