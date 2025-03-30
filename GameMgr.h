#pragma once
#include "Task.h"
#include "Player.h"
#include "Ball.h"
#include "ColMgr.h"
#include "BlockMgr.h"
#include <memory>

class GameMgr :
    public Task
{
private:
    ColMgr colMgr;

    std::shared_ptr<Player> player;
    std::shared_ptr<Ball> ball;
    std::shared_ptr<BlockMgr> blockMgr;

    bool Call_ColRectangleAndBall(std::shared_ptr<RectangleObject> player, std::shared_ptr<Ball> ball);

public:
    GameMgr();
    void Init() override ;
    void Fin() override ;
    void Update() override;
    void Draw() const override;

};

