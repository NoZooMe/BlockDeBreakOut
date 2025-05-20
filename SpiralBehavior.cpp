#include "SpiralBehavior.h"
#include "Bullet.h"

void SpiralBehavior::Update(Bullet& bullet) {
	const float spinSpeed = 0.05f;	//‰ñ“]‘¬“x
	const float baseSpeed = bullet.GetterSpeed();
	const float expandRate = 0.03f;		//”¼Œa‚Ì‘‰Á—Ê

	float cnt = static_cast<float>(bullet.GetterCnt());
	float angle = bullet.GetterAngle() + spinSpeed * cnt;
	float radius = baseSpeed * expandRate * cnt;

	Vector2<float> velocity = Vector2<float>(cosf(angle), sinf(angle)).Mult(radius);
	bullet.SetterVelocity(velocity);
}