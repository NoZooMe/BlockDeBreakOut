#pragma once

#include "BulletMgr.h"
#include "Player.h"
#include "Ball.h"
class StageScriptBase
{
public:
	virtual void Update(int cnt, BulletMgr& bulletMgr, const Player& player, const Ball& ball) = 0;
	virtual ~StageScriptBase() = default;
};

