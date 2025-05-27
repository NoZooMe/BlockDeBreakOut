#include "BulletMgr.h"
#include "SoundManager.h"
#include "ResourceID.h"
#include "SinBehavior.h"
#include "StraightBehavior.h"
#include "SpiralBehavior.h"
#include "GravityBehavior.h"
#include "WeierstrassBehavior.h"

//#include <DxLib.h>

//DxLibはデバッグ用

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
	//イテレート中に要素を削除する場合は範囲for文は用いれない
	for (auto bullet : _vector) {
		bullet->Update();
	}
	CheckOut();
}

void BulletMgr::Draw() const {

	for (auto bullet : _vector) {
		bullet->Draw();
	}

}

void BulletMgr::Set_StraightBullet(eBulletSize size, const Vector2<float>& position, float angle, int speed, int color) {
	_vector.emplace_back(make_shared<Bullet>(position, angle, speed, make_shared<StraightBehavior>(), color, size));
	SoundManager::getIns()->play(toString(ResourceID::ShotBulletSE));
}

void BulletMgr::Set_SinBullet(eBulletSize size, const Vector2<float>& position, float angle, int speed, int color) {
	_vector.emplace_back(make_shared<Bullet>(position, angle, speed, make_shared<SinBehavior>(), color, size));
	SoundManager::getIns()->play(toString(ResourceID::ShotBulletSE));
}

void BulletMgr::Set_SpiralBullet(eBulletSize size, const Vector2<float>& position, float angle, int speed, int color) {
	_vector.emplace_back(make_shared<Bullet>(position, angle, speed, make_shared<SpiralBehavior>(), color, size));
	SoundManager::getIns()->play(toString(ResourceID::ShotBulletSE));
}

void BulletMgr::Set_GravityBullet(eBulletSize size, const Vector2<float>& position, float angle, int speed, int color) {
	_vector.emplace_back(make_shared<Bullet>(position, angle, speed, make_shared<GravityBehavior>(), color, size));
	SoundManager::getIns()->play(toString(ResourceID::ShotBulletSE));
}

void BulletMgr::Set_WeierstrassBullet(eBulletSize size, const Vector2<float>& position, float angle, int speed, int color) {
	_vector.emplace_back(make_shared<Bullet>(position, angle, speed, make_shared<WeierstrassBehavior>(), color, size));
	SoundManager::getIns()->play(toString(ResourceID::ShotBulletSE));
}

void BulletMgr::AddBullet(eBulletSize size, const Vector2<float> pos, float angle, int speed, int color, std::shared_ptr<IBulletBehavior> behavior) {
	_vector.emplace_back(std::make_shared<Bullet>(pos, angle, speed, behavior, color, size));
	SoundManager::getIns()->play(toString(ResourceID::ShotBulletSE));
}

void BulletMgr::CheckOut() {
	//コンテナを使う時はイテレータ破壊を念頭にいれておくこと。
	for (auto it = _vector.begin(); it != _vector.end();) {
		if (it->get()->CheckOut()) {
			it = _vector.erase(it);
		}
		else {
			it++;
		}
	}
}

shared_ptr<Bullet> BulletMgr::GetBullet(int i) const {
	return _vector.at(i);
};

int BulletMgr::GetBulletNum() const {
	return _vector.size();
}

void BulletMgr::DeleteBullet(int num) {
	_vector.erase(_vector.begin() + num);
}
