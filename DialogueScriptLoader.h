#pragma once
#include <string>
#include <vector>

struct DialogueEntry {
	std::string speaker;
	std::string text;
	std::string leftImage;
	std::string rightImage;
};

//���[�e�B���e�B�N���X
class DialogueScriptLoader
{
public:
	DialogueScriptLoader() = delete;
	static std::vector<DialogueEntry> LoadDialogueFromJson(const std::string& filename);
};

