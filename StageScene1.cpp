#include "StageScene1.h"
#include "Macro.h"
#include "Define.h"
#include "StageScript.h"
#include "Keyboard.h"
#include "eItemName.h"
#include "ResourceID.h"
#include "SoundManager.h"
#include "GlobalStatusManager.h"
#include "ComplexTransform.h"

using namespace std;


StageScene1::StageScene1(ISceneChangedListener* impl, const Parameter& param) : AbstractStageScene(impl, param), _spell1Flag(false), _spell1Cnt(0){
	GlobalStatusManager::getIns()->SetGlobalFlag(eGlobalStatusFlag::Stage1Enter, true);
	_gui->SetterStageNum(1);
}

void StageScene1::Update() {
	AbstractStageScene::Update();
	if (_spell1Flag) {
		_spell1Cnt++;
	}
}

void StageScene1::InitStageScript() {
	_stageScript.push_back(make_unique<StageScript>("resources/Stage1Script.json", "resources/Stage1Command.json"));
	_stageScript.push_back(make_unique<StageScript>("resources/Stage1SpellScript.json", "resources/Stage1SpellCommand.json"));
}

ResourceID StageScene1::GetStageBGM() const{
	return ResourceID::Stage1;
}

void StageScene1::UpdateStageScript(int cnt) {
	_stageScript[_currentScriptIndex]->Update(cnt, *_bulletMgr, *_player, *_ball, Define::STAGE1_CNT);
}

void StageScene1::ChangeCurrentScript(int BlockNum) {
	int newIndex;

	if (BlockNum > Define::SPELL_BLOCK_NUM) {
		newIndex = 0;
		ComplexTransform::mode = SpaceTransformMode::Identity;
	}
	else {
		newIndex = 1;
		if (!_spell1Flag) {
			_spell1Flag = true;
		}
		if (_spell1Cnt == 240) {
			//ここ冗長じゃない？
			SoundManager::getIns()->play(toString(ResourceID::EnemyAtackSE));
			_effectPipeline->AddWaveEffect(30, 0.5f, 2.0f, 5);
			//テスト。
			ComplexTransform::mode = SpaceTransformMode::Sinh;
		}

	}
	if (_spell1Cnt >= 240) {
		_player->WaveFlag(Player::fPlayer::_onODE, true);
	}

	if (_currentScriptIndex != newIndex) {
		_currentScriptIndex = newIndex;
		_cnt = 0;
	}
}