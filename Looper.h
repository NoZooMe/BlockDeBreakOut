#pragma once
#include "Fps.h"
class Looper final
{
public:
	Looper();
	~Looper();
	bool loop() ;

private:
	Fps _fps;
};

