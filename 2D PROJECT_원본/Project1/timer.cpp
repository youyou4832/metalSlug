#include "stdafx.h"
#include "timer.h"
#include <mmsystem.h>

#pragma comment (lib, "winmm.lib")


HRESULT timer::init()
{
	// ���� Ÿ�̸Ӱ� �����ȴٸ� !!
	if (QueryPerformanceFrequency(
		(LARGE_INTEGER*)&m_periodFrequency))
	{
		QueryPerformanceCounter(
			(LARGE_INTEGER*)&m_lastTime);
		m_isHardware = true;

		m_timeScale = 1.0f / m_periodFrequency;
	}
	else
	{
		m_lastTime = timeGetTime();
		m_isHardware = false;

		m_timeScale = 0.001f;
	}


	m_frameRate = 0;
	m_fpsFrameCount = 0;
	m_fpsTimeElapsed = 0;
	m_currTime = 0;
	m_worldTime = 0;
	m_timeElapsed = 0;

	return S_OK;
}

void timer::tick(float lockFPS)		// lockFPS : 30 or 60
{
	// ���� �ð� ����
	if (m_isHardware)
	{
		QueryPerformanceCounter(
			(LARGE_INTEGER*)&m_currTime);
	}
	else
	{
		m_currTime = timeGetTime();
	}
	// �� ������ ���� �ð� ����
	m_timeElapsed = (m_currTime - m_lastTime) * m_timeScale;

	// ������������ ������
	if (lockFPS > 0.0f)
	{
		// �� �������� ����Ǵ� �ð��� �������Ƿ�
		// �� �ð����� ���� �ڵ带 �ݺ���Ų��
		while (m_timeElapsed < (1.0f / lockFPS))
		{
			if (m_isHardware)
			{
				QueryPerformanceCounter(
					(LARGE_INTEGER*)&m_currTime);
			}
			else
			{
				m_currTime = timeGetTime();
			}
			m_timeElapsed = (m_currTime - m_lastTime) * m_timeScale;
		}
	}

	m_lastTime = m_currTime;// timeGetTime();
	m_worldTime += m_timeElapsed;

	m_fpsTimeElapsed += m_timeElapsed;
	m_fpsFrameCount++;

	// ������ �ʱ�ȭ�� 1�ʸ��� �����Ѵ�
	if (m_fpsTimeElapsed > 1.0f)
	{
		m_frameRate = m_fpsFrameCount;
		m_fpsFrameCount = 0;
		m_fpsTimeElapsed = 0;
	}
}

timer::timer()
{
}


timer::~timer()
{
}
