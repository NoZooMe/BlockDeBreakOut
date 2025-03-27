#include "Looper.h"

Looper::Looper()
{
}

Looper::~Looper()
{
}

bool Looper::loop() 
{
	_fps.draw();
	_fps.wait();
	return true;
}