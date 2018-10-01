#include "stdafx.h"
#include "pixelCollision.h"


HRESULT pixelCollision::init()
{
	IMAGEMANAGER->addImage("image/background.bmp", 600, 800);
	
	m_pImg = IMAGEMANAGER->findImage("image/background.bmp");

	m_position.x = WINSIZEX / 2;
	m_position.y = WINSIZEY / 2 - 100;

	m_rc = RectMakeCenter(m_position.x, m_position.y, m_pImg->getWidth(), m_pImg->getHeight());

	m_currY = m_position.y + m_pImg->getHeight() / 2;

	return S_OK;
}

void pixelCollision::release()
{
}

void pixelCollision::update()
{
	m_position.y += 3;

	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && m_rc.left > 0)
	{
		m_position.x -= 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && m_rc.right < WINSIZEX)
	{
		m_position.x += 3;
	}

	m_currY = m_position.y + m_pImg->getHeight() / 2;

	for (int i = m_currY - 50; i < m_currY + 50; ++i)
	{
		COLORREF color = GetPixel(m_pImg->getMemDC(), m_position.x, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		//if (r == 255 && g == 0 && b == 255)
		//{
		//	m_position.y = i - m_pImgBall->getHeight();
		//}

		if (!(r == 255 && g == 0 && b == 255))
		{
			m_position.y = i - m_pImg->getHeight();
			break;
		}
	}
}

void pixelCollision::render(HDC hdc)
{
	IMAGEMANAGER->findImage("image/background.bmp")->render(hdc, 0, 0);
	m_pImg->render(hdc, 0, 0);
}

pixelCollision::pixelCollision()
{
}


pixelCollision::~pixelCollision()
{
}
