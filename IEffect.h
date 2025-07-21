#pragma once


class IEffect {
public:
	IEffect(int duration, int width, int height);
	virtual ~IEffect() = default;
	virtual void Apply(int srcGraph, int dstGraph) = 0;
	virtual void Update();
	bool GetterDeleteFlag();

protected:
	int _duration;
	int _cnt;
	int _w, _h;
	bool _deleteFlag;
};