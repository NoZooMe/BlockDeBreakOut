#include "Choices.h"
#include "Define.h"
#include "Keyboard.h"
#include "SoundManager.h"
#include "ResourceID.h"
#include <DxLib.h>


using namespace std;
//ここ、_choicesをポインタで持つとchoicesを変更される恐れがあるので渡せない
Choices::Choices(const map<int, string>& choices) : _choices(choices) , itemNum(_choices.size()), nowSelect(0), _x(Define::SCREEN_WIDTH / 2), _y(Define::SCREEN_HEIGHT / 2), _isMove(false){

}

Choices::Choices(const map<int, string>& choices, int x, int y, bool isMoving) : _choices(choices), itemNum(_choices.size()), nowSelect(0), _x(x), _y(y), _isMove(isMoving) {

}

int Choices::Update() {
	//下キーが押されていたら
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_DOWN) == 1) {
		nowSelect = (nowSelect + 1) % itemNum;	//選択状態を一つ下げる
		SoundManager::getIns()->play(toString(ResourceID::SelectMenuSE));
	}
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_UP) == 1) {
		nowSelect = (nowSelect + (itemNum - 1)) % itemNum;//選択状態を一つ上げる
		SoundManager::getIns()->play(toString(ResourceID::SelectMenuSE));
	}

	//エンターキーが押されたら選ばれている項目(1から始まる)を返し、そうでなければ0を返す
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_RETURN) == 1) {
		SoundManager::getIns()->play(toString(ResourceID::SelectMenuSE));
		return nowSelect+1;
	}
	else {
		return 0;
	}
}

void Choices::Draw() const {
	for (int i = 0; i < _choices.size(); i++) {
		if (i == nowSelect) {
			DrawFormatString(_x, _y + 20 * i, Define::WHITE, "■%s", _choices.at(i).c_str());
		}
		else {
			DrawFormatString(_x, _y + 20 * i, Define::WHITE, "%s", _choices.at(i).c_str());
		}
	}
}