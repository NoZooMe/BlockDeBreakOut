#include "Stage1Script.h"
#include "ExprEval.h"
#include "Define.h"
#include "StageScriptLoader.h"

Stage1Script::Stage1Script(const std::string& stagescriptPath) {
	_events = StageScriptLoader::LoadStageScriptFromJSON(stagescriptPath);
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
		if (cnt < e.startFrame) return;
		
		//���A�T�C�N���̉��t���[���ڂ����擾
		int cycleFrame = (cnt - e.startFrame) % cycleLength;

		if (cycleFrame >= shotsPerCycle) return; //�x�~�t�F�[�Y�Ȃ�X�L�b�v

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
		else return;

		if (e.type == "StraightBullet") {
			bulletMgr.Set_StraightBullet(bulletSize, e.position, angle, e.speed, e.layer);
		}
		else if (e.type == "SinBullet") {
			bulletMgr.Set_SinBullet(bulletSize, e.position, angle, e.speed, e.layer);
		}

	}

}