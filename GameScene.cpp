#include "GameScene.h"
#include "Define.h"
#include "Keyboard.h"
#include "SoundManager.h"
#include "ResourceID.h"
#include <DxLib.h>

const char* GameScene::ParameterTagLevel = "ParameterTagLevel";
const char* GameScene::ParameterTagStage = "ParameterTagStage";

const char* GameScene::GameMenu1 = "������";
const char* GameScene::GameMenu2 = "�^�C�g���ɖ߂�";

using namespace std;

GameScene::GameScene(ISceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter), pose(false){
	_level = _parameter.get(ParameterTagLevel);		//���x����Parameter�ŕR�Â�����Ă��鐔�l����

	Parameter param;

	_stageScene1 = make_shared<StageScene1>(this, param);

	map<int, string> gameMenu;
	gameMenu[0] = GameMenu1;
	gameMenu[1] = GameMenu2;

	_gameMenu = make_shared<Choices>(gameMenu);
}

void GameScene::Initialize() {
	_stageScene1->Initialize();
}

void GameScene::Finalize() {
	_stageScene1->Finalize();
}

void GameScene::Update() {
	
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
			Parameter parameter;
			parameter.set(GameScene::ParameterTagLevel, Define::NORMAL);
			_implSceneChangedListener->onSceneChanged(Title, parameter, true);
		}
	}
	else {
		_stageScene1->Update();
	}
}

void GameScene::Draw() const {
	
	_stageScene1->Draw();
	if (pose) {
		_gameMenu->Draw();
	}
	else {

	}
}

void GameScene::onSceneChanged(const eScene nextScene, const Parameter& parameter, const bool stackClear) {

}