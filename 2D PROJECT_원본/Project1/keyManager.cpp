#include "stdafx.h"
#include "keyManager.h"


HRESULT keyManager::init()
{
	for (int i = 0; i < KEYMAX; i++)
	{
		this->getKeyUp().set(i, false);
		this->getKeyDown().set(i, false);
	}

	return S_OK;
}

void keyManager::release()
{
}

bool keyManager::isOnceKeyDown(int key)
{
	// 함수 호출 시점에 가상키가 어떤 상태인지 확인이 가능하다
	// 1. 0x0000 => 이전에 누른 적이 없고 호출시점에도 눌려있지 않음
	// 2. 0x0001 => 이전에 누른 적이 있고 호출시점에는 눌려있지 않음
	// 3. 0x8000 => 이전에 누른 적이 없고 호출시점에는 눌려있는 상태
	// 4. 0x8001 => 이전에 누른 적이 있고 호출시점에도 눌려있는 상태
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!this->getKeyDown()[key])
		{
			this->setKeyDown(key, true);
			return true;
		}
	}
	else
		this->setKeyDown(key, false);

	return false;
}

bool keyManager::isOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
		this->setKeyUp(key, true);
	else
	{
		if (this->getKeyUp()[key])
		{
			this->setKeyUp(key, false);
			return true;
		}
	}

	return false;
}

bool keyManager::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) return true;

	return false;
}

bool keyManager::isToggleKey(int key)
{
	if (GetAsyncKeyState(key) & 0x0001) return true;

	return false;
}

keyManager::keyManager()
{
}


keyManager::~keyManager()
{
}
