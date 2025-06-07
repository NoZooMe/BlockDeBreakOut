#pragma once
#include <vector>
#include <optional>

class RectangleObject;
class CircleObject;
class Player;
class Ball;
class BulletMgr;
class BlockMgr;
class ItemMgr;
class Segment;
struct CollisionEvent;
template<typename T> class Vector2;

class ColMgr
{


public:
    ColMgr() = default;
    ~ColMgr() = default;
    void Initialize();
    void Finalize();
    void Update(BlockMgr& blockMgr, BulletMgr& bulletMgr, ItemMgr& itemMgr, Player& player, Ball& ball, std::vector<CollisionEvent>& evArray);

private:
    bool Col_SegmentAndBall(const Segment& segment, const CircleObject& circle) const;
    //è’ìÀÇµÇƒÇ¢ÇÈsegmentÇï‘Ç∑
    std::optional<Segment> Col_RectAndBall(const RectangleObject& rect, const CircleObject& circle) const;
    bool Col_SegmentAndSegment(const Segment& segment1, const Segment& segment2) const;
    //bool Col_RectAndRect(const RectangleObject& rect1, const RectangleObject& rect2) const;
    bool SAT_Intersect(const std::vector<Vector2<float>>& polyA, const std::vector<Vector2<float>>& polyB);

    //ëΩäpå`ÇÃí∏ì_Çé≤Ç…ëŒÇµÇƒéÀâeÇ∑ÇÈ
    void ProjectPolygon(const std::vector<Vector2<float>>& vertices, const Vector2<float>& axis, float& min, float& max);

    
};

