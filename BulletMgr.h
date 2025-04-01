#pragma once
#include "Task.h"
#include "Player.h"
#include "AbstractBullet.h"
#include <vector>
#include <memory>
class BulletMgr :
    public Task
{
public:
    BulletMgr(int stageNum, int cnt, Player player);
    ~BulletMgr() = default;
    void Initialize() override;
    void Finalize() override;
    void Update() override;
    void Draw() const override;

    void SetCnt(const int& cnt);

private:
    std::vector<std::shared_ptr<AbstractBullet>> _bulletVector;
    int _stageNum;
    int _cnt;
    Player _player;
};

