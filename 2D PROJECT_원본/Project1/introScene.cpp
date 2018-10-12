#include "stdafx.h"
#include "introScene.h"
#include "enemyManager.h"
#include "player.h"

HRESULT introScene::init()
{
	//이미지
	m_introMap = IMAGEMANAGER->addImage("introMap", "image/map/map_Intro.bmp", WINSIZEX, WINSIZEY, false, 0);
	
	// 플레이어
	m_pPlayer = new player;
	m_pPlayer->init(100, -140);

	m_enemyMgr = new enemyManager;
	m_enemyMgr->setTank("tank", WINSIZEX + 600, WINSIZEY / 2 + 70, 5, CharInfo::i_tank, m_pPlayer, 1);
	m_enemyMgr->setSniper("sniper", WINSIZEX / 2 + 300, WINSIZEY / 2 - 30, 5, CharInfo::i_sniper, m_pPlayer);
	m_enemyMgr->setCannon("cannon", WINSIZEX + 200, WINSIZEY / 2 + 50, 5, CharInfo::i_cannon, m_pPlayer, 2);
	m_enemyMgr->setNormal("normal", WINSIZEX +400, WINSIZEY / 2 + 70, 5, CharInfo::i_normal, m_pPlayer, 3);
	//m_enemyMgr->setTank("tank", WINSIZEX + 600, WINSIZEY / 2 + 70, 5, CharInfo::i_tank, m_pPlayer, 1);

	
	gate = RectMakeCenter(WINSIZEX - 20, WINSIZEY / 2, 40, WINSIZEY);
	
	
	



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
	//Rectangle(hdc, gate.left, gate.top, gate.right, gate.bottom);
	EFFECTMANAGER->render(hdc,2);
}

void introScene::collider()
{
	RECT upper_rc = m_pPlayer->getRectUpper();
	RECT lower_rc = m_pPlayer->getRectLower();
	RECT rc;
	if (IntersectRect(&rc, &upper_rc, &gate)) {
		SCENEMANAGER->changeScene("fightScene");
	}
}

introScene::introScene()
{
}

introScene::~introScene()
{
}
