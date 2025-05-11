#include "ColMgr.h"
#include "SoundManager.h"
#include "ResourceID.h"
#include <cmath>
#include <DxLib.h>

void ColMgr::Initialize() {

}

void ColMgr::Finalize() {

}

void ColMgr::Update(BlockMgr& blockMgr, BulletMgr& bulletMgr, Player& player, Ball& ball) {
	if (ball.CheckFlag((int)Ball::fBall::_move)) {
		//playerとball
		if (Col_RectAndBall(player, ball)) {
			ball.ReflectFromSurface(*Col_RectAndBall(player, ball), player.GetterVelocity());
		}
	}
	

	//blockとball
	for (int i = 0; i < Define::BLOCK_NUM; i++) {
		//生きているなら
		if (blockMgr.Getter_LiveBlock(i) != nullptr) {//そのBlockが生きているなら
			if (Col_RectAndBall(*blockMgr.Getter_LiveBlock(i), ball)) {//当たったら
				ball.ReflectFromSurface(*Col_RectAndBall(*blockMgr.Getter_LiveBlock(i), ball), blockMgr.Getter_LiveBlock(i)->GetterVelocity());
				blockMgr.SetBlockFlag_Live(i, false);
				SoundManager::getIns()->play(toString(ResourceID::BreakBlockSE));
			}
		}
	}

	//bulletとplayer
	for (int i = 0; i < bulletMgr.GetBulletNum(); i++) {
		//ここら辺、ポインタと参照が混じっててカオス
		if (Col_RectAndBall(player, *bulletMgr.GetBullet(i))) {
			//無敵でないなら無敵フラグをオン
			if (!player.isDamaged()) {
				player.CallDecLife();
				SoundManager::getIns()->play(toString(ResourceID::DamageSE));
				player.DamagePlayer();
			}
			bulletMgr.DeleteBullet(i);
		}
	}

}


std::optional<Segment> ColMgr::Col_RectAndBall(const RectangleObject& rect, const CircleObject& ball) const {
	//もしもrectが配列で辺を保持していたらもう少し短くかけた
	if (Col_SegmentAndBall(rect.vertSide1, ball)) {
		return rect.vertSide1;
	}
	if (Col_SegmentAndBall(rect.vertSide2, ball)) {
		return rect.vertSide2;
	}
	if (Col_SegmentAndBall(rect.horiSide1, ball)) {
		return rect.horiSide1;
	}
	if(Col_SegmentAndBall(rect.horiSide2, ball)) {
		return rect.horiSide2;
	}

	return std::nullopt;
}

bool ColMgr::Col_SegmentAndBall(const Segment& segment, const CircleObject& ball) const {
	//線分の始点から終点へのベクトルと、線分の始点から円の中心へのベクトルを作る
	Vector2<float> vectorA = segment.GetterSegVector();
	Vector2<float> vectorB = ball.GetterPosition() - segment.GetterBegVector();

	//Aに対するBの外積(スカラー)。中心と直線との最短距離
	int dist = vectorB.CrossProd(vectorA.Norm());

	//最短距離が半径より小さければ次の判定へ
	if (fabsf(dist) < ball.GetterR()) {
		//線分の終点から円の中心へのベクトルを作る
		Vector2<float> vectorC = ball.GetterPosition() - segment.GetterEndVector();

		//(A, B), (C, B)の内積を求め、正負が異なれば線分上に垂線が落ちている
		float dotProd1 = vectorB.DotProd(vectorA);
		float dotProd2 = vectorC.DotProd(vectorA);

		//もしも当たり判定がおかしかったらここを解除して、if文の中身をsing1*sing2<0に。
		////正負判定。異なるなら-1。同じなら1
		//int sign1 = (dotProd1 > 0) - (dotProd1 < 0);
		//int sign2 = (dotProd2 > 0) - (dotProd2 < 0);

		if (dotProd1 * dotProd2 < 0.0f) {
			return true;
		}

		//線分の末端付近が当たっているか調べる
		if (vectorB.Abs() < ball.GetterR() || vectorC.Abs() < ball.GetterR()) {
			return true;
		}

	}
	return false;
	
}
