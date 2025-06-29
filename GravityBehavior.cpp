#include "GravityBehavior.h"
#include "Bullet.h"

void GravityBehavior::Update(Bullet& bullet) {
	float vx = cosf(bullet.GetterAngle()) * bullet.GetterSpeed();
	float vy = sinf(bullet.GetterAngle()) * bullet.GetterSpeed() + 0.2f * bullet.GetterCnt();	//重力加速度
	bullet.SetterVelocity(Vector2<float>(vx, vy));
}