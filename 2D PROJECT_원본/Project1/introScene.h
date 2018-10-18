#pragma once
#include "scene.h"
class player;
class enemyManager;
class ingameui;


struct UiDelay {
	int index = 0;
	int count = 0;
};

class introScene : public scene
{
private:
	enemyManager*	m_enemyMgr;
	player*	m_pPlayer;
	ingameui* m_pInGameUi;
	image*	m_introMap;
	image *	m_pImgINGameUi;

	RECT gate;
	UiDelay m_UiDelay;

	int UiCount;
	float m_missionUifX;
	float m_missionUifY;

	bool isUiStart;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);


	void UiDelayCount();
	void knifeCollideToEnemy();
	void BulletCollideToEnemy();

	void collider();

	introScene();
	~introScene();
};

