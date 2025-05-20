#pragma once

class Bullet;	//���O�����O���錾
//���g���g�p���Ă��Ȃ��̂ł���ŏ\��

class IBulletBehavior
{
public:
	virtual void Update(Bullet& bullet) = 0;
	virtual ~IBulletBehavior() = default;
};

