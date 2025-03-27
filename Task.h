#pragma once
class Task
{
public:
	Task() = default;
	virtual ~Task() = default;
	virtual void Initialize() = 0;
	virtual void Finalize() = 0;
	virtual void Update() = 0;
	virtual void Draw() const = 0;
};

