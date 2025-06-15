#include "AbstractDialogueScene.h"
#include "Keyboard.h"
#include "ConvertUtils.h"
#include "Define.h"
#include <DxLib.h>

AbstractDialogueScene::AbstractDialogueScene(ISceneChangedListener* impl, const Parameter& param) : 
AbstractScene(impl, param){

}

void AbstractDialogueScene::Initialize() {
	InitDialogueScript();
	_leftImageHandle = LoadGraph(_dialogues[0].leftImage.c_str());
	_rightImageHandle = LoadGraph(_dialogues[0].rightImage.c_str());
}

void AbstractDialogueScene::Finalize() {

}

void AbstractDialogueScene::Update() {
	if (_finished) CallSceneChange();

	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_RETURN) == 1) {
		_currentIndex++;
		if (_currentIndex >= _dialogues.size()) {
			_finished = true;
		}
		else {
			//次のテキストへ
			auto& entry = _dialogues[_currentIndex];
			_currentText = entry.text;
			_leftImageHandle = LoadGraph(entry.leftImage.c_str());
			_rightImageHandle = LoadGraph(entry.rightImage.c_str());
		}
	}
}

void AbstractDialogueScene::Draw() const {
	if (_finished) return;

	DrawGraph(20, Define::SCREEN_HEIGHT - 800, _leftImageHandle, true);
	DrawGraph(Define::SCREEN_WIDTH - 566/2 - 50, Define::SCREEN_HEIGHT - 800, _rightImageHandle, true);

	// ウィンドウ風の背景
	DrawBox(30, 700, 1250, 840, GetColor(0, 0, 0), true);
	DrawBox(30, 700, 1250, 840, GetColor(255, 255, 255), false);

	std::string speakerStr = ConvertUtils::Utf8ToSjis(_dialogues[_currentIndex].speaker);
	std::string textStr = ConvertUtils::Utf8ToSjis(_dialogues[_currentIndex].text);


	// テキスト
	DrawString(40, 710, speakerStr.c_str(), GetColor(255, 255, 0));
	DrawString(40, 725, textStr.c_str(), GetColor(255, 255, 255));
}

bool AbstractDialogueScene::isFinished() const {
	return _finished;
}