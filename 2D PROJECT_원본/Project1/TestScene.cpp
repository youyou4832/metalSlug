#include "stdafx.h"
#include "TestScene.h"
#include "player.h"

HRESULT TestScene::init()
{
	m_pBG = IMAGEMANAGER->addImage("image/testScene/background.bmp", "image/testScene/background.bmp", WINSIZEX, WINSIZEY, false, NULL);

	m_pPlayer = new player;
	m_pPlayer->init(WINSIZEX / 2, -140);

	return S_OK;
}

void TestScene::release()
{
	SAFE_DELETE(m_pPlayer);
}

void TestScene::update()
{
	m_pPlayer->update();
}

void TestScene::render(HDC hdc)
{
	if (m_pBG)
		m_pBG->render(hdc, 0, 0);

	m_pPlayer->render(hdc);
}

TestScene::TestScene()
{
}


TestScene::~TestScene()
{
}
