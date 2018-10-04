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
	m_pimgBoss = IMAGEMANAGER->addImage("move", "image/boss/Boss.bmp",
		2760, 1449, true, RGB(255, 0, 255));
	m_pMoveAni = new animation;
	m_pMoveAni->init(m_pimgBoss->getWidth(), m_pimgBoss->getHeight(),
		230, 207);
	m_pMoveAni->setPlayFrame(0, 12, false, true);
	m_pMoveAni->setFPS(15);

	m_nCurrFrameX = 0;
	m_nCurrFrameY = 0;

	m_fSpeed = 5.0f;
	m_fX = 0;
	m_fY = WINSIZEY-830;

	if (m_isAlive == true)
	{
		m_pMoveAni->start();
	}
	/*m_rc = RectMakeCenter(m_fX, m_fY, m_pimgBoss->getWidth() / 4, m_pimgBoss->getHeight() / 4);
	m_nCurrHP = m_nMaxHP = 100;*/
	return S_OK;
}

void boss::release()
{

}

void boss::update()
{	
	m_pMoveAni->frameUpdate(TIMEMANAGER->getElapsedTime());	
}

void boss::render(HDC hdc)
{

	m_pimgBoss->aniRender(hdc, m_fX, m_fY, m_pMoveAni,4);

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


