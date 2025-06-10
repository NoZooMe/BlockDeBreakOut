#include "GameScene.h"
#include "Define.h"
#include "Keyboard.h"
#include "SoundManager.h"
#include "ResourceID.h"
#include "StageScene1.h"
#include "DialogueScene1.h"
#include "Macro.h"
#include <DxLib.h>

const char* GameScene::ParameterTagLevel = "ParameterTagLevel";
const char* GameScene::ParameterTagStage = "ParameterTagStage";

const char* GameScene::GameMenu1 = "続ける";
const char* GameScene::GameMenu2 = "タイトルに戻る";

using namespace std;

GameScene::GameScene(ISceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter), pose(false), _isClear(false){
	_level = _parameter.get(ParameterTagLevel);		//レベルにParameterで紐づけされている数値を代入

	Parameter param;

	_currentScene = make_shared<DialogueScene1>(this, param);

	map<int, string> gameMenu;
	gameMenu[0] = GameMenu1;
	gameMenu[1] = GameMenu2;

	_gameMenu = make_shared<Choices>(gameMenu);
}

void GameScene::Initialize() {
	_currentScene->Initialize();
}

void GameScene::Finalize() {
	_currentScene->Finalize();
	_currentScene.reset();
}

void GameScene::Update() {

	if (_isClear) {
		_currentScene->Finalize();
		Parameter param;
		_implSceneChangedListener->onSceneChanged(eScene::Title, param, true);
	}
	else {
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_ESCAPE) == 1) {
			if (pose) {
				pose = false;
			}
			else {
				SoundManager::getIns()->play(toString(ResourceID::OpenMenuSE));
				pose = true;
			}
		}

		if (pose) {
			int nowSelect = _gameMenu->Update();
			if (nowSelect == 1) {
				pose = false;
			}
			else if (nowSelect == 2) {
				_currentScene->Finalize();
				Parameter parameter;
				parameter.set(GameScene::ParameterTagLevel, Define::NORMAL);
				_implSceneChangedListener->onSceneChanged(Title, parameter, true);
			}
		}
		else {
			_currentScene->Update();
		}
	}
}

void GameScene::Draw() const {
	
	_currentScene->Draw();
	if (pose) {
		_gameMenu->Draw();
	}
	else {

	}
}

void GameScene::onSceneChanged(const eScene nextScene, const Parameter& parameter, const bool stackClear) {
	_currentScene->Finalize();
	switch (nextScene) {
	case eScene::Stage1:
		_currentScene = std::make_shared<StageScene1>(this, parameter);
		break;
	default:
		ERR("不明なシーンです");
	}
	_currentScene->Initialize();
}

void GameScene::exitGame() {
	_isClear = true;
}