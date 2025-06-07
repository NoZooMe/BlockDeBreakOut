#pragma once
#include "eCollisionEvent.h"
#include "Vector2.h"
#include "Segment.h"
#include <optional>
#include <memory>

struct CollisionEvent {
	eCollisionEvent _type;
	int _index = -1;
	//Õ“Ë‚µ‚½•¨‘Ì‚Ì‘¬“x‚Æ•\–ÊB
	std::optional<Vector2<float>> _vector;
	std::optional<Segment> _surface;
};