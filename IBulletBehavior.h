#pragma once

class Bullet;	//名前だけ前方宣言
//中身を使用していないのでこれで十分

class IBulletBehavior
{
public:
	virtual void Update(Bullet& bullet) = 0;
	virtual ~IBulletBehavior() = default;
};

