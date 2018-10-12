#include "stdafx.h"
#include "fightScene.h"
#include "player.h"
#include "enemyManager.h"

HRESULT fightScene::init()
{
	//이미지
	m_fightMap = IMAGEMANAGER->addImage("fightMap", "image/map/mainMap.bmp", 8000, WINSIZEY, false, 0);
	m_pixel = IMAGEMANAGER->addImage("pixel", "image/map/mainMap_pixel.bmp", 8000, WINSIZEY, true, RGB(255, 0, 255));

	// 플레이어
	m_pPlayer = new player;
	m_pPlayer->init(100, WINSIZEY/2);

	m_enemyMgr = new enemyManager;
	

	return S_OK;
}

void fightScene::release()
{
	SAFE_DELETE(m_enemyMgr);
	SAFE_DELETE(m_pPlayer);
}

void fightScene::update()
{
	gravity();
	m_enemyMgr->update();
	m_pPlayer->update();
	collider();
}

void fightScene::render(HDC hdc)
{
	m_fightMap->render(hdc,0,0);
	//m_pixel->render(hdc, 0, 0);
	m_enemyMgr->render(hdc);
	m_pPlayer->render(hdc);

	//Rectangle(hdc, gate.left, gate.top, gate.right, gate.bottom);
	EFFECTMANAGER->render(hdc, 2);
}

void fightScene::collider()
{
}

void fightScene::gravity()
{
	
	m_pPlayer->setLowerImgY(m_pPlayer->getLowerImgY() + 5);

	int heightSize =m_pPlayer->getRectLower().bottom - m_pPlayer->getLowerImgY();


	for (int i = m_pPlayer->getLowerImgY()+heightSize -20; i < m_pPlayer->getLowerImgY() + heightSize + 1; ++i)//하체 48
	{
		COLORREF color = GetPixel(m_pixel->getMemDC(), m_pPlayer->getLowerImgX(), i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);


		if (!(r == 255 && g == 0 && b == 255))
		{
			m_pPlayer->setLowerImgY(i - heightSize - 2);
			
			break;
		}
	}
}

fightScene::fightScene()
{
}


fightScene::~fightScene()
{
}
