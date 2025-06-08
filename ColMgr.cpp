#define NOMINMAX
#include "ColMgr.h"

#include "RectangleObject.h"
#include "CircleObject.h"
#include "Player.h"
#include "Ball.h"
#include "BulletMgr.h"
#include "BlockMgr.h"
#include "ItemMgr.h"
#include "CollisitonEvent.h"
#include <cmath>
#include <algorithm>
#include <DxLib.h>

void ColMgr::Initialize() {

}

void ColMgr::Finalize() {

}

void ColMgr::Update(BlockMgr& blockMgr, BulletMgr& bulletMgr, ItemMgr& itemMgr, Player& player, Ball& ball, std::vector<CollisionEvent>& evCol) {
	if (ball.CheckFlag((int)Ball::fBall::_move)) {
		//player��ball
		if (Col_RectAndBall(player, ball)) {
			CollisionEvent t = {eCollisionEvent::BallToPlayer, -1, player.GetterVelocity(), Col_RectAndBall(player, ball)};
			evCol.push_back(t);
		}
	}
	
	//block��ball
	for (int i = 0; i < Define::BLOCK_NUM; ++i) {
		//�����Ă���Ȃ�
		if (blockMgr.Getter_LiveBlock(i) != nullptr) {//����Block�������Ă���Ȃ�
			if (Col_RectAndBall(*blockMgr.Getter_LiveBlock(i), ball)) {//����������
				CollisionEvent t = { eCollisionEvent::BallToBlock, i, blockMgr.Getter_LiveBlock(i)->GetterVelocity(), Col_RectAndBall(*blockMgr.Getter_LiveBlock(i), ball) };
				evCol.push_back(t);
			}
		}
	}

	//bullet��player
	for (int i = 0; i < bulletMgr.GetBulletNum(); ++i) {
		//������ӁA�|�C���^�ƎQ�Ƃ��������ĂăJ�I�X
		if (Col_RectAndBall(player, *bulletMgr.GetBullet(i))) {
			CollisionEvent t = { eCollisionEvent::BulletToPlayer, i};
			evCol.push_back(t);
		}
	}

	//ball��bullet
	for (int i = 0; i < bulletMgr.GetBulletNum(); ++i) {
		if (Col_BallAndBall(ball, *bulletMgr.GetBullet(i))) {
			CollisionEvent t = { eCollisionEvent::BallToBullet, i };
			evCol.push_back(t);
		}
	}

	//item��player
	for (int i = 0; i < itemMgr.GetArrayNum(); ++i) {
		std::vector<Vector2<float>> playerVert = player.GetterVertexs();
		std::vector<Vector2<float>> itemVert = itemMgr.GetterItem(i)->GetterVertexs();
		if (SAT_Intersect(playerVert, itemVert)) {
			CollisionEvent t = { eCollisionEvent::ItemToPlayer, i };
			evCol.push_back(t);
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

//bool ColMgr::Col_RectAndRect(const RectangleObject& rect1, const RectangleObject& rect2) const {
//	
//}

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

bool ColMgr::SAT_Intersect(const std::vector<Vector2<float>>& polyA, const std::vector<Vector2<float>>& polyB) {
	std::vector<Vector2<float>> axes;

	// A�̕�
	for (size_t i = 0; i < polyA.size(); ++i) {
		//�Ō��1�ӂ͍ŏ��̒��_���I�_
		Vector2<float> edge = polyA[(i + 1) % polyA.size()] - polyA[i];
		axes.push_back(Vector2<float>(-edge.GetterY(), edge.GetterX()).Norm());	//�P�ʖ@���x�N�g��
	}
	// B�̕�
	for (size_t i = 0; i < polyB.size(); ++i) {
		Vector2<float> edge = polyB[(i + 1) % polyB.size()] - polyB[i];
		axes.push_back(Vector2<float>(-edge.GetterY(), edge.GetterX()).Norm());
	}

	//�e���œ��e���A��Ԃ��������Ă��Ȃ����m�F
	for (const auto& axis : axes) {
		float minA, maxA, minB, maxB;
		ProjectPolygon(polyA, axis, minA, maxA);
		ProjectPolygon(polyB, axis, minB, maxB);

		//�ˉe���������Ă���Ȃ�Փ˂��Ă��Ȃ�
		if (maxA < minB || maxB < minA) {
			return false;
		}
	}
	//�S�Ă̎��ŏd�Ȃ��Ă��遨�Փ�
	return true;
}

bool ColMgr::Col_BallAndBall(const CircleObject& circle1, const CircleObject& circle2) const {
	Vector2<float> diff = circle2.GetterPosition() - circle1.GetterPosition();

	//�����̓��(�������̓R�X�g�������ד��ς�)
	float dist = diff.DotProd(diff);

	float sumRadius = circle1.GetterR() + circle2.GetterR();

	return dist <= sumRadius * sumRadius;

}

bool ColMgr::Col_SegmentAndSegment(const Segment& segment1, const Segment& segment2) const{
	//segment1�𒼐�AB, segment2�𒼐�CD�Ƃ���
	Vector2<float> AB = segment1.GetterSegVector();
	Vector2<float> AC = segment2.GetterBegVector() - segment1.GetterBegVector();
	Vector2<float> AD = segment2.GetterEndVector() - segment1.GetterBegVector();

	Vector2<float> CD = segment2.GetterSegVector();
	Vector2<float> CA = segment1.GetterBegVector() - segment2.GetterBegVector();
	Vector2<float> CB = segment1.GetterEndVector() - segment2.GetterBegVector();

	float cross1 = AB.CrossProd(AC);
	float cross2 = AB.CrossProd(AD);
	float cross3 = CD.CrossProd(CA);
	float cross4 = CD.CrossProd(CB);

	//AC, AD��sin�̐����ɒ��ځB���ꂪ�|�ł���Β���CD�͓_A���ׂ��ő��݂��Ă���B
	//CA, CB��sin�̐��������킹�邱�ƂŐ������m�̓����蔻��ɂȂ�B
	return (cross1 * cross2 < 0) && (cross3 * cross4 < 0);
}

void ColMgr::ProjectPolygon(const std::vector<Vector2<float>>& vertices, const Vector2<float>& axis, float& min, float& max) {
	//���_�̎��ւ̎ˉe
	min = vertices[0].DotProd(axis);
	max = vertices[0].DotProd(axis);
	//�ˉe��������
	for (const auto& v : vertices) {
		float proj = v.DotProd(axis);
		min = std::min(min, proj);
		max = std::max(max, proj);

	}
}