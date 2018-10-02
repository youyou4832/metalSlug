#pragma once
#include "scene.h"

class boss;
class animation;

class bossScene :public scene
{
private:
	image	*	m_pimgBG;
	boss	*	m_pBoss;
	

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	bossScene();
	~bossScene();
};

