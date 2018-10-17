#include "stdafx.h"
#include "mainGame.h"
#include "effectManager.h"
#include "bossScene.h"
#include "selectScene.h"
#include "introScene.h"
#include "fightScene.h"

void mainGame::setBackBuffer()
{
	m_pBackBuffer = new image;
	m_pBackBuffer->init(WINSIZEX, WINSIZEY);
}

HRESULT mainGame::init()
{
	hdc = GetDC(g_hWnd);
	setBackBuffer();

	m_enemyCount = 0;

	//HANDLE hTimer = (HANDLE)SetTimer(g_hWnd, 1, 10, NULL);
	KEYMANAGER->init();
	IMAGEMANAGER->init();
	TIMEMANAGER->init();
	EFFECTMANAGER->init();
	SCENEMANAGER->init();
	UIMANAGER->init();
	SOUNDMANAGER->init();

	IMAGEMANAGER->addImage("sniper", "image/enemy/sniper_Attack.bmp", WINSIZEX / 2, WINSIZEY / 2, 2484, 76, 27, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("specialBullet", "image/enemy/cannon_effect.bmp", 0, 0, 576, 43, 16, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("sandbag", "image/sandbag/sandbag.bmp", 0, 0, 1600, 297, 20, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("enemy_death", "image/enemy/enemy_death.bmp", 0, 0, 264, 39, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("cannon", "image/enemy/cannon.bmp", 0, 0, 726, 624, 11, 14, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("cannon_Attack", "image/enemy/cannon_Attack.bmp", 0, 0, 812, 52, 14, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("normalBullet", "image/enemy/normal_bullet.bmp", 24, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("normal", "image/enemy/normal_enemy.bmp", 0, 0, 368, 199, 12, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("tank", "image/enemy/tank.bmp", 0, 0, 576, 396, 10, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("npc", "image/npc/NPC.bmp", 0, 0, 574, 375, 9, 14, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item", "image/npc/item.bmp", 0, 0, 110, 120, 5, 6, true, RGB(255, 0, 255));
	EFFECTMANAGER->addEffect("tankEffect", "image/enemy/tank_effect.bmp", 800, 42, 50, 42, 20, TIMEMANAGER->getElapsedTime(), 10);
	m_pixel = IMAGEMANAGER->addImage("pixel", "image/map/mainMap_pixel2.bmp", 8000, WINSIZEY, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->addImage("magenta", "image/map/magenta.bmp", WINSIZEX, WINSIZEY,false,0);
	
	
	m_pTitleScene = new titleScene;
	SCENEMANAGER->addScene("titleScene", m_pTitleScene);

	m_pSelectScene = new selectScene;
	SCENEMANAGER->addScene("selectScene", m_pSelectScene);
	

	setEnemyPosition();
	m_pIntroScene = new introScene;
	SCENEMANAGER->addScene("intro", m_pIntroScene);

	m_pBossScene = new bossScene;
	SCENEMANAGER->addScene("bossScene", m_pBossScene);

	m_pFightScene = new fightScene;
	SCENEMANAGER->addScene("fightScene", m_pFightScene);

	SCENEMANAGER->changeScene("intro");
	
	// 필요한 리소스 미리 로드

	return S_OK;
}

void mainGame::release()
{
	SAFE_DELETE(m_pBackBuffer);

	ReleaseDC(g_hWnd, hdc);

	TXTDATA->release();
	KEYMANAGER->release();
	IMAGEMANAGER->release();
	TIMEMANAGER->release();
	SCENEMANAGER->release();

	TXTDATA->releaseSingleton();
	KEYMANAGER->releaseSingleton();
	IMAGEMANAGER->releaseSingleton();
	TIMEMANAGER->releaseSingleton();
	SCENEMANAGER->releaseSingleton();
}

LRESULT mainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	//HDC hdc;
	//PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_MOUSEMOVE:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		break;
	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			return 0;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

void mainGame::setEnemyPosition()
{
	for (int i = 0; i < 8000; i++) {
		for (int j = 0; j < WINSIZEY; j++) {
			COLORREF color = GetPixel(m_pixel->getMemDC(), i, j);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 0 && g == 0 && b == 1) {
				//m_enemyMgr->setSniper("sniper", i - 100, j - 200, 5, m_pPlayer);
				m_enemyPos[m_enemyCount].e_pos.x = i - 100;
				m_enemyPos[m_enemyCount].e_pos.y = j - 200;
				m_enemyPos[m_enemyCount].charNum = CharInfo::i_sniper;
				++m_enemyCount;
			}
			else if (r == 0 && g == 0 && b == 2) {
				//m_enemyMgr->setNormal("normal", i - 300, j - 100, 5, m_pPlayer, 1, false);
				m_enemyPos[m_enemyCount].e_pos.x = i - 300;
				m_enemyPos[m_enemyCount].e_pos.y = j - 100;
				m_enemyPos[m_enemyCount].charNum = CharInfo::i_normal;
				++m_enemyCount;
			}
			else if (r == 0 && g == 0 && b == 3) {
				//m_enemyMgr->setCannon("cannon", i, j - 100, 5, m_pPlayer, 1, false);
				m_enemyPos[m_enemyCount].e_pos.x = i - 130;
				m_enemyPos[m_enemyCount].e_pos.y = j - 130;
				m_enemyPos[m_enemyCount].charNum = CharInfo::i_cannon;
				++m_enemyCount;
			}
			else if (r == 0 && g == 0 && b == 4) {
				//m_enemyMgr->setTank("tank", i, j - 100, 5, m_pPlayer, false);
				m_enemyPos[m_enemyCount].e_pos.x = i;
				m_enemyPos[m_enemyCount].e_pos.y = j - 100;
				m_enemyPos[m_enemyCount].charNum = CharInfo::i_tank;
				++m_enemyCount;
			}

		}
	}
}

void mainGame::update()
{
	InvalidateRect(g_hWnd, NULL, false);
	SCENEMANAGER->update();
	EFFECTMANAGER->update();
}

void mainGame::render()
{
	HDC backDC = m_pBackBuffer->getMemDC();
	SCENEMANAGER->render(backDC);
	m_pBackBuffer->render(hdc, 0, 0);
}

mainGame::mainGame()
{
}


mainGame::~mainGame()
{
}
