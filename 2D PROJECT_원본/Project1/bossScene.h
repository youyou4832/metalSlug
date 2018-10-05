#pragma once
#include "scene.h"

class boss;
class animation;

class bossScene :public scene
{
private:
	image	*	m_pimgBG;
	image	*	m_pimgSubBG;
	
	image	*	m_pimgbridge;
	boss	*	m_pBoss;
	
	float m_mapSpeed;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	bossScene();
	~bossScene();
};

