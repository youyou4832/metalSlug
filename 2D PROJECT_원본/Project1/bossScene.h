#pragma once
#include "scene.h"

class boss;
class animation;
class player;

class bossScene :public scene
{
private:
	image	*	m_pimgBG;
	image	*	m_pimgSubBG;
	
	image	*	m_pimgbridge;
	image	*	m_pimgSbridge;
	image	*	m_pimgeffect;
	boss	*	m_pBoss;
	player* m_pPlayer;
	RECT	m_rc;

	float m_mapPoX;
	float m_bridgeX;
	float m_SubbridgeX;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	bossScene();
	~bossScene();
};

