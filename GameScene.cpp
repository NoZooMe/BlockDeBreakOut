#include "GameScene.h"
#include "Define.h"
#include <DxLib.h>

const char* GameScene::ParameterTagLevel = "ParameterTagLevel";
const char* GameScene::ParameterTagStage = "ParameterTagStage";

GameScene::GameScene(ISceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter) {
	_level = _parameter.get(ParameterTagLevel);		//ƒŒƒxƒ‹‚ÉParameter‚Å•R‚Ã‚¯‚³‚ê‚Ä‚¢‚é”’l‚ğ‘ã“ü
}

void GameScene::Initialize() {

}

void GameScene::Finalize() {

}

void GameScene::Update() {

}

void GameScene::Draw() const {
	DrawFormatString(100, 100, Define::WHITE, "“ïˆÕ“x‚Í%d‚Å‚·", _level);
}