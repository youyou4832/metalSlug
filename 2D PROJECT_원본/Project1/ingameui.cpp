#include "stdafx.h"
#include "ingameui.h"
#include "player.h"


HRESULT ingameui::init()
{
	isUiStart = true;

	m_pImgInGameUi = new image;
	m_pImgInGameUi2 = new image;

	
	m_pImgInGameUi = IMAGEMANAGER->addImage("inGameUi", "image/ui/ingameui.bmp",
		162, 60, true, RGB(255, 0, 255));
	m_pImgInGameUi2 = IMAGEMANAGER->addImage("inGameUI2", "image/ui/ui.bmp",
		512, 255, true, RGB(255, 0, 255));
	
	//
	/*m_pImgINGameUi3 = IMAGEMANAGER->addImage("inGameUI3", "image/ui/ingameui2.bmp",
		190, 128, true, RGB(255, 0, 255));*/

	m_UifX1 = 50;
	m_UifY1 = 20;

	m_LifeUifX = 140;
	m_LifeUifY = 60;

	m_BulltNumUifX = 545;
	m_BulltNumUifY = 55;

	m_missionUifX = 500;
	m_missionUifY = WINSIZEY / 4;

	/*UiCount = 0;*/
	
	return S_OK;
}

void ingameui::release()
{
	SAFE_DELETE(m_pImgInGameUi);
	SAFE_DELETE(m_pImgInGameUi2);
}

void ingameui::update()
{
	/*UiDelayCount();*/
}

void ingameui::render(HDC hdc)
{
	m_pImgInGameUi->render(hdc, m_UifX1, m_UifY1, 0, 0, 141, 29, 2);
	m_pImgInGameUi->render(hdc, m_UifX1+450, m_UifY1, 0, 29, 162, 31, 2);
	m_pImgInGameUi2->render(hdc, m_LifeUifX, m_LifeUifY, 0 + (8 * g_saveData.life), 239, 8, 8, 2);
	m_pImgInGameUi2->render(hdc, m_BulltNumUifX, m_BulltNumUifY, 0, 247, 20, 8, 2);

	/*if (m_UiDelay.index % 2 == 0 && isUiStart)
	{
		m_pImgINGameUi3->render(hdc, m_missionUifX, m_missionUifY, 0, 0, 190, 32, 3);

		if (UiCount >= 15)
		{
			m_pImgINGameUi3->render(hdc, m_missionUifX + 65, m_missionUifY + 150, 0, 32, 148, 32, 3);
		}
	}*/

	/*if (m_UiDelay.index % 2 == 0 && isUiStart) // 보스 클리어 시 
	{
		m_pImgINGameUi3->render(hdc, m_missionUifX, m_missionUifY, 0, 0, 190, 32, 3);

		if (UiCount >= 15)
		{
			m_pImgINGameUi3->render(hdc, m_missionUifX + 65, m_missionUifY + 150, 0, 64, 148, 32, 3);
		}
	}*/

	/*if (m_UiDelay.index % 2 == 0 && isUiStart) // 모든 목숨을 소모한 후 제거
	{
		m_pImgINGameUi3->render(hdc, m_missionUifX, m_missionUifY, 0, 0, 190, 32, 3);

		if (UiCount >= 15)
		{
			m_pImgINGameUi3->render(hdc, m_missionUifX + 130, m_missionUifY + 150, 0, 96, 148, 32, 3);
		}
	}*/

	
}

//void ingameui::UiDelayCount()
//{
//	if (isUiStart)
//	{
//		++m_UiDelay.count;
//		++UiCount;
//		if (m_UiDelay.count % 5 == 0) {
//			++m_UiDelay.index;
//			if (m_UiDelay.index == 20) {
//				m_UiDelay.index = 0;
//				UiCount = 0;
//				isUiStart = false;
//			}
//			m_UiDelay.count = 0;
//		}
//	}
//}

ingameui::ingameui()
{
}


ingameui::~ingameui()
{
}
