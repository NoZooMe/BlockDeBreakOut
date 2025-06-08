#include "Stage1Script.h"
#include "ExprEval.h"
#include "Define.h"
#include "StageScriptLoader.h"
#include "Ball.h"
#include "Player.h"
#include "eBulletSize.h"
#include "BulletMgr.h"
#include <iostream>
#include <Windows.h>

Stage1Script::Stage1Script(const std::string& stagescriptPath, const std::string& commandPath) {
	_events = StageScriptLoader::LoadStageScriptFromJSON(stagescriptPath);
	_commands = StageScriptLoader::LoadCommandsFromJSON(commandPath);
	 
	
	//// BulletEvent�̒��g�𕶎��񉻂��ďo��
	//for (const auto& e : _events) {
	//	const char* toPlayerStr = e.targetPlayer ? "true" : "false";

	//	char buffer[1024];  // �� �K���\���ȃT�C�Y���m��
	//	int ret = sprintf_s(buffer, sizeof(buffer),
	//		"[DEBUG] _events: type=%s, size=%s, pos=(%.1f, %.1f), angle=%s, speed=%.1f, interval=%d, startFrame=%d, endFrame=%d, toPlayer=%s\n",
	//		e.type.c_str(), e.size.c_str(),
	//		e.position.GetterX(), e.position.GetterY(),
	//		e.angleExpr.c_str(), e.speed, e.interval, e.startFrame, e.endFrame, toPlayerStr);

	//	if (ret > 0) {
	//		OutputDebugStringA(buffer);
	//	}
	//	else {
	//		OutputDebugStringA("[ERROR] sprintf_s failed\n");
	//	}
	//}
}

void Stage1Script::Update(int cnt, BulletMgr& bulletMgr, const Player& player, const Ball& ball) {
	//�҂���Ԃ̎��A�Q�[���I�[�o�[���Ă鎞��script�͐i�߂Ȃ�
	if (ball.CheckFlag((int)Ball::fBall::_wait)) return;
	if (player.Getter_PlayerLife() <= 0) return;

	for (const auto& e : _events) {

		//��������
		int shotsPerCycle = e.endFrame - e.startFrame;
		//�P�T�C�N���̒���(�V���b�g���ԁ{�x�~����)
		int cycleLength = shotsPerCycle + e.interval;

		//startFrame�O�ɂ͌����Ȃ�
		if (cnt < e.startFrame) continue;
		
		//���A�T�C�N���̉��t���[���ڂ����擾
		int cycleFrame = (cnt - e.startFrame) % cycleLength;

		if (cycleFrame >= shotsPerCycle) continue; //�x�~�t�F�[�Y�Ȃ�X�L�b�v

		//�e��1����������
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
		//frame�𒴂����甭�ˁBduration���g���ꍇ��duration���ɔ���
		if (!cmd.useDuration) {
			if (cnt >= cmd.frame && (cnt - cmd.frame) % 800 == 0) {
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