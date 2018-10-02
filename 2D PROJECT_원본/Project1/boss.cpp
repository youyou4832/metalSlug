#include "stdafx.h"
#include "boss.h"
#include "missileManager.h"

boss::boss()
{
}


boss::~boss()
{
}

HRESULT boss::init()
{
	m_nCount = 0;
	m_nCurrFrameX = 0;
	m_nCurrFrameY = 0;
	m_pImg = NULL;

	ZeroMemory(&m_rc, sizeof(m_rc));

	m_pMissileMgr = new missileManager;
	m_pMissileMgr->init(10);

	m_nFireCount = 0;
	m_nRandFireCount = 10;
	m_fX = 0;
	m_fY = 0;
	

	isAlive = true;
	return S_OK;
}

HRESULT boss::init(const char * szFileName, POINT position)
{
	m_nCount = 0;
	m_nCurrFrameX = 0;
	m_nCurrFrameY = 0;
	std::string strFile = std::string(szFileName);
	/*m_pImg = IMAGEMANAGER->addImage(/*이미지이름,
									실제이미지저장된 폴터위치,
									width, hight,
									frameX, frameY,
									trans, RGB(255, 0, 255));*/

	m_rc = RectMakeCenter(position.x, position.y,
		m_pImg->getFrameWidth(), m_pImg->getFrameHeight());

	m_pMissileMgr = new missileManager;
	m_pMissileMgr->init(0);
	m_nFireCount = 0;
	m_nRandFireCount = 0;
	m_fX = position.x;
	m_fY = position.y;
	return S_OK;
}

void boss::release()
{
	if (m_pMissileMgr)
	{
		m_pMissileMgr->release();
		delete m_pMissileMgr;
	}
}

void boss::update()
{
	if (isAlive == true)
	{
		
		if (m_pImg)
		{
			
		}

		fire();
		move();
		if (m_pMissileMgr)
			m_pMissileMgr->update();
	}
}

void boss::render(HDC hdc)
{
	if (isAlive == true)
	{
		if (m_pImg)
		{
			/*m_pImg->frameRender(hdc,
				m_fX - m_pImg->getFrameWidth() / 2, m_fY - m_pImg->getFrameHeight() / 2,
				m_nCurrFrameX, m_nCurrFrameY)*/;
		}

		if (m_pMissileMgr)
		{

		}

		fire();
		move();
	}
}

void boss::move()
{
	/*m_rc = RectMakeCenter(m_fX, m_fY,
		m_pImg->getFrameWidth(), m_pImg->getFrameHeight());*/
}

void boss::fire()
{
}
