#include "stdafx.h"
#include "gameoverScene.h"


HRESULT gameoverScene::init()
{
	m_pimgGameOverBG = IMAGEMANAGER->addImage("gameoveScene", "image/gameoverScene/gameover.bmp",
		WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	return S_OK;
}

void gameoverScene::release()
{
}

void gameoverScene::update()
{
}

void gameoverScene::render(HDC hdc)
{
	m_pimgGameOverBG->render(hdc, 0, 0);
}

gameoverScene::gameoverScene()
{
}


gameoverScene::~gameoverScene()
{
}
