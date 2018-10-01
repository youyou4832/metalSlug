#pragma once
#include "singletonBase.h"
class timer;

class timeManager : public singletonBase<timeManager>
{
private:
	timer * m_timer;

public:
	HRESULT init();
	void release();
	
	void update(float lockFPS = 0.0f);
	void render(HDC hdc);

	timeManager();
	~timeManager();
};

