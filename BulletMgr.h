#pragma once
#include "Task.h"
#include "Bullet.h"
#include "eBulletSize.h"
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

    void Set_StraightBullet(eBulletSize size, const Vector2<float>& position, float angle, int speed, int color);
    void Set_SinBullet(eBulletSize size, const Vector2<float>& position, float angle, int speed, int color);

    void CheckOut();

    std::shared_ptr<Bullet> GetBullet(int i) const;
    int GetBulletNum() const;
    void DeleteBullet(int num);

private:
    //’e‚Ì”z—ñ
    std::vector<std::shared_ptr<Bullet>> _vector;

};

