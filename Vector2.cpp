#include "Vector2.h"
#include <cmath>

//テンプレートの明示的インスタンス化
template class Vector2<float>;
template class Vector2<int>;

template<typename T>

Vector2<T>::Vector2(T iniX, T iniY) : x(iniX), y(iniY) {

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
	T abs = std::sqrtf(x * x + y * y);
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
		Vector2<T> nor(x / abs, y / abs);
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