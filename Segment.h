#pragma once
#include"Vector2.h"

//線分クラス
class Segment
{
private:
	Vector2<float> _begin;
	Vector2<float> _end;

	Vector2<float> segment;

public:
	Segment();
	Segment(float beginX, float beginY, float endX, float endY);
	Segment(Vector2<float> beginVector, Vector2<float> endVector);

	//点が線上にあるかどうかをbool値で返す
	bool CheckOnPoint(const Vector2<float>& point) const;

	//線分ベクトルを返す
	Vector2<float> GetterSegVector()const { return segment; }
	Vector2<float> GetterBegVector()const { return _begin; }
	Vector2<float> GetterEndVector()const { return _end; }

	void UpdateSegment(float beginX, float beginY, float endX, float endY);
	void UpdateSegment(Vector2<float> begin, Vector2<float> end);

	};

