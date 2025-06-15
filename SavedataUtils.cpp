#include "SavedataUtils.h"
#include <fstream>

void SavedataUtils::SaveBinary(const GlobalStatus& status, const std::string& filename ) {
	std::ofstream ofs(filename, std::ios::binary);
	if (!ofs) return;	//�t�@�C���������ݎ��s

	ofs.write(reinterpret_cast<const char*>(&status), sizeof(status));
}

GlobalStatus SavedataUtils::LoadBinary(const std::string& filename) {
	GlobalStatus status{};	//�O�̂��߃f�t�H���g������

	std::ifstream ifs(filename, std::ios::binary);
	if (!ifs) return status;	//�t�@�C���������Ȃ珉�����

	ifs.read(reinterpret_cast<char*>(&status), sizeof(status));
	return status;
}