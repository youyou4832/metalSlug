#pragma once
#include "scene.h"
class player;
class enemyManager;

class introScene : public scene
{
private:
	player* m_player;
	enemyManager* m_enemyMgr;
	image* m_introMap;
	RECT gate;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	void collider();

	introScene();
	~introScene();
};

