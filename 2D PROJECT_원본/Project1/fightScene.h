#pragma once
#include "scene.h"

class player;
class enemyManager;
class npcManager;
class fightScene : public scene
{
private:
	enemyManager*	m_enemyMgr;
	npcManager* m_npcMgr;
	player*	m_pPlayer;
	image*	m_fightMap;
	image* m_pixel;

	RECT gate;
	RECT m_moveMap;
	
	float m_fightMapX;
	float m_mapMoveDest;
	int m_currScene = 1;

	bool m_isMapMove = false;

	float currY;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	void BulletCollideToEnemy();
	void setEnemy();
	void collider();
	void gravity();
	void mapMove();

	fightScene();
	~fightScene();
};

