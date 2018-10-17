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
	m_enemyMgr->setTank("tank", WINSIZEX + 600, WINSIZEY / 2 + 70, 5, m_pPlayer, true);
	m_enemyMgr->setSniper("sniper", WINSIZEX / 2 + 300, WINSIZEY / 2 - 30, 5, m_pPlayer);
	m_enemyMgr->setCannon("cannon", WINSIZEX + 200, WINSIZEY / 2 + 50, 5,  m_pPlayer, 2, true);
	m_enemyMgr->setNormal("normal", WINSIZEX +400, WINSIZEY / 2 + 70, 5,  m_pPlayer, 3, true);
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
	collisionRect();

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

void introScene::collisionRect()
{
	vector<enemy *> vEnemy = m_enemyMgr->getVecEnemy();
	vector<enemy *>::iterator enemyIter = vEnemy.begin();
	RECT tempRC;

	for (enemyIter = vEnemy.begin(); enemyIter != vEnemy.end(); ++enemyIter)
	{
		// 플레이어RC, vEnemy의 rect와 intersectRect
		if (IntersectRect(&tempRC, &m_pPlayer->getRectAttBox(), &(*enemyIter)->getRect()) && m_pPlayer->getIsAttack() == true)
		{
			// 에너미가 살아있을 경우에만 충돌 처리
			if ((*enemyIter)->getIsAlive() == true)
			{
				m_pPlayer->setCollide(true);
				m_pPlayer->setIsAttack(false);
				m_pPlayer->fire();
				(*enemyIter)->setIsAlive(false);
			}

			break;
		}
	}
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
