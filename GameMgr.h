#pragma once
class Player;
class Ball;
class BlockMgr;
class BulletMgr;
class ItemMgr;
class IGameLifeCycleHandler;
struct CollisionEvent;

#include<vector>

class GameMgr
{

public:
    GameMgr(IGameLifeCycleHandler* impl);
    void Initialize();
    void Finalize();
    //evColÇÕì«Ç›éÊÇËêÍópÇ»ÇÃÇ≈constéQè∆Ç≈ó«Ç¢ÅB
    void Update(BlockMgr& blockMgr, BulletMgr& bulletMgr, ItemMgr& itemMgr, Player& player, Ball& ball, const std::vector<CollisionEvent>& evCol);
    void Draw(const BlockMgr& blockMgr, const BulletMgr& bulletMgr, const ItemMgr& itemMgr, const Player& player, const Ball& ball) const;

private:
    IGameLifeCycleHandler* _implLifeCycle;
    void CollisionProcess(BlockMgr& blockMgr, BulletMgr& bulletMgr, ItemMgr& itemMgr, Player& player, Ball& ball, const std::vector<CollisionEvent>& evCol);
    bool ItemGenerate(ItemMgr& itemMgr, BlockMgr& blockMgr, int blockIndex);
    void ShakeScreen(int power, int duration);

    int _itemCnt;
    int _itemCntMax;
    bool _isBombActive;
    int _bombCoolCnt;
    int _dx, _dy;
    int _shakeScreenBuffer;
    bool _isShake;
    int _shakeTime;
    int _shakePower;
    int _shakeCnt;


};

