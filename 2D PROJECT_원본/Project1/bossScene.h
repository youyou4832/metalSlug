#pragma once
#include "scene.h"


class boss;
class animation;
class player;
class bridge;

class bossScene :public scene
{
private:
	image	*	m_pimgBG;
	image	*	m_pimgSubBG;
	
	image	*	m_pimgeffect;

	image*		m_tempBG;
	boss	*	m_pBoss;
	bridge	*	m_pBridge;
	player	*	m_pPlayer;
	RECT		m_rc;
	RECT		m_rc2;


	float m_mapPoX;

	float m_pixelPosX;
	float m_pixelPosY;

	int m_pixelCurrY;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	void pixelCollide();

	bossScene();
	~bossScene();
};

