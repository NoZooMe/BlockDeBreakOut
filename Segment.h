#pragma once

#include"Vector2.h"


//�����N���X
class Segment
{
private:
	Vector2<float> begin;
	Vector2<float> end;

	Vector2<float> segment;

public:
	//Vector2�̃C���X�g���N�^���Ăяo���Ȃ��Ƃ����Ȃ��̂�float�ň��������
	Segment(float beginX, float beginY, float endX, float endY);

	//�_������ɂ��邩�ǂ�����bool�l�ŕԂ�
	bool CheckOnPoint(const Vector2<float>& point) const;

	//�����x�N�g����Ԃ�
	Vector2<float> GetterSegVector()const { return segment; }
	Vector2<float> GetterBegVector()const { return begin; }
	Vector2<float> GetterEndVector()const { return end; }

	void UpdateSegment(float beginX, float beginY, float endX, float endY);

	};

