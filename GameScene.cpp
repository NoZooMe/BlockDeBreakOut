#include "GameScene.h"
#include "Define.h"
#include <DxLib.h>

const char* GameScene::ParameterTagLevel = "ParameterTagLevel";
const char* GameScene::ParameterTagStage = "ParameterTagStage";

GameScene::GameScene(ISceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter) {
	_level = _parameter.get(ParameterTagLevel);		//���x����Parameter�ŕR�Â�����Ă��鐔�l����
}

void GameScene::Initialize() {

}

void GameScene::Finalize() {

}

void GameScene::Update() {

}

void GameScene::Draw() const {
	DrawFormatString(100, 100, Define::WHITE, "��Փx��%d�ł�", _level);
}