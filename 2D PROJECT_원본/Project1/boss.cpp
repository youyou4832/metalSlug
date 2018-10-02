#include "stdafx.h"
#include "boss.h"
#include "missile.h"
#include "missileManager.h"
#include "animation.h"

HRESULT boss::init()
{
	//보스 상태 초기화
	m_isAlive = true;
	m_state = NOMAL;
	m_attack = SMASH;

	//보스 이미지 삽입(230*207 12씩 총 7개)
	m_pimgBoss = IMAGEMANAGER->addImage("move", "image/boss/boss.bmp",
		2760, 1449, 12, 1, true, RGB(255, 0, 255));
	m_pMoveAni = new animation;
	m_pMoveAni->init(m_pimgBoss->getWidth(), m_pimgBoss->getHeight(),
		m_pimgBoss->getFrameWidth(), m_pimgBoss->getFrameHeight());
	m_pMoveAni->setPlayFrame(false, true);
	m_pMoveAni->setFPS(15);

	m_nCurrFrameX = 0;
	m_nCurrFrameY = 0;

	m_fSpeed = 5.0f;
	m_fX = 30;
	m_fY = WINSIZEY / 2;

	m_rc = RectMakeCenter(m_fX, m_fY, m_pimgBoss->getWidth() / 4, m_pimgBoss->getHeight() / 4);
	m_nCurrHP = m_nMaxHP = 100;
	return S_OK;
}

void boss::release()
{
}

void boss::update()
{
	if (isAlive == true)
	{
		m_pMoveAni->start();
	}
}

void boss::render(HDC hdc)
{
	if (isAlive == true)
	{
		m_pimgBoss->aniRender(hdc, (m_fX - m_pimgBoss->getFrameWidth() / 2), m_fY - (m_pimgBoss->getFrameHeight() / 2), m_pMoveAni);
	}
}

void boss::damaged(int damage)
{
}

void boss::diechack()
{
}

boss::boss()
{
}


boss::~boss()
{
}


