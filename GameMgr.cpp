#include "GameMgr.h"
#include "Player.h"
#include "Ball.h"
#include "BlockMgr.h"
#include "BulletMgr.h"
#include "ItemMgr.h"
#include "IGameLifecycleHandler.h"
#include "CollisitonEvent.h"
#include "Define.h"
#include "Keyboard.h"
#include "Macro.h"
#include "SoundManager.h"
#include "ResourceID.h"
#include "eItemName.h"
#include <DxLib.h>
#include <optional>
#include <random>

using namespace std;

GameMgr::GameMgr(IGameLifeCycleHandler* impl){
	_implLifeCycle = impl;
	_itemCnt = 0;
	_itemCntMax = 0;
	_isBombActive = false;
	_bombCoolCnt = 0;
	_dx = _dy = 0;
	_shakeScreenBuffer = MakeScreen(Define::SCREEN_WIDTH, Define::SCREEN_HEIGHT, TRUE);
	_isShake = false;
	_shakeTime = 0;
	_shakePower = 0;
	_shakeCnt = 0;
}

void GameMgr::Initialize() {
}

void GameMgr::Finalize() {
}

void GameMgr::Update(BlockMgr& blockMgr, BulletMgr& bulletMgr, ItemMgr& itemMgr, Player& player, Ball& ball, const std::vector<CollisionEvent>& evCol) {

	//�c�@������Ƃ��ƂȂ��Ƃ��ŕ���
	if (player.Getter_PlayerLife() > 0 && blockMgr.Getter_LiveNum() != 0) {//�c�@�����邩�N���A���ĂȂ��Ƃ�
		//��ʊO�����͊e�C���X�^���X�ɔC����.
		
		//�Փˏ���
		CollisionProcess(blockMgr, bulletMgr, itemMgr, player, ball, evCol);
		//Player�ɂ��҂���Ԃ�����Ă����炪���̂�flag��ON�݂̂ɂ���B
		//ball���҂���ԂȂ瓮���Ȃ��B�e���A�u���b�N�����l�B
		if (!ball.CheckFlag(static_cast<int>(Ball::fBall::_wait))) {
			player.Update();
			bulletMgr.Update();
			blockMgr.Update();
			itemMgr.Update();
		}

		if (ball.CheckFlag(static_cast<int>(Ball::fBall::_move))) {
			ball.Update();
		}
		else {//ball��player�ɒǏ]����Ƃ�
			ball.Update(player.GetterPosX(), player.GetterPosY() - (ball.GetterR()+Define::PLAYER_HEIGHT/2.0f));
		}

		//�{�[�������ɗ�������
		if (ball.CheckFlag(static_cast<int>(Ball::fBall::_out))) {
			_implLifeCycle->RequestDamage();
			player.CallDecLife();
		}

		//Bomb
		if (player.TryUseBomb()) {
			if (!_isBombActive) {
				_isBombActive = true;
				player.CallDecBomb();
				ShakeScreen(40, 20);
				
				for (int i = 0; i < bulletMgr.GetBulletNum(); ++i) {
					Vector2<float> temp = bulletMgr.GetBullet(i)->GetterPosition();
					itemMgr.Generate(eItemName::ScoreToPlayer, temp.GetterX(), temp.GetterY());
				}
			}
		}

		if (_isBombActive) {
			//�{�����Ԓ��͒e��������������
			bulletMgr.DeleteAllBullet();
			_bombCoolCnt++;
			itemMgr.SetPlayerPosition(player.GetterPosition());
			if (_bombCoolCnt >= Define::PLAYER_BOMBTIME * 60) {
				_bombCoolCnt = 0;
				_isBombActive = false;
			}
		}

		//ScreenShake
		if (_isShake) {
			_shakeCnt++;

			_dx = (rand() % _shakePower * 2) - _shakePower;
			_dy = (rand() % _shakePower * 2) - _shakePower;

			if (_shakeCnt >= _shakeTime) {
				_shakeCnt = 0;
				_isShake = false;
				_dx = _dy = 0;
			}
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
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_SPACE) == 1) {
			//player�̏I���Ə���������
			_implLifeCycle->RequestRestart();
		}
	}
}

void GameMgr::Draw(const BlockMgr& blockMgr, const BulletMgr& bulletMgr, const ItemMgr& itemMgr, const Player& player, const Ball& ball) const {
	if (!player.CheckFlag((int)Player::fPlayer::_death)) {

		SetDrawScreen(_shakeScreenBuffer);
		ClearDrawScreen();

		player.Draw();
		ball.Draw();
		blockMgr.Draw();
		bulletMgr.Draw();
		itemMgr.Draw();

		SetDrawScreen(DX_SCREEN_BACK);
		DrawGraph(_dx, _dy, _shakeScreenBuffer, TRUE);
	}
}

void GameMgr::CollisionProcess(BlockMgr& blockMgr, BulletMgr& bulletMgr, ItemMgr& itemMgr, Player& player, Ball& ball, const std::vector<CollisionEvent>& evCol) {
	for (const auto& ev : evCol) {
		switch (ev._type) {
		case eCollisionEvent::BallToPlayer:
			ball.ReflectFromSurface(*ev._surface, *ev._vector);
			break;
		case eCollisionEvent::BallToBlock:
			//PowerItem���ʒ��͔��˂��Ȃ�
			if (!ball.CheckFlag(static_cast<int>(Ball::fBall::_power))) {
				ball.ReflectFromSurface(*ev._surface, blockMgr.Getter_LiveBlock(ev._index)->GetterVelocity());
			}
			SoundManager::getIns()->play(toString(ResourceID::BreakBlockSE));
			player.AddScore(10);
			if (ItemGenerate(itemMgr, blockMgr, ev._index)) {
				//�����A�C�e�������̌��ʉ���
			}
			blockMgr.SetBlockFlag_Live(ev._index, false);
			break;
		case eCollisionEvent::BulletToPlayer:
			//���G�łȂ��Ȃ疳�G�t���O���I��
			if (!player.isDamaged()) {
				player.CallDecLife();
				SoundManager::getIns()->play(toString(ResourceID::DamageSE));
				player.DamagePlayer();
			}
			bulletMgr.DeleteBullet(ev._index);
			break;
		case eCollisionEvent::ItemToPlayer: {	//�ꎞ�ϐ����g���̂ŃX�R�[�v�𖾎��w��
			auto item = itemMgr.GetterItem(ev._index);
			if (!item) break; // nullptr

			ItemContext temp = { player, ball };
			//����ImmidiateItem�Ȃ�Cnt�ɒl������
			if (std::holds_alternative<ImmidiateItem>(itemMgr.GetterItem(ev._index)->GetterVariant())) {
				_itemCntMax = std::get<ImmidiateItem>(itemMgr.GetterItem(ev._index)->GetterVariant())._time;
			}
			itemMgr.CallEffect(ev._index, temp);
			break;
		}
		default:
			ERR("���݂��Ȃ������蔻��C�x���g�ł�");
			break;
		}
	}
}

bool GameMgr::ItemGenerate(ItemMgr& itemMgr, BlockMgr& blockMgr, int blockIndex) {
	std::random_device rd;		//�񌈒�I�ȏ�����
	std::mt19937 gen(rd());		//�����Z���k�E�c�C�^�X�^�Ő������������

	std::uniform_int_distribution<> dist(0, 100);

	int result = dist(gen);

	//Block�̈ʒu���擾
	float x = blockMgr.Getter_LiveBlock(blockIndex)->GetterPosX();
	float y = blockMgr.Getter_LiveBlock(blockIndex)->GetterPosY();

	if (result < 30) {
		itemMgr.Generate(eItemName::Score, x, y);
		return true;
	}
	else if (result >= 35 && result < 45) {
		itemMgr.Generate(eItemName::PowerUp, x, y);
		return true;
	}
	else if (result >= 45 && result < 50) {
		itemMgr.Generate(eItemName::Bomb, x, y);
		return true;
	}
	return false;

}

void GameMgr::ShakeScreen(int power, int duration) {
	_shakePower = power;
	_shakeTime = duration;
	_isShake = true;
}