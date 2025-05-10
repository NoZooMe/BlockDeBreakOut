#pragma once
#include "Task.h"
#include "RectangleObject.h"
#include "CircleObject.h"
#include "Player.h"
#include "Ball.h"
#include "BulletMgr.h"
#include "BlockMgr.h"
#include <optional>


class ColMgr
{

private:
    bool Col_SegmentAndBall(const Segment& segment, const CircleObject& circle) const;
    //è’ìÀÇµÇƒÇ¢ÇÈsegmentÇï‘Ç∑
    std::optional<Segment> Col_RectAndBall(const RectangleObject& rect, const CircleObject& circle) const;


public:
    ColMgr() = default;
    ~ColMgr() = default;
    void Initialize();
    void Finalize();
    void Update(BlockMgr& blockMgr, BulletMgr& bulletMgr, Player& player, Ball& ball);

    
};

