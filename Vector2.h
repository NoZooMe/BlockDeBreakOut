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


	//足し算, 引き算
	Vector2 operator+(const Vector2& vector) const;
	Vector2	operator-(const Vector2& vector) const;
	//スカラー倍
	Vector2 Mult(const T scalar) const;
	//絶対値を返す
	T Abs() const;
	//外積(2次元, 平行四辺形の面積)を返す
	T CrossProd(const Vector2& vector) const;
	//内積を返す
	T DotProd(const Vector2& vector) const;

	//正規化されたベクトルを返す
	Vector2 Norm() const;

	//角度(radian)を返す(x軸からy軸正方向)
	float GetterAngle() const;

	//自身をradianだけ回転させたベクトルを返す
	Vector2 RotateVector(float angle) const;

	//セッタ
	void Setter(T dx, T dy) { _x = dx; _y = dy; };
	void SetterX(T dx) { _x = dx; };
	void SetterY(T dy) { _y = dy; };

	T GetterX() const { return _x; };
	T GetterY() const { return _y; };
};

