#pragma once

#include <string>
#include "Vector2.h"

struct BulletEvent {
	std::string type;
	std::string size;
	int startFrame;
	int endFrame;
	int interval;
	Vector2<float> position;
	std::string angleExpr;
	float speed;
	int layer;
	bool targetPlayer = false;
};