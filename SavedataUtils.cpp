#include "SavedataUtils.h"
#include <fstream>

void SavedataUtils::SaveBinary(const GlobalStatus& status, const std::string& filename ) {
	std::ofstream ofs(filename, std::ios::binary);
	if (!ofs) return;	//ファイル書き込み失敗

	ofs.write(reinterpret_cast<const char*>(&status), sizeof(status));
}

GlobalStatus SavedataUtils::LoadBinary(const std::string& filename) {
	GlobalStatus status{};	//念のためデフォルト初期化

	std::ifstream ifs(filename, std::ios::binary);
	if (!ifs) return status;	//ファイルが無いなら初期状態

	ifs.read(reinterpret_cast<char*>(&status), sizeof(status));
	return status;
}