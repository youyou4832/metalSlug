#include "stdafx.h"
#include "selectScene.h"


HRESULT selectScene::init()
{
	m_pSelectBG = IMAGEMANAGER->addImage("selectScene", "image/selectScene/selectScene2.bmp",
		WINSIZEX, WINSIZEY, true, RGB(255, 0 ,255));
	m_pimgSelectUi = IMAGEMANAGER->addImage("SelectUi", "image/selectScene/charactersSelect2.bmp",
		256, 380, true, RGB(255, 0, 255));


	m_PlayerUIfX1 = 225;
	m_PlayerUIfY1 =	170;

	m_PlayerUIfX2 = 170;
	m_PlayerUIfY2 = 300;
	return S_OK;
}

void selectScene::release()
{
	SAFE_DELETE(m_pSelectBG);
}

void selectScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		SCENEMANAGER->changeScene("intro");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		if (m_PlayerUIfX1 < 1290)
		{
			m_PlayerUIfX1 += 355;
			m_PlayerUIfX2 += 355;
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		if (m_PlayerUIfX1 > 225)
		{
			m_PlayerUIfX1 -= 355;
			m_PlayerUIfX2 -= 355;
		}
	}
}

void selectScene::render(HDC hdc)
{
	m_pSelectBG->render(hdc, 0, 0);
	m_pimgSelectUi->render(hdc, m_PlayerUIfX1, m_PlayerUIfY1, 0, 0, 27, 20, 3);

	m_pimgSelectUi->render(hdc, 170, 300, 0, 260, 64, 120, 3);
	m_pimgSelectUi->render(hdc, 525, 300, 64, 260, 64, 120, 3);
	m_pimgSelectUi->render(hdc, 880, 300, 128, 260, 64, 120, 3);
	m_pimgSelectUi->render(hdc, 1235, 300, 192, 260, 64, 120, 3);

	if (m_PlayerUIfX2 == 170)
	{
		m_pimgSelectUi->render(hdc, m_PlayerUIfX2, 300, 0, 20, 64, 120, 3);
	}

	else if (m_PlayerUIfX2 == 525)
	{
		m_pimgSelectUi->render(hdc, m_PlayerUIfX2, 300, 64, 20, 64, 120, 3);
	}

	else if (m_PlayerUIfX2 == 880)
	{
		m_pimgSelectUi->render(hdc, m_PlayerUIfX2, 300, 128, 20, 64, 120, 3);
	}

	else if (m_PlayerUIfX2 == 1235)
	{
		m_pimgSelectUi->render(hdc, m_PlayerUIfX2, 300, 192, 20, 64, 120, 3);
	}
	
}

selectScene::selectScene()
{
}


selectScene::~selectScene()
{
}
