#include "stdafx.h"
#include "ingameui.h"


HRESULT ingameui::init()
{
	m_pImgInGameUi = new image;
	m_pImgInGameUi2 = new image;

	m_pImgInGameUi = IMAGEMANAGER->addImage("inGameUi", "image/ui/ingameui.bmp",
		162, 60, true, RGB(255, 0, 255));
	m_pImgInGameUi2 = IMAGEMANAGER->addImage("inGameUI2", "image/ui/ui.bmp",
		512, 255, true, RGB(255, 0, 255));

	m_UifX1 = 50;
	m_UifY1 = 20;

	m_LifeUifX = 140;
	m_LifeUifY = 60;

	m_BulltNumUifX = 545;
	m_BulltNumUifY = 55;
	
	return S_OK;
}

void ingameui::release()
{
	SAFE_DELETE(m_pImgInGameUi);
	SAFE_DELETE(m_pImgInGameUi2);
}

void ingameui::update()
{
	
}

void ingameui::render(HDC hdc)
{
	m_pImgInGameUi->render(hdc, m_UifX1, m_UifY1, 0, 0, 141, 29, 2);
	m_pImgInGameUi->render(hdc, m_UifX1+450, m_UifY1, 0, 29, 162, 31, 2);
	m_pImgInGameUi2->render(hdc, m_LifeUifX, m_LifeUifY, 0 + (8 * g_saveData.life), 239, 8, 8, 2);
	m_pImgInGameUi2->render(hdc, m_BulltNumUifX, m_BulltNumUifY, 0, 247, 20, 8, 2);
}

ingameui::ingameui()
{
}


ingameui::~ingameui()
{
}
