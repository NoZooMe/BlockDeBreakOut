#include "WeierstrassBehavior.h"
#include "Bullet.h"
#include "Define.h"

void WeierstrassBehavior::Update(Bullet& bullet) {
	float x = bullet.GetterCnt() / 10.0f;
	float y = 0.0f;
	const float a = 0.5f, b = 3.0f;
	for (int n = 0; n < 10; ++n) {
		y += powf(a, n) * cosf(powf(b, n) * Define::PI * x);
	}
	Vector2<float> dir = Vector2<float>(1.0f, y).Norm();
	bullet.SetterVelocity(dir.Mult(bullet.GetterSpeed()));
}