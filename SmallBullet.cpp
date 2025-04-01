#include "SmallBullet.h"
#include "Define.h"

SmallBullet::SmallBullet(const Vector2<float>& position, int speed, int color, int pattern, const Player& player) : 
	AbstractBullet(position, speed, Define::BULLET_SIZE_SMALL, color, pattern, player){

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