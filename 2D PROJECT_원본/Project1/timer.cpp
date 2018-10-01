#include "stdafx.h"
#include "timer.h"
#include <mmsystem.h>

#pragma comment (lib, "winmm.lib")


HRESULT timer::init()
{
	// 고성능 타이머가 지원된다면 !!
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
	// 현재 시간 저장
	if (m_isHardware)
	{
		QueryPerformanceCounter(
			(LARGE_INTEGER*)&m_currTime);
	}
	else
	{
		m_currTime = timeGetTime();
	}
	// 한 프레임 진행 시간 저장
	m_timeElapsed = (m_currTime - m_lastTime) * m_timeScale;

	// 고정프레임이 있으면
	if (lockFPS > 0.0f)
	{
		// 한 프레임이 진행되는 시간이 정해지므로
		// 그 시간동안 위의 코드를 반복시킨다
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

	// 프레임 초기화를 1초마다 진행한다
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
