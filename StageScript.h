#pragma once

#include "StageScriptBase.h"
#include "BulletEvent.h"
#include "BulletCommand.h"
#include <string>
#include <vector>

class StageScript : public StageScriptBase {
public:
	explicit StageScript(const std::string& scriptPath, const std::string& commandPath);
	void Update(int cnt, BulletMgr& bulletMgr, const Player& player, const Ball& ball, int stageCnt) override;

private:
	std::vector<BulletEvent> _events;
	
	std::vector<BulletCommand::TimedCommand> _commands;
};

