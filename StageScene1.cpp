#include "StageScene1.h"
#include "Macro.h"
#include "Define.h"
#include "Stage1Script.h"
#include "Keyboard.h"
#include "eItemName.h"
#include "ResourceID.h"

using namespace std;


StageScene1::StageScene1(ISceneChangedListener* impl, const Parameter& param) : AbstractStageScene(impl, param){
	
}

void StageScene1::Update() {
	AbstractStageScene::Update();
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_S) == 1) {
		_itemMgr->Generate(eItemName::PowerUp, 200, 200);
	}
}

void StageScene1::InitStageScript() {
	//_stageScript = make_unique<Stage1Script>("Stage1SpellScript.json", "Stage1SpellCommand.json");
	_stageScript = make_unique<Stage1Script>("Stage1Script.json", "Stage1Command.json");
}

ResourceID StageScene1::GetStageBGM() const{
	return ResourceID::Stage1;
}

void StageScene1::UpdateStageScript(int cnt) {
	_stageScript->Update(cnt, *_bulletMgr, *_player, *_ball);
}