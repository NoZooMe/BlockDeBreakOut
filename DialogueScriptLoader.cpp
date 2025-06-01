#include "DialogueScriptLoader.h"
#include "Macro.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <windows.h>


std::vector<DialogueEntry> DialogueScriptLoader::LoadDialogueFromJson(const std::string& filename) {

	std::ifstream file(filename);
	if (!file) {
		ERR(("会話スクリプトファイルが見つかりません: " + filename).c_str());
	}

	std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	OutputDebugStringA(("読み込んだJSON:\n" + content + "\n").c_str());

	nlohmann::json j;

	//ここ。parse(..., nullptr, false)にすると厳格すぎてdiscardedされるから注意。一時間半ほど飛ばした。
	try {
		j = nlohmann::json::parse(content);
	}
	catch (const std::exception& e) {
		OutputDebugStringA(("JSONパース例外: " + std::string(e.what()) + "\n").c_str());
		ERR("構文エラー検出");
	}

	if (j.is_null()) {
		ERR("JSONがnullです\n");
	}


	if (j.is_discarded()) {
		ERR("JSONのパースに失敗しました。構文エラーの可能性があります");
	}

	std::vector<DialogueEntry> entries;

	for (const auto& item : j) {
		if (!item.contains("speaker") || !item.contains("text")) {
			OutputDebugStringA("[WARNING] Dialogueエントリにspeakerまたはtextがありません。スキップします。\n");
			continue;
		}
		DialogueEntry entry;
		entry.speaker = item.value("speaker", "???");
		entry.text = item.value("text", "");
		entry.leftImage = item.value("leftImage", "");
		entry.rightImage = item.value("rightImage", "");

		char buf[256];
		sprintf_s(buf, "[DEBUG] Dialogue: speaker=%s, text=%s\n", entry.speaker.c_str(), entry.text.c_str());
		OutputDebugStringA(buf);

		entries.push_back(entry);
	}

	if (entries.empty()) {
		ERR("会話スクリプトの読み込みに成功しましたが、セリフが一つもありません。スクリプトを確認してください");
	}

	return entries;
}