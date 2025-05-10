#include "Vector2.h"
#include <cmath>

//テンプレートの明示的インスタンス化
template class Vector2<float>;
template class Vector2<int>;

template<typename T>
Vector2<T>::Vector2() :_x(0), _y(0) {

}

template<typename T>

Vector2<T>::Vector2(T iniX, T iniY) : _x(iniX), _y(iniY) {

}

template<typename T>

Vector2<T> Vector2<T>::operator+(const Vector2& vector) const{
	Vector2 addVec(this->GetterX() + vector.GetterX(), this->GetterY() + vector.GetterY());

	return addVec;
}

template<typename T>

Vector2<T> Vector2<T>::operator-(const Vector2& vector) const {
	Vector2 subVec(this->GetterX() - vector.GetterX(), this->GetterY() - vector.GetterY());

	return subVec;
}

template<typename T>

Vector2<T> Vector2<T>::Mult(const T scalar) const {
	Vector2<T> multVec(this->GetterX() * scalar, this->GetterY() * scalar);
	return multVec;
}

template<typename T>

T Vector2<T>::Abs() const {
	T abs = std::sqrtf(_x * _x + _y * _y);
	return abs;
}

template<typename T>

Vector2<T> Vector2<T>::Norm() const {
	float abs = Abs();

	//大きさが0のときとそうでない時で場合分け
	if (abs == 0) {
		Vector2<T> nor(0, 0);
		return nor;
	}
	else {
		Vector2<T> nor(_x / abs, _y / abs);
		return nor;
	}
}

template<typename T>

T Vector2<T>::CrossProd(const Vector2<T>& vector) const {
	T value = (this->GetterX() * vector.GetterY()) - (this->GetterY() * vector.GetterX());

	return value;
}

template<typename T>

T Vector2<T>::DotProd(const Vector2<T>& vector) const {
	T value = this->GetterX() * vector.GetterX() + this->GetterY() * vector.GetterY();

	return value;
}

template<typename T>
float Vector2<T>::GetterAngle() const {
	float ty = static_cast<float>(_y);
	float tx = static_cast<float>(_x);

	return atan2f(ty, tx);
}

template<typename T>
Vector2<T> Vector2<T>::RotateVector(float angle) const {
	//回転行列を作用
	T x = cosf(angle) * _x + -sinf(angle) * _y;
	T y = sinf(angle) * _x + cosf(angle) * _y;

	Vector2<T> rotateVector2(x, y);

	return rotateVector2;
}