#include "stdafx.h"
#include "boss.h"
#include "missile.h"
#include "missileManager.h"
#include "animation.h"

HRESULT boss::init()
{
	//보스 상태 초기화
	m_isAppear = true;
	m_isAlive = true;
	m_isChange = false;

	m_state = NOMAL;
	m_move = MOVE;
	m_pattonChack = 0;
	//보스 이미지 삽입(230*207 12씩 총 7개)
	m_pimgBoss = IMAGEMANAGER->addImage("move", "image/boss/Boss.bmp",
		2760, 1449, true, RGB(255, 0, 255));
	m_pMoveAni = new animation;
	m_pMoveAni->init(m_pimgBoss->getWidth(), m_pimgBoss->getHeight(),
		230, 207);
	m_pMoveAni->setPlayFrame(1, 12, false, true);
	m_pMoveAni->setFPS(15);

	//보스 변신
	m_pChangeBoss = new animation;
	m_pChangeBoss->init(m_pimgBoss->getWidth(), m_pimgBoss->getHeight(),
		230, 207);
	m_pChangeBoss->setPlayFrame(12, 24);
	m_pChangeBoss->setFPS(15);

	//보스 분노상태
	m_pRageBoss = new animation;
	m_pRageBoss->init(m_pimgBoss->getWidth(), m_pimgBoss->getHeight(),
		230, 207);
	m_pRageBoss->setPlayFrame(24, 36, false , true);
	m_pRageBoss->setFPS(15);

	//보스 죽음
	m_pDieAni = new animation;
	m_pDieAni->init(m_pimgBoss->getWidth(), m_pimgBoss->getHeight(),
		230, 207);
	m_pDieAni->setPlayFrame(72, 84);
	m_pDieAni->setFPS(15);

	m_pCannon = new missileManager;
	m_pCannon->init(10);

	m_nCurrFrameX = 0;
	m_nCurrFrameY = 0;

	m_fSpeed = 5.0f;
	m_upspeed = 3.0;

	m_fX = -20;
	m_fY = 1035;

	m_nCurrHP = m_nMaxHP = 10;
	//m_rc = RectMakeCenter(m_fX, m_fY, m_pimgBoss->getWidth(), m_pimgBoss->getHeight());
	
	//m_rc = RectMake(m_fX + 100, m_fY + 50, (m_pimgBoss->getWidth() + 400) / 4, m_pimgBoss->getHeight());


	return S_OK;
}

void boss::release()
{
	SAFE_DELETE(m_pMoveAni);
	SAFE_DELETE(m_pChangeBoss);
	SAFE_DELETE(m_pRageBoss);
	SAFE_DELETE(m_pDieAni);
	SAFE_DELETE(m_pCannon);
}

void boss::update()
{
	change(m_isChange);

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		damaged(1);
	}

	m_rc = RectMake(m_fX+100, m_fY+50, (m_pimgBoss->getWidth()+400)/4, m_pimgBoss->getHeight());
	
	move();

	m_pMoveAni->frameUpdate(TIMEMANAGER->getElapsedTime());
	m_pDieAni->frameUpdate(TIMEMANAGER->getElapsedTime());
	m_pRageBoss->frameUpdate(TIMEMANAGER->getElapsedTime());
	m_pChangeBoss->frameUpdate(TIMEMANAGER->getElapsedTime());
}

void boss::render(HDC hdc)
{
	if (m_isAlive)
	{
		if(m_state == NOMAL)
		m_pimgBoss->aniRender(hdc, m_fX, m_fY, m_pMoveAni, 4.0);

		else if (m_state == CHANGE)
		{
			m_pimgBoss->aniRender(hdc, m_fX, m_fY, m_pChangeBoss, 4.0);
		}

		else if (m_state == RAGE)
		{
			m_pimgBoss->aniRender(hdc, m_fX, m_fY, m_pRageBoss, 4.0);
		}
	}

	else
	{
		m_pimgBoss->aniRender(hdc, m_fX, m_fY, m_pDieAni, 4.0);
	}
	//Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);

}

void boss::move()
{
	if (m_isAppear == true && m_fY >= -10) //보스 등장씬(이펙트 아직 없음) 
	{
		m_fY -= m_upspeed;
		m_upspeed += 0.8;

		if (m_fY <= 0)
		{
			m_isAppear = false; //등장후 씬이 움직이게 하기 위해
			m_pMoveAni->start();
		}

	}

	if (m_isAlive && !m_isAppear)
	{
		if (m_state == NOMAL || m_state == RAGE)
		{
			++b_pattern.count;
			if (m_move == MOVE) // 등장이 끝난후 잠깐 제자리 걸음(사실상 정지)
			{
				//m_fX += m_fSpeed;
				
				if (b_pattern.count%5 == 0)
				{
					++b_pattern.index;
					if (b_pattern.index == 10)
					{
						b_pattern.count = 0;
						b_pattern.index = 0;
						m_move = S_BACKMOVE;
					}
				}
			}

			if (m_move == S_BACKMOVE) // 뒤로 조금 이동
			{
				if (m_pattonChack == 0)
				{
					if (m_fX >= -900)
					{
						m_fX -= m_fSpeed;
					}

					else
					{
						if (b_pattern.count % 5 == 0)
						{
							++b_pattern.index;
							if (b_pattern.index == 15)
							{
								b_pattern.count = 0;
								b_pattern.index = 0;
								m_move = S_RUSHMOVE;

							}
						}
					}
				}

				if (m_pattonChack == 1)// 뒤로 조금 이동
				{
					if (m_fX >= -1000)
					{
						m_fX -= m_fSpeed;
					}

					else
					{
						if (b_pattern.count % 5 == 0)
						{
							++b_pattern.index;
							if (b_pattern.index == 25)
							{
								b_pattern.count = 0;
								b_pattern.index = 0;
								m_move = P_RUSHMOVE;

							}
						}
					}
				}
			}

			if (m_move == S_RUSHMOVE) // 조금만 돌진
			{

				if (m_fX < 180 )
				{
					int plusup[] = { 1, 3, 5 };
					for (int i = 0; i < 3; i++)
					{
							m_fX += m_fSpeed + plusup[i];
					}
				}

				else
				{
					if (b_pattern.count % 5 == 0)
					{
						++b_pattern.index;
						if (b_pattern.index == 15)
						{
							b_pattern.count = 0;
							b_pattern.index = 0;
							m_pattonChack = 1;
							m_move = IDLEMOVE;
						}
					}
				}
			}

			if (m_move == P_RUSHMOVE) // 강하게 앞으로 돌진? or 플레이어 위치로 돌진?
			{

				if (m_fX <= 500)
				{
					int plusup[] = { 1, 3, 5 };
					for (int i = 0; i < 3; i++)
					{
						
						m_fX += m_fSpeed + plusup[i];
						
					}
				}

				else
				{
					if (b_pattern.count % 5 == 0)
					{
						++b_pattern.index;
						if (b_pattern.index == 15)
						{
							b_pattern.count = 0;
							b_pattern.index = 0;
							m_pattonChack = 0;
							m_move = IDLEMOVE;
						}
					}
				}
			}

			if (m_move == IDLEMOVE) // 초기 위치로 이동
			{
				if (m_fX >= -20)
					m_fX -= m_fSpeed;
				else
				{
					if (b_pattern.count % 20 == 0)
					{
						++b_pattern.index;
						if (b_pattern.index == 10)
						{
							b_pattern.count = 0;
							b_pattern.index = 0;
							m_move = S_BACKMOVE;
						}
					}
					
				}
				
			}
		}

		
	}
	
	else if(!m_isAlive)
	{
		if (!m_isAppear && (m_fX >= -1200 && m_fY <= 2000)) {

			m_fX -= m_fSpeed;
			m_fY += m_fSpeed;
		}
	}

}

void boss::change(bool ischagne)
{
	if (ischagne == true)
	{
		++b_chagne.count;
		if (b_chagne.count% 10 == 0)
		{
			++b_chagne.index;
			
			if (b_chagne.index == 5)
			{
				m_state = RAGE;
				m_isChange = false;
				m_pRageBoss->start();
				m_pChangeBoss->stop();

				
			}
		}
	}

	
}

void boss::damaged(int damage)
{
	m_nCurrHP -= damage;
	if (m_nCurrHP <= 0)
	{
		m_isAlive = false;
		m_pDieAni->start();
	}

	if (m_nCurrHP == 5)
	{
		m_state = CHANGE;
		m_isChange = true;
		m_pChangeBoss->start();
	}
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


