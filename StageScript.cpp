#include "StageScript.h"
#include "ExprEval.h"
#include "Define.h"
#include "StageScriptLoader.h"
#include "Ball.h"
#include "Player.h"
#include "eBulletSize.h"
#include "BulletMgr.h"
#include <iostream>
#include <Windows.h>

StageScript::StageScript(const std::string& stagescriptPath, const std::string& commandPath) {
	_events = StageScriptLoader::LoadStageScriptFromJSON(stagescriptPath);
	_commands = StageScriptLoader::LoadCommandsFromJSON(commandPath);
}

void StageScript::Update(int cnt, BulletMgr& bulletMgr, const Player& player, const Ball& ball, int stageCnt) {
	//待ち状態の時、ゲームオーバーしてる時はscriptは進めない
	if (ball.CheckFlag((int)Ball::fBall::_wait)) return;
	if (player.Getter_PlayerLife() <= 0) return;

	for (const auto& e : _events) {

		//何発撃つか
		int shotsPerCycle = e.endFrame - e.startFrame;
		//１サイクルの長さ(ショット時間＋休止時間)
		int cycleLength = shotsPerCycle + e.interval;

		//startFrame前には撃たない
		if (cnt < e.startFrame) continue;
		
		//今、サイクルの何フレーム目かを取得
		int cycleFrame = (cnt - e.startFrame) % cycleLength;

		if (cycleFrame >= shotsPerCycle) continue; //休止フェーズならスキップ

		//弾を1発だけ撃つ
		float angle = 0.0f;

		//フラグがTRUEかつ角度が入っていればターゲットの方向＋その角度で撃つ。
		if (e.targetPlayer) {
			Vector2<float> dir = player.GetterPosition() - e.position;
			angle = dir.GetterAngle() + EvaluateExpr(e.angleExpr);
		}
		else {
			angle = EvaluateExpr(e.angleExpr);
		}

		eBulletSize bulletSize;
		if (e.size == "Small") bulletSize = eBulletSize::Small;
		else if (e.size == "Midium") bulletSize = eBulletSize::Midium;
		else if (e.size == "Large") bulletSize = eBulletSize::Large;
		else continue;

		if (e.type == "StraightBullet") {
			bulletMgr.Set_StraightBullet(bulletSize, e.position, angle, e.speed, e.layer);
		}
		else if (e.type == "SinBullet" ) {
			bulletMgr.Set_SinBullet(bulletSize, e.position, angle, e.speed, e.layer);
		}
		else if (e.type == "SpiralBullet") {
			bulletMgr.Set_SpiralBullet(bulletSize, e.position, angle, e.speed, e.layer);
		}
		else if (e.type == "GravityBullet") {
			bulletMgr.Set_GravityBullet(bulletSize, e.position, angle, e.speed, e.layer);
		}
		else if (e.type == "WeierBullet") {
			bulletMgr.Set_WeierstrassBullet(bulletSize, e.position, angle, e.speed, e.layer);
		}

	}

	for (const auto& cmd : _commands) {
		//frameを超えたら発射。durationを使う場合はduration毎に発射
		if (!cmd.useDuration) {
			if (cnt >= cmd.frame && (cnt - cmd.frame) % stageCnt == 0) {
				cmd.command->Execute(bulletMgr);

			}
		}
		else {
			if (cnt >= cmd.frame && (cnt - cmd.frame) % cmd.duration == 0) {
				cmd.command->Execute(bulletMgr);
			}

		}
	}

}