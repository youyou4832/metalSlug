#include "stdafx.h"
#include "fightScene.h"
#include "player.h"
#include "enemyManager.h"
#include "npcManager.h"
HRESULT fightScene::init()
{
	

	// 플레이어
	//m_currScene = 1;
	
	
	
	if (m_currScene == 1) {
		m_fightMap = IMAGEMANAGER->addImage("fightMap", "image/map/mainMap.bmp", 8000, WINSIZEY, false, 0);
		m_pixel = IMAGEMANAGER->findImage("pixel");
		m_pPlayer = new player;
		m_enemyMgr = new enemyManager;
		m_npcMgr = new npcManager;
		m_enemyMgr->init();
		m_fightMapX = 0;
		//setEnemy();
		m_npcMgr->setNPC("npc", WINSIZEX/2, WINSIZEY/2-300, 5);
		//이미지
		
		m_pPlayer->init(100, WINSIZEY / 2);
		/*m_enemyMgr->setSniper("sniper", WINSIZEX / 2 - 100, WINSIZEY / 2 + 30, 5, m_pPlayer);
		m_enemyMgr->setSniper("sniper", WINSIZEX / 2 + 100, WINSIZEY / 2 - 10, 5, m_pPlayer);
		m_enemyMgr->setCannon("cannon", WINSIZEX / 2 + 400, WINSIZEY / 2 + 70, 5, m_pPlayer, 1, false);*/
		m_moveMap = RectMakeCenter(WINSIZEX - 20, WINSIZEY / 2, 40, WINSIZEY);
		
	}
	else {
		m_enemyMgr->init();
		//setEnemy();
	}

	

	
	
	return S_OK;
}

void fightScene::release()
{
	SAFE_DELETE(m_enemyMgr);
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_npcMgr);
}

void fightScene::update()
{
	if (!g_saveData.isMoveMap) {
		gravity();
		m_enemyMgr->update();
		
		collider();
	}
	else {
		mapMove();
	}
	m_pPlayer->update();
	m_npcMgr->update();
}

void fightScene::render(HDC hdc)
{
	m_fightMap->render(hdc, m_fightMapX,0);
	m_pixel->render(hdc, m_fightMapX, 0);
	m_enemyMgr->render(hdc);
	m_pPlayer->render(hdc);
	m_npcMgr->render(hdc);

	//Rectangle(hdc, m_moveMap.left, m_moveMap.top, m_moveMap.right, m_moveMap.bottom);
	EFFECTMANAGER->render(hdc, 2);
}

void fightScene::setEnemy()
{
	for (int i = 0; i < TOTAL_ENEMY; ++i) {
		if (g_mainGame.getEnemyPosition(i).e_pos.x < WINSIZEX * m_currScene && g_mainGame.getEnemyPosition(i).e_pos.x > 0 + WINSIZEX * (m_currScene - 1)) {
			if (g_mainGame.getEnemyPosition(i).charNum == CharInfo::i_cannon) {
				m_enemyMgr->setCannon("cannon", g_mainGame.getEnemyPosition(i).e_pos.x - WINSIZEX * (m_currScene - 1), g_mainGame.getEnemyPosition(i).e_pos.y, 5, m_pPlayer, 1, false);
			}
			else if (g_mainGame.getEnemyPosition(i).charNum == CharInfo::i_sniper) {
				m_enemyMgr->setSniper("sniper", g_mainGame.getEnemyPosition(i).e_pos.x - WINSIZEX * (m_currScene - 1), g_mainGame.getEnemyPosition(i).e_pos.y, 5, m_pPlayer);
			}
			else if (g_mainGame.getEnemyPosition(i).charNum == CharInfo::i_tank) {
				m_enemyMgr->setTank("tank", g_mainGame.getEnemyPosition(i).e_pos.x - WINSIZEX * (m_currScene - 1), g_mainGame.getEnemyPosition(i).e_pos.y, 5, m_pPlayer, false);
			}
			else if (g_mainGame.getEnemyPosition(i).charNum == CharInfo::i_normal) {
				m_enemyMgr->setNormal("normal", g_mainGame.getEnemyPosition(i).e_pos.x - WINSIZEX * (m_currScene - 1), g_mainGame.getEnemyPosition(i).e_pos.y, 5, m_pPlayer, 1, false);
			}
			else if (g_mainGame.getEnemyPosition(i).charNum == CharInfo::i_npc) {
				m_npcMgr->setNPC("npc", g_mainGame.getEnemyPosition(i).e_pos.x - WINSIZEX * (m_currScene - 1), g_mainGame.getEnemyPosition(i).e_pos.y, 2);
			}
		}
	}
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
		COLORREF color = GetPixel(m_pixel->getMemDC(), m_pPlayer->getLowerImgX() - m_fightMapX, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);


		if (!(r == 255 && g == 0 && b == 255))
		{
			m_pPlayer->setLowerImgY(i - heightSize - 2);
			
			break;
		}
	}

	if (m_pPlayer->getLowerImgX() > WINSIZEX-1) {
		g_saveData.isMoveMap = true;
		m_mapMoveDest = m_fightMapX - 1600;
		++m_currScene;
	}
	
	vector<npc*> vNPC = m_npcMgr->getVecNPC();
	vector<npc*>::iterator n_iter;
	
	for (n_iter = vNPC.begin(); n_iter != vNPC.end(); n_iter++) {
		if ((*n_iter)->getIsAlive()) {
			if ((!(*n_iter)->getHangState() && !(*n_iter)->getMoveState()) || (*n_iter)->getMoveState()) {
				(*n_iter)->setNPCPosY((*n_iter)->getNPCPosY() + 8);

				for (int i = (*n_iter)->getNPCPosY() + 150; i < (*n_iter)->getNPCPosY() + 171; ++i) {
					COLORREF color = GetPixel(m_pixel->getMemDC(), (*n_iter)->getNPCPosX(), i);

					int r = GetRValue(color);
					int g = GetGValue(color);
					int b = GetBValue(color);

					if (!(r == 255 && g == 0 && b == 255))
					{
						(*n_iter)->setNPCPosY((*n_iter)->getNPCPosY() - ((*n_iter)->getNPCPosY() + 171 - i));
						(*n_iter)->setMoveState(true);
						(*n_iter)->setFallState(false);

						break;
					}
				}
			}
		}
	}
}

void fightScene::mapMove()
{
	if (m_fightMapX != m_mapMoveDest) {
		m_pPlayer->setLowerImgX(m_pPlayer->getLowerImgX() - 10);
		m_fightMapX -= 10;
		
	}
	else {
		g_saveData.isMoveMap = false;
		init();
	}
}

fightScene::fightScene()
{
}


fightScene::~fightScene()
{
}
