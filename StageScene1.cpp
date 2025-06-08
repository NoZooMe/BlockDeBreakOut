#include "StageScene1.h"
#include "Macro.h"
#include "Define.h"
#include "Stage1Script.h"
#include "Keyboard.h"
#include "eItemName.h"
#include "ResourceID.h"
#include "ComplexTransform.h"

using namespace std;


StageScene1::StageScene1(ISceneChangedListener* impl, const Parameter& param) : AbstractStageScene(impl, param){
	
}

void StageScene1::Update() {
	AbstractStageScene::Update();
}

void StageScene1::InitStageScript() {
	_stageScript.push_back(make_unique<Stage1Script>("Stage1Script.json", "Stage1Command.json"));
	_stageScript.push_back(make_unique<Stage1Script>("Stage1SpellScript.json", "Stage1SpellCommand.json"));
}

ResourceID StageScene1::GetStageBGM() const{
	return ResourceID::Stage1;
}

void StageScene1::UpdateStageScript(int cnt) {
	_stageScript[_currentScriptIndex]->Update(cnt, *_bulletMgr, *_player, *_ball);
}

void StageScene1::ChangeCurrentScript(int BlockNum) {
	int newIndex;

	if (BlockNum > Define::BLOCK_NUM/2) {
		newIndex = 0;
	}
	else {
		newIndex = 1;
		//テスト。
		ComplexTransform::mode = SpaceTransformMode::Sinh;
	}

	if (_currentScriptIndex != newIndex) {
		_currentScriptIndex = newIndex;
		_cnt = 0;
	}
}