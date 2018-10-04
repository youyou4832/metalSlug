#include "stdafx.h"
#include "bossScene.h"
#include "boss.h"


HRESULT bossScene::init()
{
	m_pimgBG = IMAGEMANAGER->addImage("boos", "image/map/testBG.bmp",
		WINSIZEX, WINSIZEY, false, 0);
	m_pimgSubBG = IMAGEMANAGER->addImage("boos", "image/map/testBG.bmp",
		WINSIZEX, WINSIZEY, false, 0);
	m_pimgBG->setX(0);
	m_pimgBG->setY(0);

	m_mapSpeed = -1.0;

	m_pBoss = new boss;
	m_pBoss->init();

	return S_OK;
}

void bossScene::release()
{
}

void bossScene::update()
{
	m_pBoss->update();
	
}

void bossScene::render(HDC hdc)
{
	m_pimgBG->render(hdc,m_pimgBG->getX(), m_pimgBG->getY());
	//m_pimgSubBG->render(hdc, m_pimgBG->getX()+WINSIZEX, m_pimgBG->getY());
	m_pBoss->render(hdc);
}

bossScene::bossScene()
{
}


bossScene::~bossScene()
{
}
