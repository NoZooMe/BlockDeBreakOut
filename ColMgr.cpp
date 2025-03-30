#include "ColMgr.h"
#include <cmath>
#include "DxLib.h"

bool ColMgr::ColVert_RectAndBall(const RectangleObject& rect,const CircleObject& ball) const  {

	if (Col_SegmentAndBall(rect.vertSide1, ball) || Col_SegmentAndBall(rect.vertSide2, ball)) {
		return true;
	}

	return false;
}

bool ColMgr::ColHori_RectAndBall(const RectangleObject& rect, const CircleObject& ball) const {
	if (Col_SegmentAndBall(rect.horiSide1, ball) || Col_SegmentAndBall(rect.horiSide2, ball)) {
		return true;
	}

	return false;
}

bool ColMgr::Col_SegmentAndBall(const Segment& segment, const CircleObject& ball) const {
	//�����̎n�_����I�_�ւ̃x�N�g���ƁA�����̎n�_����~�̒��S�ւ̃x�N�g�������
	Vector2<float> vectorA = segment.GetterSegVector();
	Vector2<float> vectorB = ball.GetterPosition() - segment.GetterBegVector();

	//���S�ƒ����Ƃ̍ŒZ����
	int dist = vectorB.CrossProd(vectorA.Norm());

	//�ŒZ���������a��菬������Ύ��̔����
	if (fabsf(dist) < ball.GetterR()) {
		//�����̏I�_����~�̒��S�ւ̃x�N�g�������
		Vector2<float> vectorC = ball.GetterPosition() - segment.GetterEndVector();

		//(A, B), (C, B)�̓��ς����߁A����������Ă���ΐڐG
		int dotProd1 = vectorB.DotProd(vectorA);
		int dotProd2 = vectorC.DotProd(vectorA);

		if ((dotProd1 * dotProd2) <= 0) {
			return true;
		}

		//�����̖��[�t�߂��������Ă��邩���ׂ�
		if (vectorB.Abs() < ball.GetterR() || vectorC.Abs() < ball.GetterR()) {
			return true;
		}

	}

	

	return false;
	
}

int ColMgr::Check_DistPointAndLine(const Vector2<float>& point, const Vector2<float>& lineBegin, const Vector2<float>& lineEnd) const {
	return 0;
}