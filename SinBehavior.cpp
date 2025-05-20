#include "SinBehavior.h"
#include "Bullet.h"

void SinBehavior::Update(Bullet& bullet) {
	int t = bullet.GetterCnt();
	float speed = bullet.GetterSpeed();
	float angle = bullet.GetterAngle();
	Vector2<float> base(speed, 10 * cosf(t / 10.0));
	bullet.SetterVelocity(base.RotateVector(angle));
}