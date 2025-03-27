#include "TitleScene.h"
#include "Define.h"
#include "Keyboard.h"
#include "GameScene.h"
#include <DxLib.h>

TitleScene::TitleScene(ISceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter) {

}

TitleScene::~TitleScene() {

}

void TitleScene::Initialize() {

}

void TitleScene::Finalize() {

}

void TitleScene::Update() {
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_N) == 1) {
		Parameter parameter;
		parameter.set(GameScene::ParameterTagLevel, Define::NORMAL);
		_implSceneChangedListener->onSceneChanged(Game, parameter, true);
	} 
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_H) == 1) {
		Parameter parameter;
		parameter.set(GameScene::ParameterTagLevel, Define::HARD);
		_implSceneChangedListener->onSceneChanged(Game, parameter, true);
	}
}

void TitleScene::Draw() const {
	DrawString(200, 200, "タイトル画面です\n", Define::WHITE);
	DrawString(200, 220, "Nキーを押すとノーマルモード, \nHキーでハードモードに移ります.", Define::WHITE);
}