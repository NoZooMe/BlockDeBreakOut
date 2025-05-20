#include "StraightBehavior.h"
#include "Bullet.h"

void StraightBehavior::Update(Bullet& bullet) {
    float angle = bullet.GetterAngle();
    int speed = bullet.GetterSpeed();
    bullet.SetterVelocity(Vector2<float>(cosf(angle), sinf(angle)).Mult(speed));
}