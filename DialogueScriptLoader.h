#pragma once
#include <string>
#include <vector>

struct DialogueEntry {
	std::string spaeker;
	std::string text;
	std::string leftImage;
	std::string rightImage;
};

class DialogueScriptLoader
{
public:
	static std::vector<DialogueEntry> LoadDialogueFromJson(const std::string& filename);
};

