#define NOMINMAX
#include "ColMgr.h"

#include "RectangleObject.h"
#include "CircleObject.h"
#include "Player.h"
#include "Ball.h"
#include "BulletMgr.h"
#include "BlockMgr.h"
#include "ItemMgr.h"
#include "CollisitonEvent.h"
#include <cmath>
#include <algorithm>
#include <DxLib.h>

void ColMgr::Initialize() {

}

void ColMgr::Finalize() {

}

void ColMgr::Update(BlockMgr& blockMgr, BulletMgr& bulletMgr, ItemMgr& itemMgr, Player& player, Ball& ball, std::vector<CollisionEvent>& evCol) {
	if (ball.CheckFlag((int)Ball::fBall::_move)) {
		//playerとball
		if (Col_RectAndBall(player, ball)) {
			CollisionEvent t = {eCollisionEvent::BallToPlayer, -1, player.GetterVelocity(), Col_RectAndBall(player, ball)};
			evCol.push_back(t);
		}
	}
	
	//blockとball
	for (int i = 0; i < Define::BLOCK_NUM; ++i) {
		//生きているなら
		if (blockMgr.Getter_LiveBlock(i) != nullptr) {//そのBlockが生きているなら
			if (Col_RectAndBall(*blockMgr.Getter_LiveBlock(i), ball)) {//当たったら
				CollisionEvent t = { eCollisionEvent::BallToBlock, i, blockMgr.Getter_LiveBlock(i)->GetterVelocity(), Col_RectAndBall(*blockMgr.Getter_LiveBlock(i), ball) };
				evCol.push_back(t);
			}
		}
	}

	//bulletとplayer
	for (int i = 0; i < bulletMgr.GetBulletNum(); ++i) {
		//ここら辺、ポインタと参照が混じっててカオス
		if (Col_RectAndBall(player, *bulletMgr.GetBullet(i))) {
			CollisionEvent t = { eCollisionEvent::BulletToPlayer, i};
			evCol.push_back(t);
		}
	}

	//ballとbullet
	for (int i = 0; i < bulletMgr.GetBulletNum(); ++i) {
		if (Col_BallAndBall(ball, *bulletMgr.GetBullet(i))) {
			CollisionEvent t = { eCollisionEvent::BallToBullet, i };
			evCol.push_back(t);
		}
	}

	//itemとplayer
	for (int i = 0; i < itemMgr.GetArrayNum(); ++i) {
		std::vector<Vector2<float>> playerVert = player.GetterVertexs();
		std::vector<Vector2<float>> itemVert = itemMgr.GetterItem(i)->GetterVertexs();
		if (SAT_Intersect(playerVert, itemVert)) {
			CollisionEvent t = { eCollisionEvent::ItemToPlayer, i };
			evCol.push_back(t);
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

//bool ColMgr::Col_RectAndRect(const RectangleObject& rect1, const RectangleObject& rect2) const {
//	
//}

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

bool ColMgr::SAT_Intersect(const std::vector<Vector2<float>>& polyA, const std::vector<Vector2<float>>& polyB) {
	std::vector<Vector2<float>> axes;

	// Aの辺
	for (size_t i = 0; i < polyA.size(); ++i) {
		//最後の1辺は最初の頂点が終点
		Vector2<float> edge = polyA[(i + 1) % polyA.size()] - polyA[i];
		axes.push_back(Vector2<float>(-edge.GetterY(), edge.GetterX()).Norm());	//単位法線ベクトル
	}
	// Bの辺
	for (size_t i = 0; i < polyB.size(); ++i) {
		Vector2<float> edge = polyB[(i + 1) % polyB.size()] - polyB[i];
		axes.push_back(Vector2<float>(-edge.GetterY(), edge.GetterX()).Norm());
	}

	//各軸で投影し、区間が分離していないか確認
	for (const auto& axis : axes) {
		float minA, maxA, minB, maxB;
		ProjectPolygon(polyA, axis, minA, maxA);
		ProjectPolygon(polyB, axis, minB, maxB);

		//射影が分離しているなら衝突していない
		if (maxA < minB || maxB < minA) {
			return false;
		}
	}
	//全ての軸で重なっている→衝突
	return true;
}

bool ColMgr::Col_BallAndBall(const CircleObject& circle1, const CircleObject& circle2) const {
	Vector2<float> diff = circle2.GetterPosition() - circle1.GetterPosition();

	//距離の二乗(平方根はコストが高い為内積で)
	float dist = diff.DotProd(diff);

	float sumRadius = circle1.GetterR() + circle2.GetterR();

	return dist <= sumRadius * sumRadius;

}

bool ColMgr::Col_SegmentAndSegment(const Segment& segment1, const Segment& segment2) const{
	//segment1を直線AB, segment2を直線CDとする
	Vector2<float> AB = segment1.GetterSegVector();
	Vector2<float> AC = segment2.GetterBegVector() - segment1.GetterBegVector();
	Vector2<float> AD = segment2.GetterEndVector() - segment1.GetterBegVector();

	Vector2<float> CD = segment2.GetterSegVector();
	Vector2<float> CA = segment1.GetterBegVector() - segment2.GetterBegVector();
	Vector2<float> CB = segment1.GetterEndVector() - segment2.GetterBegVector();

	float cross1 = AB.CrossProd(AC);
	float cross2 = AB.CrossProd(AD);
	float cross3 = CD.CrossProd(CA);
	float cross4 = CD.CrossProd(CB);

	//AC, ADのsinの正負に着目。それが－であれば直線CDは点Aを跨いで存在している。
	//CA, CBのsinの正負も合わせることで線分同士の当たり判定になる。
	return (cross1 * cross2 < 0) && (cross3 * cross4 < 0);
}

void ColMgr::ProjectPolygon(const std::vector<Vector2<float>>& vertices, const Vector2<float>& axis, float& min, float& max) {
	//頂点の軸への射影
	min = vertices[0].DotProd(axis);
	max = vertices[0].DotProd(axis);
	//射影した直線
	for (const auto& v : vertices) {
		float proj = v.DotProd(axis);
		min = std::min(min, proj);
		max = std::max(max, proj);

	}
}