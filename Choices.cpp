#include "Choices.h"
#include "Define.h"
#include "Keyboard.h"
#include <DxLib.h>


using namespace std;
//ここ、_choicesをポインタで持つとchoicesを変更される恐れがあるので渡せない
Choices::Choices(const map<int, string>& choices) : _choices(choices) , itemNum(_choices.size()), nowSelect(0){

}

int Choices::Update() {
	//下キーが押されていたら
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_DOWN) == 1) {
		nowSelect = (nowSelect + 1) % itemNum;	//選択状態を一つ下げる
	}
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_UP) == 1) {
		nowSelect = (nowSelect + (itemNum - 1)) % itemNum;//選択状態を一つ上げる
	}

	//エンターキーが押されたら選ばれている項目(1から始まる)を返し、そうでなければ0を返す
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_RETURN) == 1) {
		return nowSelect+1;
	}
	else {
		return 0;
	}
}

void Choices::Draw() const {
	for (int i = 0; i < _choices.size(); i++) {
		if (i == nowSelect) {
			DrawFormatString(200, 150 + 20 * i, Define::WHITE, "■%s", _choices.at(i).c_str());
		}
		else {
			DrawFormatString(200, 150 + 20 * i, Define::WHITE, "%s", _choices.at(i).c_str());
		}
	}
}