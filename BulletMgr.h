#pragma once
#include "Task.h"
#include "AbstractBullet.h"
#include <vector>
#include <memory>
class BulletMgr :
    public Task
{
public:
    BulletMgr() = default;
    ~BulletMgr() = default;
    void Initialize() override;
    void Finalize() override;
    void Update() override;
    void Draw() const override;

private:
};

