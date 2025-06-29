#pragma once
#include <memory>
class BulletMgr;

class BulletCommand
{
public:
	virtual void Execute(BulletMgr& mgr) = 0;
	virtual ~BulletCommand() = default;
	struct TimedCommand {
		int frame;	//発射フレーム
		std::shared_ptr<BulletCommand> command;
		int duration;	//発射間隔
		bool useDuration;	//間隔で発射するかどうか
	};
};

