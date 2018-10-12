#include "stdafx.h"
#include "bridge.h"


HRESULT bridge::init()
{
	for (int i = 0; i < 19; i++)
	{
		m_bridge[i].m_pimgBridege = IMAGEMANAGER->addImage("bridgetile", "image/map/tile_bridge.bmp",
			950, 69, true, RGB(255, 0, 255));
		m_bridge[i].m_pimgPixels = IMAGEMANAGER->addImage("Pixels", "image/map/pixels.bmp",
			950, 69, true, RGB(255, 0, 255));
		
		m_bridge[i].m_isAilve = true;

		if (i == 0)
		{
			m_bridgeDestX[i] = 0;
		}
		else if (i == 1)
		{
			m_bridgeDestX[i] = 150;
		}
		else
		{
			m_bridgeDestX[i] = m_bridgeDestX[i - 1] + 90;
		}

		if (i == 0)
		{
			m_bridgeSourX[i] = 0;
		}

		else
		{
			m_bridgeSourX[i] = m_bridgeSourX[i - 1] + 50;
		}
		
	}
	
	m_Scalar = 3;
	
	//m_bridgeDestX[BRUDEGE_NUM] = {0, 150, 240, 330, 410 ,500 ,590 ,680 ,770 ,860 ,950 ,1040 ,1130 ,1220, 1310, 1400, 1490, 1580, 1670};
	m_bridgeDestY = WINSIZEY - (69 * m_Scalar);

	

	m_bridgeSourX[BRUDEGE_NUM];
	m_bridgeSourY = 0;

	m_bridgeWidth = 50;
	m_bridgeHeight = 69;
	

	

	m_PosX = 900;

	
	return S_OK;
}

void bridge::release()
{

}

void bridge::update()
{
	m_PosX -= 3;

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		m_Destruction += 48;
	}

	if (m_Destruction == 768)
	{
		m_Destruction = 0;
		
	}
}



void bridge::render(HDC hdc)
{

	
	for (int i = 0; i < 19; i++)
	{
		m_bridge[i].m_pimgBridege->render(hdc, m_PosX + m_bridgeDestX[i], m_bridgeDestY,
			m_bridgeSourX[i], m_bridgeSourY, m_bridgeWidth, m_bridgeHeight, m_Scalar);

		//픽셀 충돌 확인
		m_bridge[i].m_pimgPixels->render(hdc, m_PosX + m_bridgeDestX[i], m_bridgeDestY,
			m_bridgeSourX[i], m_bridgeSourY, m_bridgeWidth, m_bridgeHeight, m_Scalar);
	}
	
}

bridge::bridge()
{
}


bridge::~bridge()
{
}
