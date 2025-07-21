#pragma once

#include <string>
#include <vector>
#include "BulletEvent.h"
#include "BulletCommand.h"

//StageScrptを読み込むためのユーティリティクラス
class StageScriptLoader
{
public:
	static std::vector<BulletEvent> LoadStageScriptFromJSON(const std::string& filename);
	static std::vector<BulletCommand::TimedCommand> LoadCommandsFromJSON(const std::string& filename);

private:
	StageScriptLoader() = delete;
	~StageScriptLoader() = delete;

};

