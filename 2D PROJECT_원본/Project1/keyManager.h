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

	bool isOnceKeyDown(int key);	// 키를 한번만 눌렀을 때
	bool isOnceKeyUp(int key);		// 키를 눌렀다 뗐을 때
	bool isStayKeyDown(int key);	// 키를 누르고 있을 때
	bool isToggleKey(int key);		// 연타

	bitset<KEYMAX> getKeyUp() { return m_keyUp; }
	bitset<KEYMAX> getKeyDown() { return m_keyDown; }

	void setKeyUp(int key, bool state) { m_keyUp.set(key, state); }
	void setKeyDown(int key, bool state) { m_keyDown.set(key, state); }

	keyManager();
	~keyManager();
};

