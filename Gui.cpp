#include "Gui.h"
#include "ImageManager.h"
#include "ResourceID.h"
#include "BlockMgr.h"
#include <DxLib.h>


void Gui::Initialize() {
	_isPhase1 = true;
	_isPhase2 = false;
	_isPhase3 = false;
}

void Gui::Finalize() {

}

void Gui::Update(const PlayerStatus& status, const int liveBlockNum) {
	_drawnStatus = status;

	int liveNum = liveBlockNum;

	if (liveNum <= Define::SPELL_BLOCK_NUM && liveNum > 0) {
		_isPhase1 = false;
		_isPhase2 = true;
		_isPhase3 = false;
	}
	else if (liveNum <= 0) {
		_isPhase1 = false;
		_isPhase2 = false;
		_isPhase3 = true;
	}
	else {
		_isPhase1 = true;
		_isPhase2 = false;
		_isPhase3 = false;
	}


}

void Gui::Draw() const {
	//�g
	DrawBox(Define::SCREEN_WIDTH, 0, Define::DISPLAY_WIDTH, Define::SCREEN_HEIGHT, Define::BLUE, false);
	//�G�̖��O
	DrawString(Define::UI_X, Define::ENEMY_NAME_Y, "VS �}�c��", Define::WHITE);
	//�G�̉摜
	DrawExtendGraph(Define::SCREEN_WIDTH, Define::ENEMY_ILLUST_Y, Define::SCREEN_WIDTH + 283, 430, ImageManager::getIns()->getImage(toString(ResourceID::First)), true);

	//�G�̃Z���t
	if (_isPhase1) {
		DrawString(Define::SCREEN_WIDTH+5, Define::ENEMY_DIALOGUE_Y, "�������Ɠ|�����Ă��炢�܂���B", Define::WHITE);
	}
	if (_isPhase2) {
		DrawString(Define::SCREEN_WIDTH+5, Define::ENEMY_DIALOGUE_Y, "�܂����ł��ˁc�c�B\n��Ԃ�c�߂邵���Ȃ����c�c�I", Define::WHITE);
	}
	if (_isPhase3) {
		DrawString(Define::SCREEN_WIDTH+5, Define::ENEMY_DIALOGUE_Y, "�܂������I�@��������Ȃ�āI�H", Define::WHITE);
	}

	//�v���C���[�̃��C�t
	DrawString(Define::UI_X, Define::PLAYER_LIFE_Y, "Life", Define::WHITE);
	for (int i = 0; i < _drawnStatus._life; ++i) {
		DrawString(Define::UI_X + i * 15, Define::PLAYER_LIFE_Y + 20, "��", Define::WHITE);
	}
	//�v���C���[�̃{��
	DrawString(Define::UI_X, Define::PLAYER_BOMB_Y, "Bomb", Define::WHITE);
	for (int i = 0; i < _drawnStatus._bomb; ++i) {
		DrawString(Define::UI_X + i * 15, Define::PLAYER_BOMB_Y + 25, "��", Define::WHITE);
	}
	//�v���C���[�̃X�R�A
	DrawString(Define::UI_X, Define::PLAYER_SCORE_Y, "Score", Define::WHITE);
	DrawFormatString(Define::UI_X, Define::PLAYER_SCORE_Y + 20, Define::WHITE, "%d", _drawnStatus._score);
	DrawString(Define::UI_X, Define::PLAYER_SCORE_Y + 40, "HighScore", Define::WHITE);
	DrawFormatString(Define::UI_X, Define::PLAYER_SCORE_Y + 60, Define::WHITE, "%d", _drawnStatus._highScore);
}