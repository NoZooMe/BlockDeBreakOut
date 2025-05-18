#pragma once

#include <string>
#include <vector>
#include "BulletEvent.h"

//StageScrptを読み込むためのユーティリティクラス
class StageScriptLoader
{
public:
	static std::vector<BulletEvent> LoadStageScriptFromJSON(const std::string& filename);

private:
	StageScriptLoader() = delete;	//インスタンス化禁止

};

