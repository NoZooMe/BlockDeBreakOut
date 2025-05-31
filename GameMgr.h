#pragma once
#include "Player.h"
#include "Ball.h"
#include "BlockMgr.h"
#include "BulletMgr.h"
#include "ItemMgr.h"
#include "IGameLifecycleHandler.h"
#include "CollisitonEvent.h"
#include <memory>

class GameMgr
{

public:
    GameMgr(IGameLifeCycleHandler* impl);
    void Initialize();
    void Finalize();
    //evCol�͓ǂݎ���p�Ȃ̂�const�Q�Ƃŗǂ��B
    void Update(BlockMgr& blockMgr, BulletMgr& bulletMgr, ItemMgr& itemMgr, Player& player, Ball& ball, const std::vector<CollisionEvent>& evCol);
    void Draw(const BlockMgr& blockMgr, const BulletMgr& bulletMgr, const ItemMgr& itemMgr, const Player& player, const Ball& ball) const;

private:
    IGameLifeCycleHandler* _implLifeCycle;
    void CollisionProcess(BlockMgr& blockMgr, BulletMgr& bulletMgr, ItemMgr& itemMgr, Player& player, Ball& ball, const std::vector<CollisionEvent>& evCol);
    bool ItemGenerate(ItemMgr& itemMgr, BlockMgr& blockMgr, int blockIndex);

    int _itemCnt;
    int _itemCntMax;
};

