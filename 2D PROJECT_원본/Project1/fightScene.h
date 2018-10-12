#pragma once
#include "scene.h"

class player;
class enemyManager;

class fightScene : public scene
{
private:
	enemyManager*	m_enemyMgr;
	player*	m_pPlayer;
	image*	m_fightMap;
	image*	m_pixel;

	RECT gate;

	float currY;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	void collider();
	void gravity();

	fightScene();
	~fightScene();
};

