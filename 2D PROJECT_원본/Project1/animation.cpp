#include "stdafx.h"
#include "animation.h"


animation::animation()
	: m_fElapsedSec(0)
	, m_fFrameUpdateSec(0)
	, m_isLoop(false)
	, m_isPlaying(false)
	, m_nFrameHeight(0)
	, m_nFrameNum(0)
	, m_nFrameWidth(0)
	, m_nNowPlayIdx(0)
{
}


animation::~animation()
{
}

HRESULT animation::init(int totalWidth, int totalHeight, int frameWidth, int frameHeight)
{
	// 가로 프레임 수
	m_nFrameWidth = frameWidth;
	int numWidth = totalWidth / m_nFrameWidth;

	// 세로 프레임 수
	m_nFrameHeight = frameHeight;
	int numHeight = totalHeight / m_nFrameHeight;

	// 총 프레임 수
	m_nFrameNum = numWidth * numHeight;

	// 프레임 위치 리스트 셋팅
	m_vecFrameList.clear();

	for (int i = 0; i < numHeight; i++)
	{
		for (int j = 0; j < numWidth; j++)
		{
			POINT framePos;
			framePos.x = j * m_nFrameWidth;
			framePos.y = i * m_nFrameHeight;

			// 프레임 위치 리스트에 추가한다
			m_vecFrameList.push_back(framePos);
		}
	}

	return S_OK;
}

HRESULT animation::init(int totalWidth, int totalHeight, int frameWidth, int frameHeight, int startY)
{
	// 가로 프레임 수
	m_nFrameWidth = frameWidth;
	int numWidth = totalWidth / m_nFrameWidth;

	// 세로 프레임 수
	m_nFrameHeight = frameHeight;
	int numHeight = totalHeight / m_nFrameHeight;

	// 총 프레임 수
	m_nFrameNum = numWidth * numHeight;

	// 프레임 위치 리스트 셋팅
	m_vecFrameList.clear();

	for (int i = 0; i < numHeight; i++)
	{
		for (int j = 0; j < numWidth; j++)
		{
			POINT framePos;
			framePos.x = j * m_nFrameWidth;
			framePos.y = i * m_nFrameHeight + startY;

			// 프레임 위치 리스트에 추가한다
			m_vecFrameList.push_back(framePos);
		}
	}

	return S_OK;
}

void animation::setDefPlayFrame(bool reverse, bool loop)
{
	// 루프 여부
	m_isLoop = loop;

	// 플레이 리스트 클리어 (어떤 프레임을 재생할 것인가)
	m_vecPlayList.clear();

	// 정 -> 역 <- 애니메이션
	if (reverse)
	{
		for (int i = 0; i < m_nFrameNum; i++)
		{
			m_vecPlayList.push_back(i);
		}

		for (int i = m_nFrameNum - 1; i >= 0; i--)
		{
			m_vecPlayList.push_back(i);
		}

	}
	// 정 -> 애니메이션
	else
	{
		for (int i = 0; i < m_nFrameNum; i++)
		{
			m_vecPlayList.push_back(i);
		}
	}

}

void animation::setPlayFrame(int * arrPlay, int arrLen, bool loop)
{
	m_isLoop = loop;

	m_vecPlayList.clear();

	for (int i = 0; i < arrLen; i++)
	{
		// m_vecPlayList에 들어갈 원소가 int 타입이므로
		// 배열의 인덱스 값을 통해 int data를 추가한다
		m_vecPlayList.push_back(arrPlay[i]);
	}
}

void animation::setPlayFrameReverse(int start, int end, bool reverse, bool loop)
{
	m_isLoop = loop;

	m_vecPlayList.clear();

	if (start == end)
	{
		return;
	}

	// 역 <- 애니메이션

	for (int i = end - 1; i >= start; i--)
	{
		m_vecPlayList.push_back(i);
	}

	if (reverse)
	{ 
		for (int i = start; i < end; i++)
		{
			m_vecPlayList.push_back(i);
		}
	}
}

void animation::setPlayFrame(int start, int end, bool reverse, bool loop)
{
	m_isLoop = loop;

	m_vecPlayList.clear();

	if (start == end)
	{
		return;
	}

	if (start > end)
	{
		if (reverse)
		{
			// 정->
			for (int i = start; i < m_nFrameNum; i++)
			{
				m_vecPlayList.push_back(i);
			}
			for (int i = 0; i < end; i++)
			{
				m_vecPlayList.push_back(i);
			}

			// 역 <-
			for (int i = end - 1; i >= 0; i--)
			{
				m_vecPlayList.push_back(i);
			}
			for (int i = m_nFrameNum - 1; i >= start; i--)
			{
				m_vecPlayList.push_back(i);
			}
		}
		else
		{
			for (int i = start; i < m_nFrameNum; i++)
			{
				m_vecPlayList.push_back(i);
			}
			for (int i = 0; i < end; i++)
			{
				m_vecPlayList.push_back(i);
			}
		}

	}
	else
	{
		// 정 -> 역 <- 애니메이션
		if (reverse)
		{
			for (int i = start; i < end; i++)
			{
				m_vecPlayList.push_back(i);
			}

			for (int i = end - 1; i >= start; i--)
			{
				m_vecPlayList.push_back(i);
			}

		}
		// 정 -> 애니메이션
		else
		{
			for (int i = start; i < end; i++)
			{
				m_vecPlayList.push_back(i);
			}
		}
	}
}

void animation::setFPS(int fps)
{
	m_fFrameUpdateSec = 1.0f / (float)fps;
}

void animation::frameUpdate(float elapsedTime)
{
	if (m_isPlaying)
	{
		m_fElapsedSec += elapsedTime;

		if (m_fElapsedSec >= m_fFrameUpdateSec)
		{
			m_nNowPlayIdx++;
			m_fElapsedSec -= m_fFrameUpdateSec;	// 갱신 오차를 줄여준다

			if (m_nNowPlayIdx == m_vecPlayList.size())
			{
				// 루프 플레이면
				if (m_isLoop)
				{
					m_nNowPlayIdx = 0;
				}
				else
				{
					m_nNowPlayIdx--;
					m_isPlaying = false;
				}
			}
		}
	}
}

void animation::start()
{
	m_isPlaying = true;
	m_nNowPlayIdx = 0;
}

void animation::stop()
{
	m_isPlaying = false;
	m_nNowPlayIdx = 0;
}

void animation::pause()
{
	m_isPlaying = false;
}

void animation::resume()
{
	m_isPlaying = true;
}
