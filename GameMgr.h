#pragma once
#include "Player.h"
#include "Ball.h"
#include "ColMgr.h"
#include "BlockMgr.h"
#include "BulletMgr.h"
#include <memory>

//íSìñÅB
class GameMgr
{

public:
    GameMgr();
    void Initialize();
    void Finalize();
    void Update(std::shared_ptr<BlockMgr> blockMgr, std::shared_ptr<BulletMgr> bulletMgr);
    void Draw() const;

   

private:

    ColMgr colMgr;
    std::shared_ptr<Player> _player;
    std::shared_ptr<Ball> _ball;
    

    bool Call_ColRectangleAndBall(std::shared_ptr<RectangleObject> player, std::shared_ptr<Ball> ball);
    

};

