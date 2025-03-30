#include "GameScene.h"
#include "Define.h"
#include <DxLib.h>

const char* GameScene::ParameterTagLevel = "ParameterTagLevel";
const char* GameScene::ParameterTagStage = "ParameterTagStage";

GameScene::GameScene(ISceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter) {
	_level = _parameter.get(ParameterTagLevel);		//���x����Parameter�ŕR�Â�����Ă��鐔�l����
	gameMgr = std::make_shared<GameMgr>();
}

void GameScene::Initialize() {
	gameMgr->Initialize();
}

void GameScene::Finalize() {
	gameMgr->Finalize();
}

void GameScene::Update() {
	gameMgr->Update();
}

void GameScene::Draw() const {
	gameMgr->Draw();
}