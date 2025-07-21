#pragma once

#include <string>
#include <vector>
#include "BulletEvent.h"
#include "BulletCommand.h"

//StageScrpt��ǂݍ��ނ��߂̃��[�e�B���e�B�N���X
class StageScriptLoader
{
public:
	static std::vector<BulletEvent> LoadStageScriptFromJSON(const std::string& filename);
	static std::vector<BulletCommand::TimedCommand> LoadCommandsFromJSON(const std::string& filename);

private:
	StageScriptLoader() = delete;
	~StageScriptLoader() = delete;

};

