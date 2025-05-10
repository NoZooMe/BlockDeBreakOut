#pragma once
#include "Player.h"
#include "Ball.h"
#include "BlockMgr.h"
#include "BulletMgr.h"
#include "IGameLifecycleHandler.h"
#include <memory>

//�S���B
class GameMgr
{

public:
    GameMgr(IGameLifeCycleHandler* impl);
    void Initialize();
    void Finalize();
    void Update(BlockMgr& blockMgr, BulletMgr& bulletMgr, Player& player, Ball& ball);
    void Draw(const BlockMgr& blockMgr, const BulletMgr& bulletMgr, const Player& player, const Ball& ball) const;

private:
    
    IGameLifeCycleHandler* _implLifeCycle;
};

