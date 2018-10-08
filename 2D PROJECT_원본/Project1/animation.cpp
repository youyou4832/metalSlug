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
	// ���� ������ ��
	m_nFrameWidth = frameWidth;
	int numWidth = totalWidth / m_nFrameWidth;

	// ���� ������ ��
	m_nFrameHeight = frameHeight;
	int numHeight = totalHeight / m_nFrameHeight;

	// �� ������ ��
	m_nFrameNum = numWidth * numHeight;

	// ������ ��ġ ����Ʈ ����
	m_vecFrameList.clear();

	for (int i = 0; i < numHeight; i++)
	{
		for (int j = 0; j < numWidth; j++)
		{
			POINT framePos;
			framePos.x = j * m_nFrameWidth;
			framePos.y = i * m_nFrameHeight;

			// ������ ��ġ ����Ʈ�� �߰��Ѵ�
			m_vecFrameList.push_back(framePos);
		}
	}

	return S_OK;
}

HRESULT animation::init(int totalWidth, int totalHeight, int frameWidth, int frameHeight, int startY)
{
	// ���� ������ ��
	m_nFrameWidth = frameWidth;
	int numWidth = totalWidth / m_nFrameWidth;

	// ���� ������ ��
	m_nFrameHeight = frameHeight;
	int numHeight = totalHeight / m_nFrameHeight;

	// �� ������ ��
	m_nFrameNum = numWidth * numHeight;

	// ������ ��ġ ����Ʈ ����
	m_vecFrameList.clear();

	for (int i = 0; i < numHeight; i++)
	{
		for (int j = 0; j < numWidth; j++)
		{
			POINT framePos;
			framePos.x = j * m_nFrameWidth;
			framePos.y = i * m_nFrameHeight + startY;

			// ������ ��ġ ����Ʈ�� �߰��Ѵ�
			m_vecFrameList.push_back(framePos);
		}
	}

	return S_OK;
}

void animation::setDefPlayFrame(bool reverse, bool loop)
{
	// ���� ����
	m_isLoop = loop;

	// �÷��� ����Ʈ Ŭ���� (� �������� ����� ���ΰ�)
	m_vecPlayList.clear();

	// �� -> �� <- �ִϸ��̼�
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
	// �� -> �ִϸ��̼�
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
		// m_vecPlayList�� �� ���Ұ� int Ÿ���̹Ƿ�
		// �迭�� �ε��� ���� ���� int data�� �߰��Ѵ�
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

	// �� <- �ִϸ��̼�

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
			// ��->
			for (int i = start; i < m_nFrameNum; i++)
			{
				m_vecPlayList.push_back(i);
			}
			for (int i = 0; i < end; i++)
			{
				m_vecPlayList.push_back(i);
			}

			// �� <-
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
		// �� -> �� <- �ִϸ��̼�
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
		// �� -> �ִϸ��̼�
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
			m_fElapsedSec -= m_fFrameUpdateSec;	// ���� ������ �ٿ��ش�

			if (m_nNowPlayIdx == m_vecPlayList.size())
			{
				// ���� �÷��̸�
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
