#include "GameMgr.h"
#include "Define.h"
#include "Keyboard.h"
#include "Macro.h"
#include <DxLib.h>
#include <optional>

using namespace std;

GameMgr::GameMgr(IGameLifeCycleHandler* impl){
	_implLifeCycle = impl;
}

void GameMgr::Initialize() {
}

void GameMgr::Finalize() {
}

void GameMgr::Update(BlockMgr& blockMgr, BulletMgr& bulletMgr, Player& player, Ball& ball) {

	//�c�@������Ƃ��ƂȂ��Ƃ��ŕ���
	if (player.Getter_PlayerLife() > 0 && blockMgr.Getter_LiveNum() != 0) {//�c�@�����邩�N���A���ĂȂ��Ƃ�
		//��ʊO�����͊e�C���X�^���X�ɔC����.
		
		//Player�ɂ��҂���Ԃ�����Ă����炪���̂�flag��ON�݂̂ɂ���B
		//ball���҂���ԂȂ瓮���Ȃ��B�e���A�u���b�N�����l�B
		if (!ball.CheckFlag((int)Ball::fBall::_wait)) {
			player.Update();
			bulletMgr.Update();
			blockMgr.Update();
		}

		if (ball.CheckFlag((int)Ball::fBall::_move)) {
			ball.Update();
		}
		else {//ball��player�ɒǏ]����Ƃ�
			ball.Update(player.GetterPosX(), player.GetterPosY() - (ball.GetterR()+Define::PLAYER_HEIGHT/2.0f));
			if (Keyboard::getIns()->getPressingCount(KEY_INPUT_SPACE) != 0) {

			}

		}

		//�{�[�������ɗ�������
		if (ball.CheckFlag((int)Ball::fBall::_out)) {
			_implLifeCycle->RequestDamage();
			player.CallDecLife();
		}

	}
	else if(player.Getter_PlayerLife() <= 0){//�c�@�������Ȃ�����
		player.SetPlayerFlag_Death(true);
		DrawString(Define::SCREEN_WIDTH / 2, Define::SCREEN_HEIGHT / 2, "Game Over", Define::WHITE);
		DrawString(Define::SCREEN_WIDTH / 2, Define::SCREEN_HEIGHT / 2 + 15, "Continue is Space", Define::WHITE);

		//�X�y�[�X�������ꂽ��R���e�B�j���[
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_SPACE) == 1) {
			//player�̏I���Ə���������
			_implLifeCycle->RequestContinue();
		}
	}
	else if (blockMgr.Getter_LiveNum() <= 0) {//block��S�ď�������
		DrawString(Define::SCREEN_WIDTH / 2, Define::SCREEN_HEIGHT / 2, "Game Clear!", Define::WHITE);
		DrawString(Define::SCREEN_WIDTH / 2, Define::SCREEN_HEIGHT / 2 + 15, "Restart is Spece", Define::WHITE);

		_implLifeCycle->RequestClear();

		//�X�y�[�X�������ꂽ�烊�X�^�[�g
		 //������StageScene�ł��
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_SPACE) == 1) {
			//player�̏I���Ə���������
			_implLifeCycle->RequestRestart();
		}
	}

	
}

void GameMgr::Draw(const BlockMgr& blockMgr, const BulletMgr& bulletMgr, const Player& player, const Ball& ball) const {
	if (!player.CheckFlag((int)Player::fPlayer::_death)) {
		player.Draw();
		ball.Draw();
		blockMgr.Draw();
		bulletMgr.Draw();
	}
	

	for (int i = 0; i < player.Getter_PlayerLife(); i++) {
		DrawString(i*15, 10, "��", Define::WHITE);
	}
	DrawFormatString(0, 25, Define::WHITE, "%d", player.Getter_PlayerScore());
}