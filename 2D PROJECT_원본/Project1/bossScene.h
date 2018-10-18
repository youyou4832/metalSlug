#pragma once
#include "scene.h"


class boss;
class animation;
class player;
class bridge;
class ingameui;

struct ClearUiDelay {
	int index = 0;
	int count = 0;
};

class bossScene :public scene
{
private:
	image	*	m_pimgBG;
	image	*	m_pimgSubBG;

	image	*	m_bridge;
	image	*	m_bridge2;
	image	*	m_bridge3;
	
	image	*	m_pimgeffect;

	image*		m_tempBG;
	image*		m_pImgClearUi;

	boss	*	m_pBoss;
	bridge	*	m_pBridge;
	player	*	m_pPlayer;
	ingameui*	m_pInGameUi;
	RECT		m_rc;
	RECT		m_rc2;

	ClearUiDelay m_ClearDelay;

	int m_ClearUiCount;
	float m_ClearUifX;
	float m_ClearUifY;

	float m_mapPosX;
	float m_mapPosX2;

	float m_bridgePosX;
	float m_bridgePosX2;
	float m_bridgePosX3;
	bool m_checkMove = false;

	float m_pixelPosX;
	float m_pixelPosY;

	int m_pixelCurrY;
	int m_front = 0;

	bool isClearUiStart;
	bool bossClear;


public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	void ClearUiDelayCount();
	void pixelCollide();
	void gameClearChack();
	void bossDieChack();

	bossScene();
	~bossScene();
};

