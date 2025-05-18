#pragma once

#include <string>
#include <vector>
#include "BulletEvent.h"

//StageScrpt��ǂݍ��ނ��߂̃��[�e�B���e�B�N���X
class StageScriptLoader
{
public:
	static std::vector<BulletEvent> LoadStageScriptFromJSON(const std::string& filename);

private:
	StageScriptLoader() = delete;	//�C���X�^���X���֎~

};

