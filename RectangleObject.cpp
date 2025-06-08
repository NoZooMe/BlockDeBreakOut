#include "RectangleObject.h"
#include <DxLib.h>
#include "Define.h"
#include <cmath>

RectangleObject::RectangleObject(float x, float y, int _width, int _height) : ShapeObject(x, y), _width(_width), _height(_height){
	float halfwidth = _width / 2.0f;
	float halfheight = _height / 2.0f;

	//����A�E��A�E���A����(���v���)
	vertex[0] = Vector2<float>(x-halfwidth, y-halfheight);
	vertex[1] = Vector2<float>(x+halfwidth, y-halfheight);
	vertex[2] = Vector2<float>(x+halfwidth, y+halfheight);
	vertex[3] = Vector2<float>(x-halfwidth, y+halfheight);

	//����
	vertSide1 = Segment(vertex[0], vertex[3]);
	//�E��
	vertSide2 = Segment(vertex[1], vertex[2]);
	//���
	horiSide1 = Segment(vertex[0], vertex[1]);
	//����
	horiSide2 = Segment(vertex[3], vertex[2]);

}

void RectangleObject::Update(){
	ShapeObject::Update();
	float halfwidth = _width / 2.0f;
	float halfheight = _height / 2.0f;

	Vector2<float> center = _position;

	//���[�J�����W�n�ł̒��_
	Vector2<float> local[4] = {
		{-halfwidth, -halfheight}, //����
		{ halfwidth, -halfheight}, //�E��
		{ halfwidth,  halfheight}, //�E��
		{-halfwidth,  halfheight}  //����
	};

	//��]�������ă��[���h���W�n�֕ϊ�
	for (int i = 0; i < 4; i++) {

		vertex[i] = center + local[i].RotateVector(_angle);
	}

	//������ӂ͂��������ȒP�ɂł��Ȃ��H
	vertSide1.UpdateSegment(vertex[0], vertex[3]);
	vertSide2.UpdateSegment(vertex[1], vertex[2]);
	horiSide1.UpdateSegment(vertex[0], vertex[1]);
	horiSide2.UpdateSegment(vertex[3], vertex[2]);

	
}

void RectangleObject::Draw() const {
	DrawLine(vertex[0].GetterX(), vertex[0].GetterY(), vertex[1].GetterX(), vertex[1].GetterY(), _color);
	DrawLine(vertex[1].GetterX(), vertex[1].GetterY(), vertex[2].GetterX(), vertex[2].GetterY(), _color);
	DrawLine(vertex[2].GetterX(), vertex[2].GetterY(), vertex[3].GetterX(), vertex[3].GetterY(), _color);
	DrawLine(vertex[3].GetterX(), vertex[3].GetterY(), vertex[0].GetterX(), vertex[0].GetterY(), _color);
}
