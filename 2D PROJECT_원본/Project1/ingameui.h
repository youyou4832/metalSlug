#pragma once

class player;

class ingameui
{
private:
	image * m_pImgInGameUi;
	image * m_pImgInGameUi2;

	float m_UifX1;
	float m_UifY1;

	float m_UifX2;
	float m_UifY2;

	

	player * m_pPlayer;

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	ingameui();
	~ingameui();
};

