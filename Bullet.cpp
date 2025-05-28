#include "Bullet.h"
#include "Macro.h"
#include "Define.h"
#include "ComplexTransform.h"
#include "DxLib.h"
#include <cmath>

Bullet::Bullet(const Vector2<float>& position, float angle, int speed, std::shared_ptr<IBulletBehavior> b, int color, eBulletSize size)
	: CircleObject(position.GetterX(), position.GetterY(), 0), _speed(speed), _color(color),  _cnt(0), _behavior(b), _euclidPosition(_position){
	//全てのshapeObjectの角度はインスタンスで初期化されるべき。
	_angle = angle;

	//まずコンストラクタ使ってrを初期化してから代入し直すってものなんか変な気がするけど……。
	switch (size) {
	case eBulletSize::Small :
		_r = Define::BULLET_SIZE_SMALL;
		break;
	case eBulletSize::Midium:
		_r = Define::BULLET_SIZE_MIDIUM;
		break;
	case eBulletSize::Large:
		_r = Define::BULLET_SIZE_BIG;
		break;
	default:
		ERR("存在しない弾幕の大きさです");
		break;
	}

}

void Bullet::Initialize() {

}

void Bullet::Finalize() {

}

void Bullet::Update() {
	_behavior->Update(*this);	// _velocityを更新する

	//ユークリッド空間上で移動
	_euclidPosition = _euclidPosition + _velocity;
	

	//中心位置
	float cx = Define::SCREEN_WIDTH / 2.0f;
	float cy = Define::SCREEN_HEIGHT / 2.0f;

	float scale = 80.0f;

	// 画面座標 → 複素座標（中心が原点）
	std::complex<float> z((_euclidPosition.GetterX() - cx) / scale,
		-(_euclidPosition.GetterY() - cy) / scale);  // y軸反転

	// 2. 微小 z を補正（極回避）
	const float epsilon = 1e-2f;
	if (std::abs(z) < epsilon) {
		float theta = std::arg(z);
		z = std::polar(epsilon, theta); // εの距離に置き換える
	}

	// 3. 複素変換 f(z)
	std::complex<float> z_trans = ComplexTransform::Apply(z);

	// 4. f(z) が大きすぎるときは logスケール or clamp
	float mag = std::abs(z_trans);
	float maxMag = 10.0f;  // スケール前の最大許容値（調整可）

	if (mag > maxMag) {
		// logスケーリングで収める（滑らか）
		float scaledMag = std::log(1.0f + mag);
		z_trans = std::polar(scaledMag, std::arg(z_trans));
	}

	
	//変換後の位置に反映(ShapeObjectの描画・当たり判定用)

	_position.Setter(cx + z_trans.real() * scale, cy - z_trans.imag() * scale);

	ShapeObject::Update();
	_cnt++;

}

void Bullet::Draw() const{
	CircleObject::Draw();
}

bool Bullet::CheckOut() {
	if (_position.GetterX() + GetterR() <= 0 || _position.GetterX() - GetterR() >= Define::SCREEN_WIDTH
		|| _position.GetterY() + GetterR() <= 0 || _position.GetterY() - GetterR() >= Define::SCREEN_HEIGHT ) {
		return true;
	}
	else if(_euclidPosition.GetterX() + GetterR() <= 0 || _euclidPosition.GetterX() - GetterR() >= Define::SCREEN_WIDTH
		|| _euclidPosition.GetterY() + GetterR() <= 0 || _euclidPosition.GetterY() - GetterR() >= Define::SCREEN_HEIGHT)
	{
		return true;
	}
	else 
	{
		return false;
	}
}