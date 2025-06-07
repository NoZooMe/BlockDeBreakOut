#pragma once
#include <memory>
class ShapeObject;

class  IInstanceDeleteListener {
public:
	IInstanceDeleteListener() = default;
	~IInstanceDeleteListener() = default;

	virtual void onInstanceDeleted(std::shared_ptr<ShapeObject> instance) = 0;
};