#pragma once
#include "scene.h"
class player;
class enemyManager;
class enemy;
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

	void collider();
	void CheckDistance();

	introScene();
	~introScene();
};

