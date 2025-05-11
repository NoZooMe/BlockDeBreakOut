#include "ColMgr.h"
#include "SoundManager.h"
#include "ResourceID.h"
#include <cmath>
#include <DxLib.h>

void ColMgr::Initialize() {

}

void ColMgr::Finalize() {

}

void ColMgr::Update(BlockMgr& blockMgr, BulletMgr& bulletMgr, Player& player, Ball& ball) {
	if (ball.CheckFlag((int)Ball::fBall::_move)) {
		//player��ball
		if (Col_RectAndBall(player, ball)) {
			ball.ReflectFromSurface(*Col_RectAndBall(player, ball), player.GetterVelocity());
		}
	}
	

	//block��ball
	for (int i = 0; i < Define::BLOCK_NUM; i++) {
		//�����Ă���Ȃ�
		if (blockMgr.Getter_LiveBlock(i) != nullptr) {//����Block�������Ă���Ȃ�
			if (Col_RectAndBall(*blockMgr.Getter_LiveBlock(i), ball)) {//����������
				ball.ReflectFromSurface(*Col_RectAndBall(*blockMgr.Getter_LiveBlock(i), ball), blockMgr.Getter_LiveBlock(i)->GetterVelocity());
				blockMgr.SetBlockFlag_Live(i, false);
				SoundManager::getIns()->play(toString(ResourceID::BreakBlockSE));
			}
		}
	}

	//bullet��player
	for (int i = 0; i < bulletMgr.GetBulletNum(); i++) {
		//������ӁA�|�C���^�ƎQ�Ƃ��������ĂăJ�I�X
		if (Col_RectAndBall(player, *bulletMgr.GetBullet(i))) {
			//���G�łȂ��Ȃ疳�G�t���O���I��
			if (!player.isDamaged()) {
				player.CallDecLife();
				SoundManager::getIns()->play(toString(ResourceID::DamageSE));
				player.DamagePlayer();
			}
			bulletMgr.DeleteBullet(i);
		}
	}

}


std::optional<Segment> ColMgr::Col_RectAndBall(const RectangleObject& rect, const CircleObject& ball) const {
	//������rect���z��ŕӂ�ێ����Ă�������������Z��������
	if (Col_SegmentAndBall(rect.vertSide1, ball)) {
		return rect.vertSide1;
	}
	if (Col_SegmentAndBall(rect.vertSide2, ball)) {
		return rect.vertSide2;
	}
	if (Col_SegmentAndBall(rect.horiSide1, ball)) {
		return rect.horiSide1;
	}
	if(Col_SegmentAndBall(rect.horiSide2, ball)) {
		return rect.horiSide2;
	}

	return std::nullopt;
}

bool ColMgr::Col_SegmentAndBall(const Segment& segment, const CircleObject& ball) const {
	//�����̎n�_����I�_�ւ̃x�N�g���ƁA�����̎n�_����~�̒��S�ւ̃x�N�g�������
	Vector2<float> vectorA = segment.GetterSegVector();
	Vector2<float> vectorB = ball.GetterPosition() - segment.GetterBegVector();

	//A�ɑ΂���B�̊O��(�X�J���[)�B���S�ƒ����Ƃ̍ŒZ����
	int dist = vectorB.CrossProd(vectorA.Norm());

	//�ŒZ���������a��菬������Ύ��̔����
	if (fabsf(dist) < ball.GetterR()) {
		//�����̏I�_����~�̒��S�ւ̃x�N�g�������
		Vector2<float> vectorC = ball.GetterPosition() - segment.GetterEndVector();

		//(A, B), (C, B)�̓��ς����߁A�������قȂ�ΐ�����ɐ����������Ă���
		float dotProd1 = vectorB.DotProd(vectorA);
		float dotProd2 = vectorC.DotProd(vectorA);

		//�����������蔻�肪�������������炱�����������āAif���̒��g��sing1*sing2<0�ɁB
		////��������B�قȂ�Ȃ�-1�B�����Ȃ�1
		//int sign1 = (dotProd1 > 0) - (dotProd1 < 0);
		//int sign2 = (dotProd2 > 0) - (dotProd2 < 0);

		if (dotProd1 * dotProd2 < 0.0f) {
			return true;
		}

		//�����̖��[�t�߂��������Ă��邩���ׂ�
		if (vectorB.Abs() < ball.GetterR() || vectorC.Abs() < ball.GetterR()) {
			return true;
		}

	}
	return false;
	
}
