#include "TitleScene.h"
#include "Define.h"
#include "Keyboard.h"
#include "GameScene.h"
#include <DxLib.h>
#include <map>

using namespace std;

const char* TitleScene::TitleMenu1 = "�Q�[��";
const char* TitleScene::TitleMenu2 = "�ݒ�";
const char* TitleScene::TitleMenu3 = "�I��";

TitleScene::TitleScene(ISceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter){
	//�����͊m���ɂ��悤������
	map<int, string> titleMenu;
	titleMenu[0] = TitleMenu1;
	titleMenu[1] = TitleMenu2;
	titleMenu[2] = TitleMenu3;

	_titleMenu = make_shared<Choices>(titleMenu);
}

TitleScene::~TitleScene() {

}

void TitleScene::Initialize() {

}

void TitleScene::Finalize() {

}

void TitleScene::Update() {
	if (_titleMenu->Update() == 0) {

	}
	else if(_titleMenu->Update() == 1){
		Parameter parameter;
		parameter.set(GameScene::ParameterTagLevel, Define::NORMAL);
		_implSceneChangedListener->onSceneChanged(Game, parameter, true);
	}
	else if (_titleMenu->Update() == 2) {

	}
	else if (_titleMenu->Update() == 3) {
		
	}
}

void TitleScene::Draw() const {
	_titleMenu->Draw();
}