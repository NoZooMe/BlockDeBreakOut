#pragma once

#include"Vector2.h"


//線分クラス
class Segment
{
private:
	Vector2<float> begin;
	Vector2<float> end;

	Vector2<float> segment;

public:
	//Vector2のインストラクタを呼び出さないといけないのでfloatで引数を取る
	Segment(float beginX, float beginY, float endX, float endY);

	//点が線上にあるかどうかをbool値で返す
	bool CheckOnPoint(const Vector2<float>& point) const;

	//線分ベクトルを返す
	Vector2<float> GetterSegVector()const { return segment; }
	Vector2<float> GetterBegVector()const { return begin; }
	Vector2<float> GetterEndVector()const { return end; }

	void UpdateSegment(float beginX, float beginY, float endX, float endY);

	};

