#include "GameScene.h"
#include "Define.h"
#include <DxLib.h>

const char* GameScene::ParameterTagLevel = "ParameterTagLevel";
const char* GameScene::ParameterTagStage = "ParameterTagStage";

GameScene::GameScene(ISceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter) {
	_level = _parameter.get(ParameterTagLevel);		//ƒŒƒxƒ‹‚ÉParameter‚Å•R‚Ã‚¯‚³‚ê‚Ä‚¢‚é”’l‚ğ‘ã“ü
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