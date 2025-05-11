#include "BulletMgr.h"
#include "SoundManager.h"
#include "ResourceID.h"

//#include <DxLib.h>

//DxLib�̓f�o�b�O�p

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
	//�C�e���[�g���ɗv�f���폜����ꍇ�͔͈�for���͗p����Ȃ�
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
	_vector.emplace_back(make_shared<Bullet>(position, angle, speed, 1, color, size));
	SoundManager::getIns()->play(toString(ResourceID::ShotBulletSE));
}

void BulletMgr::Set_SinBullet(eBulletSize size, const Vector2<float>& position, float angle, int speed, int color) {
	_vector.emplace_back(make_shared<Bullet>(position, angle, speed, 2, color, size));
	SoundManager::getIns()->play(toString(ResourceID::ShotBulletSE));
}

void BulletMgr::CheckOut() {
	//�R���e�i���g�����̓C�e���[�^�j���O���ɂ���Ă������ƁB
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