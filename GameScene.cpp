#include "GameScene.h"
#include "Define.h"
#include "Keyboard.h"
#include <DxLib.h>

const char* GameScene::ParameterTagLevel = "ParameterTagLevel";
const char* GameScene::ParameterTagStage = "ParameterTagStage";

const char* GameScene::GameMenu1 = "続ける";
const char* GameScene::GameMenu2 = "タイトルに戻る";

using namespace std;

GameScene::GameScene(ISceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter), pose(false){
	_level = _parameter.get(ParameterTagLevel);		//レベルにParameterで紐づけされている数値を代入
	gameMgr = std::make_shared<GameMgr>();

	map<int, string> gameMenu;
	gameMenu[0] = GameMenu1;
	gameMenu[1] = GameMenu2;

	_gameMenu = make_shared<Choices>(gameMenu);
}

void GameScene::Initialize() {
	gameMgr->Initialize();
}

void GameScene::Finalize() {
	gameMgr->Finalize();
}

void GameScene::Update() {
	
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_ESCAPE) == 1) {
		if (pose) {
			pose = false;
		}
		else {
			pose = true;
		}
	}

	if (pose) {
		int nowSelect = _gameMenu->Update();
		if (nowSelect == 1) {
			pose = false;
		}
		else if (nowSelect == 2) {
			Parameter parameter;
			parameter.set(GameScene::ParameterTagLevel, Define::NORMAL);
			_implSceneChangedListener->onSceneChanged(Title, parameter, true);
		}
	}
	else {
		gameMgr->Update();
	}
}

void GameScene::Draw() const {
	
	gameMgr->Draw();
	if (pose) {
		_gameMenu->Draw();
	}
	else {

	}
}