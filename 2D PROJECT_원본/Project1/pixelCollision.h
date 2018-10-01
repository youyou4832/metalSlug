#pragma once
#include "scene.h"

class pixelCollision
{
private:
	image*	m_pImg;
	POINT	m_position;
	RECT	m_rc;
	int		m_currY;

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	pixelCollision();
	~pixelCollision();
};
