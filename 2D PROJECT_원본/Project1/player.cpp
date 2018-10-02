#include "stdafx.h"
#include "player.h"
#include "animation.h"

HRESULT player::init()
{
	m_upper.pAni = new animation;
	m_lower.pAni = new animation;

	switch (m_nSelectCharacter)
	{
	case 0:
		IMAGEMANAGER->addImage("", "", 100, 100, true, RGB(255, 0, 255));	// 플레이어 1
		break;

	case 1:
		IMAGEMANAGER->addImage("", "", 100, 100, true, RGB(255, 0, 255));	// 플레이어 2
		break;
	}

	m_upper.pImg;
	m_upper.pAni;
	m_lower.pImg;
	m_lower.pAni;

	m_upper.pImg->setX(0);
	m_upper.pImg->setY(0);
	m_lower.pImg->setX(0);
	m_lower.pImg->setY(0);

	m_fSpeed = 5.0f;
	m_fJumpSpeed = 10.0f; 
	m_fGravity = 0;
	m_nActUpper = UPPER_Idle;
	m_nActLower = LOWER_Idle;
	m_nDir = DIR_Right;

	ZeroMemory(&m_upper.rc, NULL);
	ZeroMemory(&m_lower.rc, NULL);

	return S_OK;
}

void player::update()
{
	move();
	actSet();

	m_upper.rc = RectMakeCenter(m_upper.pImg->getX(), m_upper.pImg->getY(), 
		m_upper.pImg->getFrameWidth(), m_upper.pImg->getFrameHeight());
	
	if(m_nActLower != LOWER_NULL)
		m_lower.rc = RectMakeCenter(m_lower.pImg->getX(), m_lower.pImg->getY(),
			m_lower.pImg->getFrameWidth(), m_lower.pImg->getFrameHeight());
}

void player::actSet()
{
	if (g_ptMouse.x <= m_upper.pImg->getX())		// 마우스 포인터가 캐릭터 왼쪽에 있을 경우
		m_nDir = DIR_Left;

	else if (g_ptMouse.x > m_upper.pImg->getX())	// 마우스 포인터가 캐릭터 오른쪽에 있을 경우
		m_nDir = DIR_Right;

	// 행동에 따라 애니메이션 프레임을 지정함

	// 상체

	// 하체
}

void player::move()
{
	if (KEYMANAGER->isStayKeyDown('A') && m_upper.pImg->getX() > 0)
	{
		m_upper.pImg->setX(m_upper.pImg->getX() - m_fSpeed); 

		if (m_nActLower != LOWER_NULL)
			m_lower.pImg->setX(m_lower.pImg->getX() - m_fSpeed);
	}
	if (KEYMANAGER->isStayKeyDown('D') && m_upper.pImg->getX() < WINSIZEX)
	{
		m_upper.pImg->setX(m_upper.pImg->getX() + m_fSpeed);

		if (m_nActLower != LOWER_NULL)
			m_lower.pImg->setX(m_lower.pImg->getX() + m_fSpeed);
	}

	// 공격 (마우스 포인터)
}

void player::release()
{
	SAFE_DELETE(m_upper.pAni);
	SAFE_DELETE(m_lower.pAni);
}

void player::render(HDC hdc)
{
	m_upper.pImg->aniRender(hdc, m_upper.pImg->getX(), m_upper.pImg->getY(), m_upper.pAni);
	m_lower.pImg->aniRender(hdc, m_lower.pImg->getX(), m_lower.pImg->getY(), m_lower.pAni);
}
player::player()
{
}


player::~player()
{
}
