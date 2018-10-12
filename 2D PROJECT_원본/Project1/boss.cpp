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
	m_isShoot = false;

	m_state = NOMAL;
	m_pattern = MOVE;
	m_bullet = NOMAL_BULLET;

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

	//보스 fireBall 공격 
	m_pBossFire = new animation;
	m_pBossFire->init(m_pimgBoss->getWidth(), m_pimgBoss->getHeight(),
		230, 207);
	m_pBossFire->setPlayFrame(48, 60);
	m_pBossFire->setFPS(30);

	//보스 CANNON 공격 모션
	m_pBossCfire = new animation;
	m_pBossCfire->init(m_pimgBoss->getWidth(), m_pimgBoss->getHeight(),
		230, 207);
	m_pBossCfire->setPlayFrame(36, 48);
	m_pBossCfire->setFPS(30);

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

	//보스 이펙트
	m_pimgeffect = IMAGEMANAGER->addImage("effect", "image/boss/BossEffect.bmp",
		1056, 736, true, RGB(255, 0, 255));

	
	//보스 미사일 동적할당으로 생성
	m_pmissileManager = new missileManager;
	
	m_nCurrFrameX = 0;
	m_nCurrFrameY = 0;

	m_fSpeed = 5.0f;	//보스 평소 스피드
	m_upspeed = 3.0;	//보스 등장 스피드

	//보스 초기 위치는 등장씬을 위해 안보이는 곳에서 위치를 잡아준다.
	m_fX = -20;			// 보스 초기 시작 X위치
	m_fY = 1035;		// 보스 초기 시작 Y위치

	m_nCurrHP = m_nMaxHP = 10;

	m_fAngle = (PI * 45) / 180;
	//m_rc = RectMakeCenter(m_fX, m_fY, m_pimgBoss->getWidth(), m_pimgBoss->getHeight());
	
	//m_rc = RectMake(m_fX + 100, m_fY + 50, (m_pimgBoss->getWidth() + 400) / 4, m_pimgBoss->getHeight());


	return S_OK;
}

void boss::release()
{
	SAFE_DELETE(m_pMoveAni);
	SAFE_DELETE(m_pChangeBoss);
	SAFE_DELETE(m_pBossFire);
	SAFE_DELETE(m_pBossCfire);
	SAFE_DELETE(m_pRageBoss);
	SAFE_DELETE(m_pDieAni);
	SAFE_DELETE(m_pmissileManager);
}

void boss::update()
{
    change(m_isChange);

	/*if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
			fire();
	}*/

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		damaged(1);
	}

	//m_rc = RectMake(m_fX, m_fY, (m_pimgBoss->getWidth()+400)/4, m_pimgBoss->getHeight());
	
	
	move();		//보스의 움직임을 위한 함수
	shoot();


	m_pMoveAni->frameUpdate(TIMEMANAGER->getElapsedTime());
	m_pDieAni->frameUpdate(TIMEMANAGER->getElapsedTime());
	m_pBossFire->frameUpdate(TIMEMANAGER->getElapsedTime());
	m_pRageBoss->frameUpdate(TIMEMANAGER->getElapsedTime());
	m_pChangeBoss->frameUpdate(TIMEMANAGER->getElapsedTime());
	
	m_pmissileManager->update();

}

void boss::render(HDC hdc)
{
	if (m_isAlive)
	{
	
		if (m_state == NOMAL && m_pattern != BULLET_SHOOT)
		{
			m_pimgBoss->aniRender(hdc, m_fX, m_fY, m_pMoveAni, 4.0);
		}

		else if (m_state == NOMAL && m_pattern == BULLET_SHOOT)
		{
			m_pimgBoss->aniRender(hdc, m_fX, m_fY, m_pBossFire, 4.0);

			m_pimgeffect->render(hdc, m_fX + 470, m_fY + 40, 0+(40*b_nomaleffect.index), 648, 40, 33, 5);
			m_pimgeffect->render(hdc, m_fX + 200, m_fY-10, 0 + (40 * b_nomaleffect.index), 648, 40, 33, 5);
			
		}

		else if (m_state == CHANGE)
		{
			m_pimgBoss->aniRender(hdc, m_fX, m_fY, m_pChangeBoss, 4.0);
		
		}

		else if (m_state == RAGE && m_pattern != BULLET_SHOOT)
		{
			m_pimgBoss->aniRender(hdc, m_fX, m_fY, m_pRageBoss, 4.0);
		
		}

		else if(m_state == RAGE && m_pattern == BULLET_SHOOT)
		{ 
			m_pimgBoss->aniRender(hdc, m_fX, m_fY, m_pBossCfire, 4.0);
			m_pimgeffect->render(hdc, m_fX + 530, m_fY +60, 0 + (81 * b_nomaleffect.index), 0, 81, 89, 5);
		}

		m_pimgeffect->render(hdc, m_fX - 100, m_fY + 680, 0 + (264 * b_moveeffect.index),
			492 + (52 * b_smoveeffect.index), 264, 52, 4);

		if (m_bullet == NOMAL_BULLET)
			m_pmissileManager->render(hdc, CharInfo::i_nomalboss);

		else if (m_bullet == CANNON_BULLET)
			m_pmissileManager->render(hdc, CharInfo::i_rageboss);
	}


	else
	{
		m_pimgBoss->aniRender(hdc, m_fX, m_fY, m_pDieAni, 4.0);
	}
	//Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
	
	

	
}

void boss::move()
{
	ani_moveeffect();
	ani_smoveeffect();
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
			if (m_pattern == MOVE) // 등장이 끝난후 잠깐 제자리 걸음(사실상 정지)
			{
				//m_fX += m_fSpeed;
				
				if (b_pattern.count%5 == 0)
				{
					++b_pattern.index;
					if (b_pattern.index == 10)
					{
						b_pattern.count = 0;
						b_pattern.index = 0;
						m_pattern = S_BACKMOVE;
					}
				}
			}

			if (m_pattern == S_BACKMOVE) // 뒤로 조금 이동
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
								m_pattern = S_RUSHMOVE;

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
								m_pattern = P_RUSHMOVE;

							}
						}
					}
				}
			}

			if (m_pattern == S_RUSHMOVE) // 조금만 돌진
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
							m_pattern = IDLEMOVE;
						}
					}
				}
			}

			if (m_pattern == P_RUSHMOVE) // 강하게 앞으로 돌진
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
							m_pattern = IDLEMOVE;
						}
					}
				}
			}

			if (m_pattern == IDLEMOVE) // 초기 위치로 이동
			{
				if (m_fX >= -20)
					m_fX -= m_fSpeed;
				else
				{
					if (b_pattern.count % 5 == 0)
					{
						++b_pattern.index;
						if (b_pattern.index == 5)
						{
							b_pattern.count = 0;
							b_pattern.index = 0;
							m_pattern = BULLET_SHOOT;
						}
					}
					
				}
				
			}

			if (m_pattern == BULLET_SHOOT) // 총알 슛
			{
				ani_nomalshoot();

				if (m_isShoot == true)
				{
					if (m_bullet == NOMAL_BULLET)
					{
						m_pBossFire->start();
						m_isShoot = false;
					}

					else if (m_bullet == CANNON_BULLET)
					{
						m_pBossCfire->start();
					}
				}
				

				if (b_pattern.count % 2 == 0)
				{
					++b_pattern.index;
					if (b_pattern.index == 10)
					{
						fire();
						b_pattern.count = 0;
						b_pattern.index = 0;
						m_pattern = S_BACKMOVE;
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
		++b_change.count;
		if (b_change.count% 5 == 0)
		{
			++b_change.index;
			
			if (b_change.index == 4)
			{
				m_state = RAGE;
				m_isChange = false;
				m_pRageBoss->start();
				m_pChangeBoss->stop();
			}
		}
	}
	
}

void boss::ani_moveeffect()
{
	++b_moveeffect.count;
	if (b_moveeffect.count % 5 == 0) {
		++b_moveeffect.index;
		if (b_moveeffect.index == 4) {
			b_moveeffect.index = 0;
		}
		b_moveeffect.count = 0;
	}
}

void boss::ani_smoveeffect()
{
	++b_smoveeffect.count;
	if (b_smoveeffect.count % 5 == 0) {
		++b_smoveeffect.index;
		if (b_smoveeffect.index == 2) {
			b_smoveeffect.index = 0;
		}
		b_smoveeffect.count = 0;
	}
}

void boss::ani_nomalshoot()
{
	++b_nomaleffect.count;
	if (b_nomaleffect.count % 5 == 0) {
		++b_nomaleffect.index;
		if (b_nomaleffect.index == 18) {
			b_nomaleffect.index = 0;
		}
		b_nomaleffect.count = 0;
	}
}

void boss::ani_rageshoot()
{
	++b_rageefect.count;
	if (b_rageefect.count % 5 == 0) {
		++b_rageefect.index;
		if (b_rageefect.index == 10) {
			b_rageefect.index = 0;
		}
		b_rageefect.count = 0;
	}
}

void boss::fire()
{
	if (m_bullet == NOMAL_BULLET)
	{
		m_pmissileManager->fire(m_fX + 520, m_fY + 50, m_fAngle, 5, CharInfo::i_nomalboss);
		m_pmissileManager->fire(m_fX + 230, m_fY + 25, m_fAngle, 5, CharInfo::i_nomalboss);
	}
	
	else if (m_bullet == CANNON_BULLET)
	{
		m_pmissileManager->fire(m_fX + 650, m_fY + 200, (PI * 45) / 180, 5, CharInfo::i_rageboss);
	}
			
}

void boss::shoot()
{
	if (m_pattern == BULLET_SHOOT)
	{
		m_isShoot = true;
	}

	else
	{
		m_isShoot = false;
		//m_pBossFire->stop();
		if (m_bullet == NOMAL_BULLET)
		{
			m_pBossFire->stop();
		}

		else if (m_bullet == CANNON_BULLET)
		{
			m_pBossCfire->stop();
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
		m_bullet = CANNON_BULLET;
		m_isChange = true;
		m_pChangeBoss->start();
	}
}


boss::boss()
{
}


boss::~boss()
{
}


