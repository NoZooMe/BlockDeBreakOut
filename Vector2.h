#pragma once
template<class T>

class Vector2
{
private:
	T _x, _y;
public:
	Vector2();
	Vector2(T x, T y);
	Vector2(const Vector2<T>& other);


	//�����Z, �����Z
	Vector2 operator+(const Vector2& vector) const;
	Vector2	operator-(const Vector2& vector) const;
	//�X�J���[�{
	Vector2 Mult(const T scalar) const;
	//��Βl��Ԃ�
	T Abs() const;
	//�O��(2����, ���s�l�ӌ`�̖ʐ�)��Ԃ�
	T CrossProd(const Vector2& vector) const;
	//���ς�Ԃ�
	T DotProd(const Vector2& vector) const;

	//���K�����ꂽ�x�N�g����Ԃ�
	Vector2 Norm() const;

	//�p�x(radian)��Ԃ�(x������y��������)
	float GetterAngle() const;

	//���g��radian������]�������x�N�g����Ԃ�
	Vector2 RotateVector(float angle) const;

	//�Z�b�^
	void Setter(T dx, T dy) { _x = dx; _y = dy; };
	void SetterX(T dx) { _x = dx; };
	void SetterY(T dy) { _y = dy; };

	T GetterX() const { return _x; };
	T GetterY() const { return _y; };
};

