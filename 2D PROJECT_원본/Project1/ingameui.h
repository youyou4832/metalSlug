#pragma once

class player;
class boss;



//struct UiDelay {
//	int index = 0;
//	int count = 0;
//};

class ingameui
{
private:
	image * m_pImgInGameUi;
	image * m_pImgInGameUi2;
	image *	m_pImgINGameUi3;

	player * m_pPlayer;
	boss   * m_pBoss;

	
	/*UiDelay m_UiDelay;*/

	//int UiCount;
	float m_UifX1;
	float m_UifY1;

	float m_LifeUifX;
	float m_LifeUifY;

	float m_BulltNumUifX;
	float m_BulltNumUifY;

	float m_missionUifX;
	float m_missionUifY;

	bool isUiStart;

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	/*void UiDelayCount();*/
	ingameui();
	~ingameui();
};

