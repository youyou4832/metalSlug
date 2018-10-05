#include "stdafx.h"
#include "boss.h"
#include "missile.h"
#include "missileManager.h"
#include "animation.h"

HRESULT boss::init()
{
	//보스 상태 초기화
	m_isAppear = true;
	m_isAlive = false;

	m_state = NOMAL;
	m_move = MOVE;

	//보스 이미지 삽입(230*207 12씩 총 7개)
	m_pimgBoss = IMAGEMANAGER->addImage("move", "image/boss/Boss.bmp",
		2760, 1449, true, RGB(255, 0, 255));
	m_pMoveAni = new animation;
	m_pMoveAni->init(m_pimgBoss->getWidth(), m_pimgBoss->getHeight(),
		230, 207);
	m_pMoveAni->setPlayFrame(1, 12, false, true);
	m_pMoveAni->setFPS(15);

	m_nCurrFrameX = 0;
	m_nCurrFrameY = 0;

	m_fSpeed = 5.0f;
	m_upspeed = 3.0;

	m_fX = -20;
	m_fY = 1035;

	m_nCount = 0;

	m_rc = RectMakeCenter(m_fX, m_fY, m_pimgBoss->getWidth(), m_pimgBoss->getHeight());
	


	m_nCurrHP = m_nMaxHP = 100;
	return S_OK;
}

void boss::release()
{
	
}

void boss::update()
{
	if (m_isAppear == true && m_fY >= -10) //보스 등장씬(이펙트 아직 없음) 
	{
		m_fY -= m_upspeed;
		m_upspeed += 0.8;

		if (m_fY <= 0)
		{
			m_isAppear = false; //등장후 씬이 움직이게 하기 위해
			m_isAlive = true;
			m_pMoveAni->start();
		}

	}

	move();

	/*if (m_fX  >-380 && m_fX < WINSIZEX / 2.5)
	{
		m_fX -= m_fSpeed;
	}*/

	m_pMoveAni->frameUpdate(TIMEMANAGER->getElapsedTime());
}

void boss::render(HDC hdc)
{

	m_pimgBoss->aniRender(hdc, m_fX, m_fY, m_pMoveAni,4.0);
	m_rc = RectMakeCenter(m_fX, m_fY, m_pimgBoss->getWidth(), m_pimgBoss->getHeight());

}

void boss::move()
{
	if (m_state == NOMAL)
	{

		if (m_isAlive && !m_isAppear)
		{
			if (m_move == MOVE) // 제자리 걸음
			{
				m_fX += m_fSpeed;

				if (m_nCount == 30)
				{
					m_move = BACKMOVE;

				}
				m_nCount += 1;
			}

			if (m_move == BACKMOVE && (m_fX >= -280 && m_fX < WINSIZEX / 2.5))
			{
				m_nCount = 0;
				m_fX -= m_fSpeed;

				if (m_fX == -280) m_move = RUSHMOVE;
				//m_move = SMALLMOVE;
			}

			//if (m_move == IDLEMOVE &&(m_fX >= -280 && m_fX < WINSIZEX / 2.5))
			//{
			//	m_fX -= m_fSpeed;

			//	if (m_fX == -280) m_move = RUSHMOVE;
			//		//m_move = SMALLMOVE;
			//}

			if (m_move == SMALLMOVE && m_fX < 100)
			{
				int speedup = 2;
				m_fX += (m_fSpeed + speedup);

				if (m_fX >= 100)
					m_move = MOVE;

			}

			if (m_move == RUSHMOVE && m_fX < 250)
			{
				int speedup = 2;
				m_fX += (m_fSpeed + speedup);

				if (m_fX >= 250)
					m_move = MOVE;

			}

		}

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


