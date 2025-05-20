#include "GravityBehavior.h"
#include "Bullet.h"

void GravityBehavior::Update(Bullet& bullet) {
	float vx = cosf(bullet.GetterAngle()) * bullet.GetterSpeed();
	float vy = sinf(bullet.GetterAngle()) * bullet.GetterSpeed() + 0.2f * bullet.GetterCnt();	//èdóÕâ¡ë¨ìx
	bullet.SetterVelocity(Vector2<float>(vx, vy));
}