#include "StageScriptLoader.h"
#include "ExprEval.h"
#include "CommandFactory.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <Windows.h>

std::vector<BulletEvent>  StageScriptLoader::LoadStageScriptFromJSON(const std::string& filename) {
	std::ifstream file(filename);
	if (!file) {
		throw std::runtime_error("ステージスクリプトファイルが見つかりません: " + filename);
	}
	nlohmann::json j;
	//fileをjに出力。失敗すれば例外をスロー
	try {
		file >> j;
	} catch(const std::exception& e) {
		OutputDebugStringA(("JSONパース失敗: " + std::string(e.what()) + "\n").c_str());
		throw;
	}
	

	std::vector<BulletEvent> events;

	for (const auto& item : j) {
		//デバッグ
		//std::string msg = "[DEBUG] " + item.dump(2);
		//OutputDebugStringA(msg.c_str());

		try {
			BulletEvent e;
			//valueで初期値を設定。存在しないor型違いの時に初期値を返す
			e.type = item.value("type", "StraightBullet");
			e.size = item.value("size", "Small");
			e.startFrame = item.value("startFrame", 0);
			e.endFrame = item.value("endFrame", 0);
			e.interval = item.value("interval", 0);

			// 位置ベクトル
			if (!item.contains("position") || !item["position"].is_array() || item["position"].size() != 2) {
				OutputDebugStringA("[WARNING] position が不正です。スキップします。\n");
				continue;
			}

			auto pos = item["position"];
			e.position.SetterX(EvaluateExpr(pos[0].is_string() ? pos[0].get<std::string>() : std::to_string(pos[0].get<double>())));
			e.position.SetterY(EvaluateExpr(pos[1].is_string() ? pos[1].get<std::string>() : std::to_string(pos[1].get<double>())));
			//角度(存在しない場合でも"0"文字列を使う)
			e.angleExpr = item.value("angle", "0");

			//速度とレイヤー
			e.speed = item.value("speed",  5.0f);
			e.layer = item.value("layer", 0);

			e.targetPlayer = item.value("targetPlayer", false);

			// BulletEventの中身を文字列化して出力
			char buffer[256];

			const char* toPlayerStr = e.targetPlayer ? "true" : "false";

			sprintf_s(buffer, sizeof(buffer),
				"[DEBUG] BulletEvent: type=%s, size=%s, pos=(%.1f, %.1f), angle=%s, speed=%.1f, interval=%d, startFrame=%d, endFrame=%d, toPlayer=%s\n",
				e.type.c_str(), e.size.c_str(),
				e.position.GetterX(), e.position.GetterY(),
				e.angleExpr.c_str(), e.speed, e.interval, e.startFrame, e.endFrame, toPlayerStr);
			OutputDebugStringA(buffer);

			events.push_back(e);
		}
		catch (const std::exception& e) {
			OutputDebugStringA(("[ERROR] 弾幕読み込み失敗: " + std::string(e.what()) + "\n").c_str());
			continue;
		}
	}
	return events;
}

std::vector<BulletCommand::TimedCommand> StageScriptLoader::LoadCommandsFromJSON(const std::string& path) {
	std::ifstream file(path);
	nlohmann::json j;
	file >> j;

	std::vector<BulletCommand::TimedCommand> commands;
	for (const auto& item : j) {
		int frame = item.value("frame", 0);
		auto cmdJson = item["command"];
		auto cmd = CommandFactory::CreateFromJSON(cmdJson);
		commands.push_back(BulletCommand::TimedCommand{ frame, cmd });
	}

	return commands;
}