#include "Stage1Script.h"
#include "ExprEval.h"
#include "Define.h"
#include "StageScriptLoader.h"

Stage1Script::Stage1Script(const std::string& stagescriptPath) {
	_events = StageScriptLoader::LoadStageScriptFromJSON(stagescriptPath);
}

void Stage1Script::Update(int cnt, BulletMgr& bulletMgr, const Player& player, const Ball& ball) {
	//待ち状態の時、ゲームオーバーしてる時はscriptは進めない
	if (ball.CheckFlag((int)Ball::fBall::_wait)) return;
	if (player.Getter_PlayerLife() <= 0) return;


	for (const auto& e : _events) {

		//何発撃つか
		int shotsPerCycle = e.endFrame - e.startFrame;
		//１サイクルの長さ(ショット時間＋休止時間)
		int cycleLength = shotsPerCycle + e.interval;

		//startFrame前には撃たない
		if (cnt < e.startFrame) return;
		
		//今、サイクルの何フレーム目かを取得
		int cycleFrame = (cnt - e.startFrame) % cycleLength;

		if (cycleFrame >= shotsPerCycle) return; //休止フェーズならスキップ

		//弾を1発だけ撃つ
		float angle = 0.0f;

		if (e.targetPlayer) {
			Vector2<float> dir = player.GetterPosition() - e.position;
			angle = dir.GetterAngle();
		}
		else {
			angle = EvaluateExpr(e.angleExpr);
		}

		eBulletSize bulletSize;
		if (e.size == "Small") bulletSize = eBulletSize::Small;
		else if (e.size == "Midium") bulletSize = eBulletSize::Midium;
		else if (e.size == "Large") bulletSize = eBulletSize::Large;
		else return;

		if (e.type == "StraightBullet") {
			bulletMgr.Set_StraightBullet(bulletSize, e.position, angle, e.speed, e.layer);
		}
		else if (e.type == "SinBullet") {
			bulletMgr.Set_SinBullet(bulletSize, e.position, angle, e.speed, e.layer);
		}

	}

}