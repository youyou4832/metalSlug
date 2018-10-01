#include "stdafx.h"
#include "titleScene.h"
#include "button.h"

void buttonFunc1(void)
{
	SCENEMANAGER->changeScene("select", "loading");
}

HRESULT titleScene::init()
{
	return S_OK;
}

void titleScene::release()
{
}

void titleScene::update()
{
}

void titleScene::render(HDC hdc)
{
}

titleScene::titleScene()
{
}


titleScene::~titleScene()
{
}
