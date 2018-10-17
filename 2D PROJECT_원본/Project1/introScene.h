#pragma once
#include "scene.h"
class player;
class enemyManager;
class ingameui;

class introScene : public scene
{
private:
	enemyManager*	m_enemyMgr;
	player*	m_pPlayer;
	ingameui* m_pInGameUi;
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

