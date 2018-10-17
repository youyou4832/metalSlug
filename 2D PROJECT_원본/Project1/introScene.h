#pragma once
#include "scene.h"
class player;
class enemyManager;

class introScene : public scene
{
private:
	enemyManager*	m_enemyMgr;
	player*	m_pPlayer;
	image*	m_introMap;

	RECT gate;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	void knifeCollideToEnemy();
	void BulletCollideToEnemy();

	void collider();

	introScene();
	~introScene();
};

