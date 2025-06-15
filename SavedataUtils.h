#pragma once
#include <string>
#include "GlobalStatus.h"

class SavedataUtils final {
public:
	~SavedataUtils() = default;

	static void SaveBinary(const GlobalStatus& saveData, const std::string& filename = "savedata.bat");
	static GlobalStatus LoadBinary(const std::string& filename = "savedata.bat");
};