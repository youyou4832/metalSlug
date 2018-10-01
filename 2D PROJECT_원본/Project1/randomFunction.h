#pragma once

//#include "stdafx.h"
#include "singletonBase.h"
#include <time.h>

// randomFunction

class randomFunction : public singletonBase <randomFunction>
{
public:
	randomFunction()
	{
		//srand((unsigned int)time(NULL));
		srand(GetTickCount());
	}
	~randomFunction() {}

	inline int getInt(int num) { return rand() % num; }
	// from : 1, to : 5 -> 1 ~ 5
	inline int getFromIntTo(int from, int to)
	{ 
		return (rand() % (to - from + 1)) + from;
	}

	// RAND_MAX : 32767  => 0.0 ~ 1.0
	inline float getFloat() { return (float)rand() / (float)RAND_MAX; }
	inline float getFloat(float num) { return ((float)rand() / (float)RAND_MAX) * num; }
	inline float getFromFloatTo(float from, float to)
	{
		float rnd = (float)rand() / (float)RAND_MAX;
		return from + (rnd * (to - from));
	}
	
};