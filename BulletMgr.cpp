#include "BulletMgr.h"
#include "SmallBullet.h"
#include <DxLib.h>

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
		DrawFormatString(0, 640, GetColor(255, 255, 255), "%d", _vector.size());
	}
}

void BulletMgr::Set_StraightSmallBullet(const Vector2<float>& position, const Vector2<float>& direction, int speed, int color) {
	_vector.emplace_back(make_shared<SmallBullet>(position, direction, speed, 1, color));
}

void BulletMgr::Set_SinSmallBullet(const Vector2<float>& position, const Vector2<float>& direction, int speed, int color) {
	_vector.emplace_back(make_shared<SmallBullet>(position, direction, speed, 2, color));
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

shared_ptr<AbstractBullet> BulletMgr::GetBullet(int i) const {
	return _vector.at(i);
};

int BulletMgr::GetBulletNum() const {
	return _vector.size();
}

void BulletMgr::DeleteBullet(int num) {
	_vector.erase(_vector.begin() + num);
}