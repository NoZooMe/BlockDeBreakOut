#pragma once

#include "Error.h"
#include <DxLib.h>

#define ERR(str) Error::finish(str, _T(_FUNCTION_), _LINE_)