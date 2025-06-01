#pragma once

#include "eBulletSize.h"
#include <Windows.h>
#include <string>
#include <stdexcept>

class ConvertUtils final {
public:
    ConvertUtils() = delete;

    inline static eBulletSize StringToSize(const std::string& str) {
        if (str == "Small") return eBulletSize::Small;
        if (str == "Midium") return eBulletSize::Midium;
        if (str == "Large") return eBulletSize::Large;
        throw std::runtime_error("Unknown bullet size: " + str);
    }

    inline static std::string Utf8ToSjis(const std::string& utf8) {
        // UTF-8 Å® UTF-16
        int wideLen = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, nullptr, 0);
        std::wstring wideStr(wideLen, 0);
        MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, &wideStr[0], wideLen);

        // UTF-16 Å® Shift-JIS
        int sjisLen = WideCharToMultiByte(CP_ACP, 0, wideStr.c_str(), -1, nullptr, 0, nullptr, nullptr);
        std::string sjisStr(sjisLen, 0);
        WideCharToMultiByte(CP_ACP, 0, wideStr.c_str(), -1, &sjisStr[0], sjisLen, nullptr, nullptr);

        return sjisStr;
    }
};