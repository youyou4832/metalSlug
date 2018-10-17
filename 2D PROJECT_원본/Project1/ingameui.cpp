#include "stdafx.h"
#include "ingameui.h"


HRESULT ingameui::init()
{
	m_pImgInGameUi = new image;
	m_pImgInGameUi2 = new image;

	m_pImgInGameUi = IMAGEMANAGER->addImage("inGameUi", "image/ui/ingameui.bmp",
		164, 75, true, RGB(255, 0, 255));
	m_pImgInGameUi2 = IMAGEMANAGER->addImage("inGameUI2", "image/ui/ui.bmp",
		500, 251, true, RGB(255, 0, 255));

	m_UifX1 = 50;
	m_UifY1 = 20;

	m_UifX2 = 0;
	m_UifY2 = 0; 

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
	m_pImgInGameUi->render(hdc, m_UifX1+450, m_UifY1, 0, 29, 164, 46, 2);
}

ingameui::ingameui()
{
}


ingameui::~ingameui()
{
}
