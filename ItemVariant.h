#pragma once
#include "ItemPattern.h"
#include <variant>

using ItemDataVariant = std::variant<ImmidiateItem, StackableItem>;