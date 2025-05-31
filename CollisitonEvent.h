#pragma once
#include "eCollisionEvent.h"
#include "ShapeObject.h"
#include "Vector2.h"
#include "Segment.h"
#include <optional>
#include <memory>

struct CollisionEvent {
	eCollisionEvent _type;
	int _index = -1;
	//è’ìÀÇµÇΩï®ëÃÇÃë¨ìxÇ∆ï\ñ ÅB
	std::optional<Vector2<float>> _vector;
	std::optional<Segment> _surface;
};