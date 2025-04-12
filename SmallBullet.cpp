#include "SmallBullet.h"
#include "Define.h"

SmallBullet::SmallBullet(const Vector2<float>& position, const Vector2<float>& direction, int speed, int pattern, int color) :
	AbstractBullet(position, direction, speed, pattern, color, Define::BULLET_SIZE_SMALL){

}

void SmallBullet::Initialize() {
	
}

void SmallBullet::Finalize() {

}

void SmallBullet::Update() {
	AbstractBullet::Update();
}

void SmallBullet::Draw() const {
	CircleObject::Draw();
}