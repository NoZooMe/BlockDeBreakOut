#pragma once

#include "eBulletSize.h"
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
};