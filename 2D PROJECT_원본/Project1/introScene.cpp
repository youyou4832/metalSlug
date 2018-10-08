#include "stdafx.h"
#include "introScene.h"
#include "enemyManager.h"
#include "player.h"

HRESULT introScene::init()
{
	m_introMap = IMAGEMANAGER->addImage("introMap", "image/map/map_Intro.bmp", WINSIZEX, WINSIZEY, false, 0);
	IMAGEMANAGER->addImage("sniper", "image/enemy/sniper_Attack.bmp", WINSIZEX / 2, WINSIZEY / 2, 2484, 76, 27, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("specialBullet", "image/enemy/cannon_effect.bmp", 0, 0, 576, 43, 16, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("sandbag", "image/sandbag/sandbag.bmp", 0, 0, 1600, 297, 20, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("enemy_death", "image/enemy/enemy_death.bmp", 0, 0, 264, 39, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("cannon", "image/enemy/cannon.bmp", 0, 0, 726, 624, 11, 14, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("cannon_Attack", "image/enemy/cannon_Attack.bmp", 0, 0, 812, 52, 14, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("normalBullet", "image/enemy/normal_bullet.bmp", 24, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("normal", "image/enemy/normal_enemy.bmp", 0, 0, 368, 199, 12, 5, true, RGB(255, 0, 255));

	m_enemyMgr = new enemyManager;
	m_enemyMgr->setSniper("sniper", WINSIZEX / 2, WINSIZEY / 2 - 30, 5, CharInfo::i_sniper);
	m_enemyMgr->setCannon("cannon", WINSIZEX / 2 + 300, WINSIZEY / 2 + 50, 5, CharInfo::i_cannon);
	m_enemyMgr->setNormal("normal", WINSIZEX / 2 - 300, WINSIZEY / 2 + 70, 5, CharInfo::i_normal);

	
	gate = RectMakeCenter(WINSIZEX - 20, WINSIZEY / 2, 40, WINSIZEY);
	
	// 플레이어
	m_pPlayer = new player;
	m_pPlayer->init();


	return S_OK;
 }

void introScene::release()
{
	SAFE_DELETE(m_enemyMgr);
	SAFE_DELETE(m_pPlayer);
}

void introScene::update()
{
	m_enemyMgr->update();
	m_pPlayer->update();
	collider();
}

void introScene::render(HDC hdc)
{
	m_introMap->render(hdc, 0, 0);
	m_enemyMgr->render(hdc);
	m_pPlayer->render(hdc);
	Rectangle(hdc, gate.left, gate.top, gate.right, gate.bottom);
}

void introScene::collider()
{
	RECT upper_rc = m_pPlayer->getRectUpper();
	RECT lower_rc = m_pPlayer->getRectLower();
	RECT rc;
	if (IntersectRect(&rc, &upper_rc, &gate)) {
		SCENEMANAGER->changeScene("bossScene");
	}
}

introScene::introScene()
{
}

introScene::~introScene()
{
}
