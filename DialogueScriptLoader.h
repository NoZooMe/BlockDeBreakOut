#pragma once
#include <string>
#include <vector>

struct DialogueEntry {
	std::string speaker;
	std::string text;
	std::string leftImage;
	std::string rightImage;
};

//ユーティリティクラス
class DialogueScriptLoader
{
public:
	DialogueScriptLoader() = delete;
	static std::vector<DialogueEntry> LoadDialogueFromJson(const std::string& filename);
};

