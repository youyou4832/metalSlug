#pragma once

#include "singletonBase.h"
#include <bitset>

using namespace std;

#define KEYMAX 256

class keyManager : public singletonBase<keyManager>
{
private:
	bitset<KEYMAX> m_keyUp;
	bitset<KEYMAX> m_keyDown;

public:
	HRESULT init();
	void release();

	bool isOnceKeyDown(int key);	// Ű�� �ѹ��� ������ ��
	bool isOnceKeyUp(int key);		// Ű�� ������ ���� ��
	bool isStayKeyDown(int key);	// Ű�� ������ ���� ��
	bool isToggleKey(int key);		// ��Ÿ

	bitset<KEYMAX> getKeyUp() { return m_keyUp; }
	bitset<KEYMAX> getKeyDown() { return m_keyDown; }

	void setKeyUp(int key, bool state) { m_keyUp.set(key, state); }
	void setKeyDown(int key, bool state) { m_keyDown.set(key, state); }

	keyManager();
	~keyManager();
};

