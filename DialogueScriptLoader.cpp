#include "DialogueScriptLoader.h"
#include "Macro.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <windows.h>


std::vector<DialogueEntry> DialogueScriptLoader::LoadDialogueFromJson(const std::string& filename) {

	std::ifstream file(filename);
	if (!file) {
		ERR(("��b�X�N���v�g�t�@�C����������܂���: " + filename).c_str());
	}

	std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	OutputDebugStringA(("�ǂݍ���JSON:\n" + content + "\n").c_str());

	nlohmann::json j;

	//�����Bparse(..., nullptr, false)�ɂ���ƌ��i������discarded����邩�璍�ӁB�ꎞ�Ԕ��قǔ�΂����B
	try {
		j = nlohmann::json::parse(content);
	}
	catch (const std::exception& e) {
		OutputDebugStringA(("JSON�p�[�X��O: " + std::string(e.what()) + "\n").c_str());
		ERR("�\���G���[���o");
	}

	if (j.is_null()) {
		ERR("JSON��null�ł�\n");
	}


	if (j.is_discarded()) {
		ERR("JSON�̃p�[�X�Ɏ��s���܂����B�\���G���[�̉\��������܂�");
	}

	std::vector<DialogueEntry> entries;

	for (const auto& item : j) {
		if (!item.contains("speaker") || !item.contains("text")) {
			OutputDebugStringA("[WARNING] Dialogue�G���g����speaker�܂���text������܂���B�X�L�b�v���܂��B\n");
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
		ERR("��b�X�N���v�g�̓ǂݍ��݂ɐ������܂������A�Z���t���������܂���B�X�N���v�g���m�F���Ă�������");
	}

	return entries;
}