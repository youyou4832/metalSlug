#include "stdafx.h"
#include "introScene.h"
#include "enemyManager.h"

HRESULT introScene::init()
{
	m_introMap = IMAGEMANAGER->addImage("introMap", "image/map/map_Intro.bmp", WINSIZEX, WINSIZEY, false, 0);
	IMAGEMANAGER->addImage("sniper", "image/enemy/sniper_Attack.bmp", WINSIZEX / 2, WINSIZEY / 2, 2484, 76, 27, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("specialBullet", "image/enemy/cannon_effect.bmp", 0, 0, 576, 43, 16, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("sandbag", "image/sandbag/sandbag.bmp", 0, 0, 1600, 297, 20, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("enemy_death", "image/enemy/enemy_death.bmp", 0, 0, 264, 39, 6, 1, true, RGB(255, 0, 255));

	m_enemyMgr = new enemyManager;
	m_enemyMgr->setSniper("sniper", WINSIZEX / 2, WINSIZEY / 2 - 30, 5, CharInfo::i_sniper);
	return S_OK;
 }

void introScene::release()
{
	SAFE_DELETE(m_enemyMgr);
}

void introScene::update()
{
	m_enemyMgr->update();
}

void introScene::render(HDC hdc)
{
	m_introMap->render(hdc, 0, 0);
	m_enemyMgr->render(hdc);
}

introScene::introScene()
{
}


introScene::~introScene()
{
}
