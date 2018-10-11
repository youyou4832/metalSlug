#include "stdafx.h"
#include "bossScene.h"
#include "boss.h"
#include "player.h"

HRESULT bossScene::init()
{
	m_pimgBG = IMAGEMANAGER->addImage("map", "image/map/testBG.bmp",
		WINSIZEX, WINSIZEY, false, 0);
	m_pimgSubBG = IMAGEMANAGER->addImage("submap", "image/map/testBG.bmp",
		WINSIZEX, WINSIZEY, false, 0);
	
	m_pimgbridge = IMAGEMANAGER->addImage("bridge", "image/map/bridge.bmp",
		768, 69, true, RGB(255, 0, 255));
	m_pimgSbridge = IMAGEMANAGER->addImage("bridge", "image/map/bridge.bmp",
		768, 69, true, RGB(255, 0, 255));

	m_pimgeffect = IMAGEMANAGER->addImage("boss", "image/boss/BossEffect.bmp",
		1056, 736, 15 , 5, true, RGB(255, 0, 255)); // 보스의 관한 탄 및 이펙트 이미지 

	m_pimgBG->setX(0);
	m_pimgBG->setY(0);

	m_mapPoX = 0;
	m_bridgeX = 1000;
	m_SubbridgeX = 1000;

	m_pPlayer = new player;
	m_pPlayer->init(WINSIZEX / 2, WINSIZEY / 2);

	m_pBoss = new boss;
	m_pBoss->init();

	

	return S_OK;
}

void bossScene::release()
{
	SAFE_DELETE(m_pBoss);
	SAFE_DELETE(m_pPlayer);
}

void bossScene::update()
{
	m_pBoss->update();
	m_mapPoX -= 10;
	m_bridgeX -= 10;

	if(m_mapPoX <= -WINSIZEX)
	{
		m_mapPoX = 0;
	}
	
	if (m_bridgeX <= -(1000 + 3000))
	{
		m_bridgeX = 1000;
	}
	m_pPlayer->update();
}

void bossScene::render(HDC hdc)
{ 
	//맵 출력 
	m_pimgBG->render(hdc, m_mapPoX,0 ,0 ,0, 0, m_pimgBG->getX(), m_pimgBG->getY());
	m_pimgSubBG->render(hdc, m_mapPoX + WINSIZEX, 0, 0, 0, 0, m_pimgBG->getX(), m_pimgBG->getY());
	m_pPlayer->render(hdc);
	//다리 출력
	//m_pimgbridge->render(hdc, m_bridgeX, WINSIZEY - 275, 0, 0, 768, 69, 4);
	//m_pimgSbridge->render(hdc, m_SubbridgeX + 3070, WINSIZEY-275 , 0, 0, 768, 69, 4);

	m_pBoss->render(hdc);
	
}

bossScene::bossScene()
{
}


bossScene::~bossScene()
{
}
