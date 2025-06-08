#pragma once
#include <memory>
class BulletMgr;

class BulletCommand
{
public:
	virtual void Execute(BulletMgr& mgr) = 0;
	virtual ~BulletCommand() = default;
	struct TimedCommand {
		int frame;	//”­ËƒtƒŒ[ƒ€
		std::shared_ptr<BulletCommand> command;
		int duration;	//”­ËŠÔŠu
		bool useDuration;	//ŠÔŠu‚Å”­Ë‚·‚é‚©‚Ç‚¤‚©
	};
};

