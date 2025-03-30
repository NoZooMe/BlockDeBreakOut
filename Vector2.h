#pragma once
template<class T>

class Vector2
{
private:
	T x, y;
public:
	Vector2(T x, T y);

	//基本的にユーザー定義型の引数は参照渡し

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

	//セッタ
	void Setter(T dx, T dy) { x = dx; y = dy; };
	void SetterX(T dx) { x = dx; };
	void SetterY(T dy) { y = dy; };

	T GetterX() const { return x; };
	T GetterY() const { return y; };
};

