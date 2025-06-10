#include "Choices.h"
#include "Define.h"
#include "Keyboard.h"
#include "SoundManager.h"
#include "ResourceID.h"
#include <DxLib.h>


using namespace std;
//�����A_choices���|�C���^�Ŏ���choices��ύX����鋰�ꂪ����̂œn���Ȃ�
Choices::Choices(const map<int, string>& choices) : _choices(choices) , itemNum(_choices.size()), nowSelect(0), _x(Define::SCREEN_WIDTH / 2), _y(Define::SCREEN_HEIGHT / 2), _isMove(false){

}

Choices::Choices(const map<int, string>& choices, int x, int y, bool isMoving) : _choices(choices), itemNum(_choices.size()), nowSelect(0), _x(x), _y(y), _isMove(isMoving) {

}

int Choices::Update() {
	//���L�[��������Ă�����
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_DOWN) == 1) {
		nowSelect = (nowSelect + 1) % itemNum;	//�I����Ԃ��������
		SoundManager::getIns()->play(toString(ResourceID::SelectMenuSE));
	}
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_UP) == 1) {
		nowSelect = (nowSelect + (itemNum - 1)) % itemNum;//�I����Ԃ���グ��
		SoundManager::getIns()->play(toString(ResourceID::SelectMenuSE));
	}

	//�G���^�[�L�[�������ꂽ��I�΂�Ă��鍀��(1����n�܂�)��Ԃ��A�����łȂ����0��Ԃ�
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
			DrawFormatString(_x, _y + 20 * i, Define::WHITE, "��%s", _choices.at(i).c_str());
		}
		else {
			DrawFormatString(_x, _y + 20 * i, Define::WHITE, "%s", _choices.at(i).c_str());
		}
	}
}