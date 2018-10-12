#include "stdafx.h"
#include "mainGame.h"
#include "effectManager.h"
#include "bossScene.h"
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
	EFFECTMANAGER->addEffect("tankEffect", "image/enemy/tank_effect.bmp", 800, 42, 50, 42, 20, TIMEMANAGER->getElapsedTime(), 10);

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
