#pragma once
template<class T>

class Vector2
{
private:
	T x, y;
public:
	Vector2(T x, T y);

	//��{�I�Ƀ��[�U�[��`�^�̈����͎Q�Ɠn��

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

	//�Z�b�^
	void Setter(T dx, T dy) { x = dx; y = dy; };
	void SetterX(T dx) { x = dx; };
	void SetterY(T dy) { y = dy; };

	T GetterX() const { return x; };
	T GetterY() const { return y; };
};

