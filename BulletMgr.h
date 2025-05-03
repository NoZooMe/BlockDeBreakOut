#pragma once
#include "Task.h"
#include "AbstractBullet.h"
#include <vector>
#include <memory>
class BulletMgr :
    public Task
{
public:
    BulletMgr();
    ~BulletMgr() = default;
    void Initialize() override;
    void Finalize() override;
    void Update() override;
    void Draw() const override;

    void Set_StraightSmallBullet(const Vector2<float>& position, const Vector2<float>& direction, int speed, int color);
    void Set_SinSmallBullet(const Vector2<float>& position, const Vector2<float>& direction, int speed, int color);

    void CheckOut();

    std::shared_ptr<AbstractBullet> GetBullet(int i) const;
    int GetBulletNum() const;
    void DeleteBullet(int num);

private:
    //’e‚Ì”z—ñ
    std::vector<std::shared_ptr<AbstractBullet>> _vector;

};

