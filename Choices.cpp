#include "Choices.h"
#include "Define.h"
#include "Keyboard.h"
#include <DxLib.h>


using namespace std;
//�����A_choices���|�C���^�Ŏ���choices��ύX����鋰�ꂪ����̂œn���Ȃ�
Choices::Choices(const map<int, string>& choices) : _choices(choices) , itemNum(_choices.size()), nowSelect(0){

}

int Choices::Update() {
	//���L�[��������Ă�����
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_DOWN) == 1) {
		nowSelect = (nowSelect + 1) % itemNum;	//�I����Ԃ��������
	}
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_UP) == 1) {
		nowSelect = (nowSelect + (itemNum - 1)) % itemNum;//�I����Ԃ���グ��
	}

	//�G���^�[�L�[�������ꂽ��I�΂�Ă��鍀��(1����n�܂�)��Ԃ��A�����łȂ����0��Ԃ�
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
			DrawFormatString(200, 150 + 20 * i, Define::WHITE, "��%s", _choices.at(i).c_str());
		}
		else {
			DrawFormatString(200, 150 + 20 * i, Define::WHITE, "%s", _choices.at(i).c_str());
		}
	}
}