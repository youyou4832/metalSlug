#include "stdafx.h"
#include "timeManager.h"
#include "timer.h"


HRESULT timeManager::init()
{
	m_timer = new timer;
	m_timer->init();

	return S_OK;
}

void timeManager::release()
{
	delete m_timer;
}

void timeManager::update(float lockFPS)
{
	if (m_timer)
		m_timer->tick(lockFPS);
}

void timeManager::render(HDC hdc)
{
	char szText[256];

	// TRANSPARENT : ����, OPAQUE : ������
	SetBkMode(hdc, TRANSPARENT);

	SetTextColor(hdc, RGB(255, 0, 255));

	if (m_timer)
	{
		// ������
		sprintf_s(szText, "FramePerSec : %d",
			m_timer->getFrameRate());
		TextOut(hdc, 5, 5, szText, strlen(szText));

		// ����Ÿ��
		sprintf_s(szText, "WorldTime : %f",
			m_timer->getWorldTime());
		TextOut(hdc, 5, 30, szText, strlen(szText));

		// ����Ÿ��
		sprintf_s(szText, "ElapsedTime : %f",
			m_timer->getElapsedTime());
		TextOut(hdc, 5, 55, szText, strlen(szText));
	}
}

timeManager::timeManager()
{
}


timeManager::~timeManager()
{
}
