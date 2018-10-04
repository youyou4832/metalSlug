#pragma once
#include "scene.h"
class player;

class TestScene :	public scene
{
private:
	image * m_pBG;
	player*	m_pPlayer;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	TestScene();
	~TestScene();
};

