#pragma once

class BulletMgr;
#include <memory>
class BulletCommand
{
public:
	virtual void Execute(BulletMgr& mgr) = 0;
	virtual ~BulletCommand() = default;
	struct TimedCommand {
		int frame;	//���˃t���[��
		std::shared_ptr<BulletCommand> command;
	};
};

