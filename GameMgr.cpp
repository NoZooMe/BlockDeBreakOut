#include "GameMgr.h"
#include "Def.h"
#include "KeyBoard.h"


GameMgr::GameMgr() : player(std::make_shared<Player>(PLAYER_INIX, PLAYER_INIY)), ball(std::make_shared<Ball>(BALL_INIX, BALL_INIY)), blockMgr(std::make_shared<BlockMgr>()){
	
}

void GameMgr::Init() {
	player->Init();
	ball->Init();
	blockMgr->Init();
}

void GameMgr::Fin() {
	player->Fin();
	ball->Fin();
	blockMgr->Fin();
}

void GameMgr::Update() {
	//Singleton��Keyboard���X�V
	KeyBoard::Instance()->Update();

	//�c�@������Ƃ��ƂȂ��Ƃ��ŕ���
	if (player->Getter_PlayerLife() > 0 && blockMgr->Getter_LiveNum() != 0) {//�c�@�����邩�N���A���ĂȂ��Ƃ�
		//��ʊO�����͊e�C���X�^���X�ɔC����.

		//�Փ˔��蕔
		//Player��Ball���������Ă���Γ`����
		Call_ColRectangleAndBall(player, ball);
		//Block��Ball�̓����蔻��
		for (int i = 0; i < BLOCK_NUM; i++) {
			//�����Ă���Ȃ�
			if (blockMgr->Getter_LiveBlock(i) != nullptr) {//nullptr�֗������ǂ���Ȃ��Ƃ���Ă���?
				if (Call_ColRectangleAndBall(blockMgr->Getter_LiveBlock(i), ball)) {//����������
					blockMgr->SetBlockFlag_Live(i, false);
				}
			}
		}

		blockMgr->Update();
		//ball���҂���ԂȂ瓮���Ȃ�
		if (!ball->CheckFlag((int)Ball::fBall::_wait)) {
			player->Update();
		}
		if (ball->CheckFlag((int)Ball::fBall::_move)) {
			ball->Update();
		}
		else {//ball��player�ɒǏ]����Ƃ�
			ball->Update(player->GetterPosX() + player->GetterWidth() / 2, player->GetterPosY() - (ball->GetterR()));
			if (KeyBoard::Instance()->GetPressingCount(KEY_INPUT_SPACE) != 0) {

			}

		}

		//�{�[�������ɗ�������
		if (ball->CheckFlag((int)Ball::fBall::_out)) {
			ball->Fin();
			//�C���X�^���X�ւ̃|�C���^�����
			ball.reset();
			player->CallDecLife();

			//�V�����|�C���^����
			ball = std::make_shared<Ball>(player->GetterPosX() + player->GetterWidth() / 2, player->GetterPosY() - BALL_RADIUS);
			ball->Init();
		}
	}
	else if(player->Getter_PlayerLife() <= 0){//�c�@�������Ȃ�����
		player->SetPlayerFlag_Death(true);
		DrawString(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, "Game Over", WHITE);
		DrawString(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 15, "Continue is Space", WHITE);

		//�X�y�[�X�������ꂽ��R���e�B�j���[
		if (KeyBoard::Instance()->GetPressingCount(KEY_INPUT_SPACE) == 1) {
			//player�̏I���Ə���������
			player->Fin();
			player.reset();
			player = std::make_shared<Player>(PLAYER_INIX, PLAYER_INIY);
			player->Init();
		}
	}
	else if (blockMgr->Getter_LiveNum() <= 0) {//block��S�ď�������
		DrawString(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, "Game Clear!", WHITE);
		DrawString(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 15, "Restart is Spece", WHITE);

		//�X�y�[�X�������ꂽ�烊�X�^�[�g
		if (KeyBoard::Instance()->GetPressingCount(KEY_INPUT_SPACE) == 1) {
			//player�̏I���Ə���������
			player->Fin();
			player.reset();
			player = std::make_shared<Player>(PLAYER_INIX, PLAYER_INIY);
			player->Init();

			ball->Fin();
			ball.reset();
			ball = std::make_shared<Ball>(player->GetterPosX() + player->GetterWidth() / 2, player->GetterPosY() - BALL_RADIUS);
			ball->Init();

			blockMgr->Fin();
			blockMgr.reset();
			blockMgr = std::make_shared<BlockMgr>();
			blockMgr->Init();
		}
	}

	
}

void GameMgr::Draw() const {
	if (!player->CheckFlag((int)Player::fPlayer::_death)) {
		player->Draw();
		blockMgr->Draw();
		ball->Draw();
	}
	

	for (int i = 0; i < player->Getter_PlayerLife(); i++) {
		DrawString(i*15, 10, "��", WHITE);
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
