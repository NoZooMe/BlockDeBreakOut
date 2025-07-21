#pragma once
class BulletMgr;
class Player;
class Ball;

class StageScriptBase
{
public:
	virtual void Update(int cnt, BulletMgr& bulletMgr, const Player& player, const Ball& ball, int stageCnt) = 0;
	virtual ~StageScriptBase() = default;
};

