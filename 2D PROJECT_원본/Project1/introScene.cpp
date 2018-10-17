#include "stdafx.h"
#include "introScene.h"
#include "enemyManager.h"
#include "missileManager.h"
#include "player.h"
#include "ingameui.h"

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

	m_pInGameUi = new ingameui;
	m_pInGameUi->init();

	gate = RectMakeCenter(WINSIZEX - 20, WINSIZEY / 2, 40, WINSIZEY);
	
	

	return S_OK;
 }

void introScene::release()
{
	SAFE_DELETE(m_enemyMgr);
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pInGameUi);
}

void introScene::update()
{
	knifeCollideToEnemy();

	m_enemyMgr->update();
	m_pPlayer->update();
	m_pInGameUi->update();
	BulletCollideToEnemy();
	collider();
	
}

void introScene::render(HDC hdc)
{
	m_introMap->render(hdc, 0, 0);
	m_enemyMgr->render(hdc);
	m_pPlayer->render(hdc);
	m_pInGameUi->render(hdc);
	//Rectangle(hdc, gate.left, gate.top, gate.right, gate.bottom);
	EFFECTMANAGER->render(hdc,2);
}

void introScene::knifeCollideToEnemy()
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

void introScene::BulletCollideToEnemy()
{
	vector<enemy *> vEnemy = m_enemyMgr->getVecEnemy();
	vector<enemy *>::iterator enemyIter;
	RECT playerRC = m_pPlayer->getRectHit();
	for (enemyIter = vEnemy.begin(); enemyIter != vEnemy.end(); ++enemyIter) {
		
		vector<missile*> e_vMissile = (*enemyIter)->getMissileMgr()->getVecMissile();
		vector<missile*>::iterator e_missileIter;
		//플레이어 총알
		vector<missile*> p_vMissile = m_pPlayer->getMissileMgr()->getVecMissile();
		vector<missile*>::iterator p_missileIter;
		for (p_missileIter = p_vMissile.begin(); p_missileIter != p_vMissile.end(); ++p_missileIter) {
			RECT rc;
			//플레이어 총알과 에네미 충돌
			if ((*p_missileIter)->getIsFire() && (*enemyIter)->getIsAlive() && IntersectRect(&rc, &(*enemyIter)->getRect(), &(*p_missileIter)->getRect()) && (*enemyIter)->getDeathState() == false) {
				(*enemyIter)->setCurrHP((*enemyIter)->getCurrHP() - 1);
				(*enemyIter)->hit();
				(*p_missileIter)->setIsFire(false);
			}
		}
		for (e_missileIter = e_vMissile.begin(); e_missileIter != e_vMissile.end(); ++e_missileIter) {
			RECT rc;
			if ((*e_missileIter)->getIsFire() && m_pPlayer->getIsAlive() && IntersectRect(&rc, &playerRC, &(*e_missileIter)->getRect())) {
				m_pPlayer->setIsAlive(false);
				(*e_missileIter)->setIsFire(false);
			}
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
