#pragma once
#include "eCollisionEvent.h"
#include "Vector2.h"
#include "Segment.h"
#include <optional>
#include <memory>

struct CollisionEvent {
	eCollisionEvent _type;
	int _index = -1;
	//�Փ˂������̂̑��x�ƕ\�ʁB
	std::optional<Vector2<float>> _vector;
	std::optional<Segment> _surface;
};