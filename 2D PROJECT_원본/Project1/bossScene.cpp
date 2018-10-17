#include "stdafx.h"
#include "bossScene.h"
#include "boss.h"
#include "bridge.h"
#include "player.h"
#include "ingameui.h"
#include "pixelCollision.h"

HRESULT bossScene::init()
{
	m_pimgBG = IMAGEMANAGER->addImage("map", "image/map/testBG.bmp",
		WINSIZEX, WINSIZEY, false, 0);
	m_pimgSubBG = IMAGEMANAGER->findImage("map");

	m_tempBG = new image;
	m_tempBG->init("magenta", WINSIZEX, WINSIZEY, false, 0);
	m_pimgeffect = IMAGEMANAGER->addImage("boss", "image/boss/BossEffect.bmp",
		1056, 736, 15 , 5, true, RGB(255, 0, 255)); // 보스의 관한 탄 및 이펙트 이미지 

	m_pimgBG->setX(0);
	m_pimgBG->setY(0);

	m_mapPosX = 0;
	m_mapPosX2 = WINSIZEX;

	m_bridgePosX = 0;
	m_bridgePosX2 = WINSIZEX;
	m_bridgePosX3 = WINSIZEX*2 + 800;
	
	m_pPlayer = new player;
	m_pPlayer->init(WINSIZEX / 2, WINSIZEY / 2);

	m_pBoss = new boss;
	m_pBoss->init();

	m_pInGameUi = new ingameui;
	m_pInGameUi->init();
	
	m_pBridge = new bridge;
	m_pBridge->init();
	m_bridge = IMAGEMANAGER->findImage("maxBridge");
	m_bridge2 = IMAGEMANAGER->findImage("maxBridge2");
	m_bridge3 = IMAGEMANAGER->findImage("maxBridge2");
	
	return S_OK;
}

void bossScene::release()
{
	SAFE_DELETE(m_pInGameUi);
	SAFE_DELETE(m_pBridge);
	SAFE_DELETE(m_pBoss);
	SAFE_DELETE(m_pPlayer);
}

void bossScene::update()
{
	

	m_pBoss->update();
	m_pPlayer->update();
	m_pInGameUi->update();
	m_pBridge->update();
	
	if (m_pBoss->getisAlive())
	{
		m_mapPosX -= 10;
		m_mapPosX2 -= 10;

		m_bridgePosX -= 10;
		m_bridgePosX2 -= 10;
		m_bridgePosX3 -= 10;

		if (m_mapPosX <= -WINSIZEX)
		{
			m_mapPosX = WINSIZEX;
		}
		if (m_mapPosX2 <= -WINSIZEX)
		{
			m_mapPosX2 = WINSIZEX;
		}

		if (m_bridgePosX <= -WINSIZEX)
		{
			m_bridgePosX = 800;
		}
		if (m_bridgePosX2 <= -WINSIZEX)
		{
			m_bridgePosX2 = WINSIZEX * 2;
		}
		if (m_bridgePosX3 <= -WINSIZEX)
		{
			m_bridgePosX3 = WINSIZEX * 2;
		}
	}
	//pixelCollide();
	m_rc = RectMake(m_pBoss->getX()+700, m_pixelCurrY, 50 ,50);
	m_rc2 = RectMake(m_pBoss->getX() + 700, m_pixelCurrY-150, 50, 50);

}

void bossScene::render(HDC hdc)
{ 
	m_pInGameUi->render(hdc);
	//맵 출력 
	/*m_bridge->render(hdc, m_mapPoX, 0, 0, 0, 0, m_pimgBG->getX(), m_pimgBG->getY());
	m_bridge2->render(hdc, m_mapPoX + WINSIZEX, 0, 0, 0, 0, m_pimgBG->getX(), m_pimgBG->getY());*/
	m_pimgBG->render(hdc, m_mapPosX, 0);
	m_pimgSubBG->render(hdc, m_mapPosX2, 0);
	
	m_bridge->render(hdc, m_bridgePosX, 0);
	m_bridge2->render(hdc, m_bridgePosX2, 0);
	m_bridge3->render(hdc, m_bridgePosX3, 0);
	m_pPlayer->render(hdc);
	//다리 출력
	//m_pBridge->render(hdc);
	
	//보스 출력
	m_pBoss->render(hdc);


	Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
	Rectangle(hdc, m_rc2.left, m_rc2.top, m_rc2.right, m_rc2.bottom);
	
}

void bossScene::pixelCollide()
{
	//m_pixelPosX = m_pBoss->getX();
	m_pixelPosY = m_pBoss->getY();

	m_pixelCurrY = m_pixelPosY + 750;
	/*m_front++;
	if (m_front == 19) {
		m_front = 0;
	}*/
	for (int i = m_pixelCurrY - 150; i < m_pixelCurrY + 50; ++i)
	{
		COLORREF color = GetPixel(m_pBridge->getImgPixels(m_front)->getMemDC(),m_pBoss->getX(), i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		//if (r == 255 && g == 0 && b == 255)
		//{
		//	m_position.y = i - m_pImgBall->getHeight();
		//}

		if (!(r == 255 && g == 0 && b == 255))
		{
			//Sleep(1000);
			break;
		}
	}
}

void bossScene::gameoveChack(bool playerDie)
{
	if (!playerDie)
	{
		SCENEMANAGER->changeScene("gameoveScene");
	}
}

bossScene::bossScene()
{

	
}


bossScene::~bossScene()
{
}
