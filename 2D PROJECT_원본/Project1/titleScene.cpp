#include "stdafx.h"
#include "titleScene.h"
#include "button.h"

HRESULT titleScene::init()
{
	m_pTitleBG = IMAGEMANAGER->addImage("titleScene", "image/titleScene/titleScene.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	
	return S_OK;
}

void titleScene::release()
{
	
}

void titleScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		SCENEMANAGER->changeScene("selectScene");
	}
}

void titleScene::render(HDC hdc)
{
	m_pTitleBG->render(hdc, 0, 0);
}

titleScene::titleScene()
{
}


titleScene::~titleScene()
{
}
