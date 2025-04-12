#include "GameMgr.h"
#include "Define.h"
#include "Keyboard.h"
#include "Macro.h"
#include <DxLib.h>

using namespace std;

GameMgr::GameMgr() : _player(make_shared<Player>(Define::PLAYER_INIX, Define::PLAYER_INIY)), _ball(make_shared<Ball>(Define::BALL_INIX, Define::BALL_INIY)){
	
}

void GameMgr::Initialize() {
	_player->Initialize();
	_ball->Initialize();
}

void GameMgr::Finalize() {
	_player->Finalize();
	_ball->Finalize();

}

void GameMgr::Update(shared_ptr<BlockMgr> blockMgr, shared_ptr<BulletMgr> bulletMgr) {

	//�c�@������Ƃ��ƂȂ��Ƃ��ŕ���
	if (_player->Getter_PlayerLife() > 0 && blockMgr->Getter_LiveNum() != 0) {//�c�@�����邩�N���A���ĂȂ��Ƃ�
		//��ʊO�����͊e�C���X�^���X�ɔC����.

		//�Փ˔��蕔
		//Player��Ball���������Ă���Γ`����
		Call_ColRectangleAndBall(_player, _ball);
		
		//Block��Ball�̓����蔻��
		for (int i = 0; i < Define::BLOCK_NUM; i++) {
			//�����Ă���Ȃ�
			if (blockMgr->Getter_LiveBlock(i) != nullptr) {//nullptr�֗������ǂ���Ȃ��Ƃ���Ă���?
				if (Call_ColRectangleAndBall(blockMgr->Getter_LiveBlock(i), _ball)) {//����������
					blockMgr->SetBlockFlag_Live(i, false);
				}
			}
		}
		
		//Player�ɂ��҂���Ԃ�����Ă����炪���̂�flag��ON�݂̂ɂ���B
		//ball���҂���ԂȂ瓮���Ȃ�
		if (!_ball->CheckFlag((int)Ball::fBall::_wait)) {
			_player->Update();
		}
		if (_ball->CheckFlag((int)Ball::fBall::_move)) {
			_ball->Update();
		}
		else {//ball��player�ɒǏ]����Ƃ�
			_ball->Update(_player->GetterPosX() + _player->GetterWidth() / 2, _player->GetterPosY() - (_ball->GetterR()));
			if (Keyboard::getIns()->getPressingCount(KEY_INPUT_SPACE) != 0) {

			}

		}

		//���������ǂ�����GameMgr������Bbool�ŕԂ����̌�̏�����StageScene�ɔC����B
		//�{�[�������ɗ�������
		if (_ball->CheckFlag((int)Ball::fBall::_out)) {
			_ball->Finalize();
			//�C���X�^���X�ւ̃|�C���^�����
			_ball.reset();
			_player->CallDecLife();

			//�V�����|�C���^����
			_ball = std::make_shared<Ball>(_player->GetterPosX() + _player->GetterWidth() / 2, _player->GetterPosY() - Define::BALL_RADIUS);
			_ball->Initialize();
		}
	}
	else if(_player->Getter_PlayerLife() <= 0){//�c�@�������Ȃ�����
		_player->SetPlayerFlag_Death(true);
		DrawString(Define::SCREEN_WIDTH / 2, Define::SCREEN_HEIGHT / 2, "Game Over", Define::WHITE);
		DrawString(Define::SCREEN_WIDTH / 2, Define::SCREEN_HEIGHT / 2 + 15, "Continue is Space", Define::WHITE);

		//�X�y�[�X�������ꂽ��R���e�B�j���[
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_SPACE) == 1) {
			//player�̏I���Ə���������
			_player->Finalize();
			_player.reset();
			_player = std::make_shared<Player>(Define::PLAYER_INIX, Define::PLAYER_INIY);
			_player->Initialize();
		}
	}
	else if (blockMgr->Getter_LiveNum() <= 0) {//block��S�ď�������
		DrawString(Define::SCREEN_WIDTH / 2, Define::SCREEN_HEIGHT / 2, "Game Clear!", Define::WHITE);
		DrawString(Define::SCREEN_WIDTH / 2, Define::SCREEN_HEIGHT / 2 + 15, "Restart is Spece", Define::WHITE);

		////�X�y�[�X�������ꂽ�烊�X�^�[�g
		// ������StageScene�ł��
		//if (Keyboard::getIns()->getPressingCount(KEY_INPUT_SPACE) == 1) {
		//	//player�̏I���Ə���������
		//	_player->Finalize();
		//	_player.reset();
		//	_player = std::make_shared<Player>(Define::PLAYER_INIX, Define::PLAYER_INIY);
		//	_player->Initialize();

		//	_ball->Finalize();
		//	_ball.reset();
		//	_ball = std::make_shared<Ball>(_player->GetterPosX() + _player->GetterWidth() / 2, _player->GetterPosY() - Define::BALL_RADIUS);
		//	_ball->Initialize();

		//	blockMgr->Finalize();
		//	blockMgr.reset();
		//	blockMgr = std::make_shared<BlockMgr>();
		//	blockMgr->Initialize();
		//}
	}

	
}

void GameMgr::Draw() const {
	if (!_player->CheckFlag((int)Player::fPlayer::_death)) {
		_player->Draw();
		_ball->Draw();
	}
	

	for (int i = 0; i < _player->Getter_PlayerLife(); i++) {
		DrawString(i*15, 10, "��", Define::WHITE);
	}
}

bool GameMgr::Call_ColRectangleAndBall(std::shared_ptr<RectangleObject> rectangle, std::shared_ptr<Ball> ball) {

	//�����̕ǂɓ�����ΐ����ɒ��˕Ԃ�.�����D��.
	if (colMgr.ColHori_RectAndBall(*rectangle, *ball)) {
		ball->ReflectBlock_Vertical(rectangle);
		return true;
	}

	//�����̕ǂɓ�����ΐ����ɒ��˕Ԃ�
	if (colMgr.ColVert_RectAndBall(*rectangle, *ball)) {
		ball->ReflectBlock_Horizontal(rectangle);
		return true;
	}

	return false;
}

Vector2<float> GameMgr::GetterPlayerPosition() const {
	return _player->GetterPosition();
}