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
	// �Լ� ȣ�� ������ ����Ű�� � �������� Ȯ���� �����ϴ�
	// 1. 0x0000 => ������ ���� ���� ���� ȣ��������� �������� ����
	// 2. 0x0001 => ������ ���� ���� �ְ� ȣ��������� �������� ����
	// 3. 0x8000 => ������ ���� ���� ���� ȣ��������� �����ִ� ����
	// 4. 0x8001 => ������ ���� ���� �ְ� ȣ��������� �����ִ� ����
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
