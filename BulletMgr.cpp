#include "BulletMgr.h"
#include "SmallBullet.h"

using namespace std;

BulletMgr::BulletMgr(){

}

void BulletMgr::Initialize() {
	for (auto bullet : _vector) {
		bullet->Initialize();
	}
}

void BulletMgr::Finalize() {
	for (auto bullet : _vector) {
		bullet->Finalize();
	}
}

void BulletMgr::Update() {
	for (auto bullet : _vector) {
		bullet->Update();
	}
}

void BulletMgr::Draw() const {
	for (auto bullet : _vector) {
		bullet->Draw();
	}
}

void BulletMgr::Set_StraightSmallBullet(const Vector2<float>& position, const Vector2<float>& direction, int speed, int color) {
	_vector.emplace_back(make_shared<SmallBullet>(position, direction, speed, 1, color));
}

void BulletMgr::Set_SinSmallBullet(const Vector2<float>& position, const Vector2<float>& direction, int speed, int color) {
	_vector.emplace_back(make_shared<SmallBullet>(position, direction, speed, 2, color));
}