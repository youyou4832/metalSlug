#pragma once

class player;

class ingameui
{
private:
	image * m_pImgInGameUi;
	image * m_pImgInGameUi2;

	float m_UifX1;
	float m_UifY1;

	float m_LifeUifX;
	float m_LifeUifY;

	float m_BulltNumUifX;
	float m_BulltNumUifY;

	

	player * m_pPlayer;

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	ingameui();
	~ingameui();
};

