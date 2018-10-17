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

	m_BossState = NOMAL;
	m_PatternState = MOVE;
	m_BulletState = NOMAL_BULLET;

	//boss HP
	m_nCurrHP = m_nMaxHP = 10;

	// 보스 패턴관련 변수
	m_pattonChack = 0;		// 보스 돌진 패턴	
	

	//boss 속도 
	m_Speed = 5.0f;			//보스 평소 스피드
	m_AppearSpeed = 3.0;	//보스 등장 스피드

	//보스 초기 위치는 등장씬을 위해 안보이는 곳에서 위치를 잡아준다.
	m_fX = -20;			// 보스 초기 시작 X위치
	m_fY = 1035;		// 보스 초기 시작 Y위치

	m_fAngle = (PI * 45) / 180;

	//보스 이미지 삽입(230*207 12씩 총 7개)
	m_pimgBoss = IMAGEMANAGER->addImage("move", "image/boss/Boss.bmp",
		2760, 1449, true, RGB(255, 0, 255));
	
	m_pMoveAni = new animation;
	m_pMoveAni->init(m_pimgBoss->getWidth(), m_pimgBoss->getHeight(),
		230, 207);
	m_pMoveAni->setPlayFrame(1, 12, false, true);
	m_pMoveAni->setFPS(15);

	//보스 변신
	m_pChangeBossAni = new animation;
	m_pChangeBossAni->init(m_pimgBoss->getWidth(), m_pimgBoss->getHeight(),
		230, 207);
	m_pChangeBossAni->setPlayFrame(12, 24);
	m_pChangeBossAni->setFPS(15);

	//보스 NOMAL_BULLET 공격 
	m_pNomalFireAni = new animation;
	m_pNomalFireAni->init(m_pimgBoss->getWidth(), m_pimgBoss->getHeight(),
		230, 207);
	m_pNomalFireAni->setPlayFrame(48, 60);
	m_pNomalFireAni->setFPS(30);

	//보스 RAGE_BULLET 공격 모션
	m_pRageFireAni = new animation;
	m_pRageFireAni->init(m_pimgBoss->getWidth(), m_pimgBoss->getHeight(),
		230, 207);
	m_pRageFireAni->setPlayFrame(36, 48);
	m_pRageFireAni->setFPS(30);

	//보스 분노상태
	m_pRageBossAni = new animation;
	m_pRageBossAni->init(m_pimgBoss->getWidth(), m_pimgBoss->getHeight(),
		230, 207);
	m_pRageBossAni->setPlayFrame(24, 36, false , true);
	m_pRageBossAni->setFPS(15);

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

	//m_rc = RectMakeCenter(m_fX, m_fY, m_pimgBoss->getWidth(), m_pimgBoss->getHeight());
	//m_rc = RectMake(m_fX + 100, m_fY + 50, (m_pimgBoss->getWidth() + 400) / 4, m_pimgBoss->getHeight());

	return S_OK;
}

void boss::release()
{
	SAFE_DELETE(m_pMoveAni);
	SAFE_DELETE(m_pChangeBossAni);
	SAFE_DELETE(m_pNomalFireAni);
	SAFE_DELETE(m_pRageFireAni);
	SAFE_DELETE(m_pRageBossAni);
	SAFE_DELETE(m_pDieAni);
	SAFE_DELETE(m_pmissileManager);
}

void boss::update()
{
    change(m_isChange);

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		damaged(1);
	}

	m_rc = RectMake(m_fX, m_fY, (m_pimgBoss->getWidth()+400)/4, m_pimgBoss->getHeight());
	
	move();		//보스의 움직임을 위한 함수

	m_pMoveAni->frameUpdate(TIMEMANAGER->getElapsedTime());
	m_pDieAni->frameUpdate(TIMEMANAGER->getElapsedTime());
	m_pNomalFireAni->frameUpdate(TIMEMANAGER->getElapsedTime());
	m_pRageFireAni->frameUpdate(TIMEMANAGER->getElapsedTime());
	m_pRageBossAni->frameUpdate(TIMEMANAGER->getElapsedTime());
	m_pChangeBossAni->frameUpdate(TIMEMANAGER->getElapsedTime());
	
	m_pmissileManager->update();

}

void boss::render(HDC hdc)
{
	if (m_isAlive)
	{
		if (m_BossState == NOMAL && m_PatternState != BULLET_SHOOT)
		{
			m_pimgBoss->aniRender(hdc, m_fX, m_fY, m_pMoveAni, 4.0);

		}

		else if (m_BossState == NOMAL && m_PatternState == BULLET_SHOOT)
		{
			m_pimgBoss->aniRender(hdc, m_fX, m_fY, m_pNomalFireAni, 4.0);

			m_pimgeffect->render(hdc, m_fX + 470, m_fY + 40, 0 + (40 * m_NomalEffectDelay.index), 648, 40, 33, 5);
			m_pimgeffect->render(hdc, m_fX + 200, m_fY - 10, 0 + (40 * m_NomalEffectDelay.index), 648, 40, 33, 5);

		}

		else if (m_BossState == CHANGE)
		{
			m_pimgBoss->aniRender(hdc, m_fX, m_fY, m_pChangeBossAni, 4.0);

		}

		else if (m_BossState == RAGE && m_PatternState != BULLET_SHOOT)
		{
			m_pimgBoss->aniRender(hdc, m_fX, m_fY, m_pRageBossAni, 4.0f);

		}

		else if (m_BossState == RAGE && m_PatternState == BULLET_SHOOT)
		{
			m_pimgBoss->aniRender(hdc, m_fX, m_fY, m_pRageFireAni, 4.0f);
			m_pimgeffect->render(hdc, m_fX + 530, m_fY + 60, 0 + (81 * m_RageFireAinDelay.index), 0, 81, 89, 5);
		}

		if (m_AppearEffectAniCount2.index < 2)
		{
			m_pimgeffect->render(hdc, m_fX, m_fY + 100,
				0 + (65 * m_AppearEffectAniCount.index), 178 + (157 * m_AppearEffectAniCount2.index), 65, 157, 5);
			m_pimgeffect->render(hdc, m_fX + 150, m_fY + 100,
				0 + (65 * m_AppearEffectAniCount.index), 178 + (157 * m_AppearEffectAniCount2.index), 65, 157, 5);
			m_pimgeffect->render(hdc, m_fX + 300, m_fY + 100,
				0 + (65 * m_AppearEffectAniCount.index), 178 + (157 * m_AppearEffectAniCount2.index), 65, 157, 5);
			m_pimgeffect->render(hdc, m_fX + 450, m_fY + 100,
				0 + (65 * m_AppearEffectAniCount.index), 178 + (157 * m_AppearEffectAniCount2.index), 65, 157, 5);
			m_pimgeffect->render(hdc, m_fX + 600, m_fY + 100,
				0 + (65 * m_AppearEffectAniCount.index), 178 + (157 * m_AppearEffectAniCount2.index), 65, 157, 5);
		}

		else
		{
			m_pimgeffect->render(hdc, m_fX - 100, m_fY + 680, 0 + (264 * m_MoveEffectAniCount.index),
				492 + (52 * m_MoveEffectAniCount2.index), 264, 52, 4);
		}

		if (m_BulletState == NOMAL_BULLET)
			m_pmissileManager->render(hdc, CharInfo::i_nomalboss);

		else if (m_BulletState == RAGE_BULLET)
			m_pmissileManager->render(hdc, CharInfo::i_rageboss);
	}

	else
	{
		m_pimgBoss->aniRender(hdc, m_fX, m_fY, m_pDieAni, 4.0);
		if (m_AppearEffectAniCount2.index < 2)
		{
			m_pimgeffect->render(hdc, m_fX, WINSIZEY - 720 ,
				0 + (65 * m_AppearEffectAniCount.index), 178 + (157 * m_AppearEffectAniCount2.index), 65, 157, 5);
			m_pimgeffect->render(hdc, m_fX + 150, WINSIZEY- 720,
				0 + (65 * m_AppearEffectAniCount.index), 178 + (157 * m_AppearEffectAniCount2.index), 65, 157, 5);
			m_pimgeffect->render(hdc, m_fX + 300, WINSIZEY - 720,
				0 + (65 * m_AppearEffectAniCount.index), 178 + (157 * m_AppearEffectAniCount2.index), 65, 157, 5);
			m_pimgeffect->render(hdc, m_fX + 450, WINSIZEY - 720,
				0 + (65 * m_AppearEffectAniCount.index), 178 + (157 * m_AppearEffectAniCount2.index), 65, 157, 5);
			m_pimgeffect->render(hdc, m_fX + 600, WINSIZEY - 720,
				0 + (65 * m_AppearEffectAniCount.index), 178 + (157 * m_AppearEffectAniCount2.index), 65, 157, 5);
		}
	}
	//Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
}

void boss::move()
{
	MoveEffectAniCount();
	MoveEffectAniCount2();
	
	if (m_isAppear == true && m_fY >= -10) //보스 등장씬(이펙트 아직 없음) 
	{
		m_fY -= m_AppearSpeed;
		m_AppearSpeed += 0.8;

		if (m_fY <= 0)
		{
			m_isAppear = false; //등장후 씬이 움직이게 하기 위해
			m_pMoveAni->start();
		}
	}

	AppearAndDie();
	
	if (m_isAlive && !m_isAppear)
	{
		if (m_BossState == NOMAL || m_BossState == RAGE)
		{
			++m_NextPatternDelay.count;
			if (m_PatternState == MOVE) // 등장이 끝난후 잠깐 제자리 걸음(사실상 정지)
			{
				if (m_NextPatternDelay.count%5 == 0)
				{
					++m_NextPatternDelay.index;
					if (m_NextPatternDelay.index == 10)
					{
						m_NextPatternDelay.count = 0;
						m_NextPatternDelay.index = 0;
						m_PatternState = S_BACKMOVE;
					}
				}
			}

			if (m_PatternState == S_BACKMOVE) // 뒤로 조금 이동
			{
				if (m_pattonChack == 0)
				{
					if (m_fX >= -900)
					{
						m_fX -= m_Speed;
					}

					else
					{
						if (m_NextPatternDelay.count % 5 == 0)
						{
							++m_NextPatternDelay.index;
							if (m_NextPatternDelay.index == 15)
							{
								m_NextPatternDelay.count = 0;
								m_NextPatternDelay.index = 0;
								m_PatternState = S_RUSHMOVE;

							}
						}
					}
				}

				if (m_pattonChack == 1)// 뒤로 조금 이동
				{
					if (m_fX >= -1000)
					{
						m_fX -= m_Speed;
					}

					else
					{
						if (m_NextPatternDelay.count % 5 == 0)
						{
							++m_NextPatternDelay.index;
							if (m_NextPatternDelay.index == 25)
							{
								m_NextPatternDelay.count = 0;
								m_NextPatternDelay.index = 0;
								m_PatternState = P_RUSHMOVE;

							}
						}
					}
				}
			}

			if (m_PatternState == S_RUSHMOVE) // 조금만 돌진
			{
				if (m_fX < 180 )
				{
					int plusup[] = { 1, 3, 5 };
					for (int i = 0; i < 3; i++)
					{
							m_fX += m_Speed + plusup[i];
					}
				}

				else
				{
					if (m_NextPatternDelay.count % 5 == 0)
					{
						++m_NextPatternDelay.index;
						if (m_NextPatternDelay.index == 15)
						{
							m_NextPatternDelay.count = 0;
							m_NextPatternDelay.index = 0;
							m_pattonChack = 1;
							m_PatternState = IDLEMOVE;
						}
					}
				}
			}

			if (m_PatternState == P_RUSHMOVE) // 강하게 앞으로 돌진
			{

				if (m_fX <= 500)
				{
					int plusup[] = { 1, 3, 5 };
					for (int i = 0; i < 3; i++)
					{
						
						m_fX += m_Speed + plusup[i];
						
					}
				}

				else
				{
					if (m_NextPatternDelay.count % 5 == 0)
					{
						++m_NextPatternDelay.index;
						if (m_NextPatternDelay.index == 15)
						{
							m_NextPatternDelay.count = 0;
							m_NextPatternDelay.index = 0;
							m_pattonChack = 0;
							m_PatternState = IDLEMOVE;
						}
					}
				}
			}

			if (m_PatternState == IDLEMOVE) // 초기 위치로 이동
			{
				if (m_fX >= -20)
					m_fX -= m_Speed;
				else
				{
					if (m_NextPatternDelay.count % 5 == 0)
					{
						++m_NextPatternDelay.index;
						if (m_NextPatternDelay.index == 5)
						{
							m_NextPatternDelay.count = 0;
							m_NextPatternDelay.index = 0;
							m_PatternState = BULLET_SHOOT;
						}
					}
					
				}
			}

			if (m_PatternState == BULLET_SHOOT) // 총알 슛
			{
				if (m_NextPatternDelay.count == 0)
				{
					if (m_BulletState == NOMAL_BULLET)
					{
						m_pNomalFireAni->start();
					}

					else if (m_BulletState == RAGE_BULLET)
					{
						m_pRageFireAni->start();
					}
				}

				if (m_BulletState == NOMAL_BULLET)
				{
					FireEffectAniCount();
				}

				else if (m_BulletState == RAGE_BULLET)
				{
					FireEffectAniCount2();
				}
				
				if (m_NextPatternDelay.count % 2 == 0)
				{
					++m_NextPatternDelay.index;
					if (m_NextPatternDelay.index == 10 && m_BulletState == NOMAL_BULLET)
					{
						fire();
						m_NextPatternDelay.count = 0;
						m_NextPatternDelay.index = 0;
						m_pNomalFireAni->stop();
						m_PatternState = S_BACKMOVE;
					}

					if (m_NextPatternDelay.index == 5 && m_BulletState == RAGE_BULLET)
					{
						fire();
						m_NextPatternDelay.count = 0;
						m_NextPatternDelay.index = 0;
						m_pRageFireAni->stop();
						m_PatternState = S_BACKMOVE;
					}
				}
			}
		}
	}
	
	else if(!m_isAlive)
	{
		if (!m_isAppear && (m_fX >= -1200 && m_fY <= 2000)) {
			
			AppearAndDie();
			m_fY += m_Speed;
		}
	}
}

void boss::change(bool ischagne)
{
	if (ischagne == true)
	{
		++m_ChangeDelay.count;
		if (m_ChangeDelay.count% 5 == 0)
		{
			++m_ChangeDelay.index;
			
			if (m_ChangeDelay.index == 4)
			{
				m_BossState = RAGE;
				m_isChange = false;
				m_pRageBossAni->start();
				m_pChangeBossAni->stop();
			}
		}
	}
}

void boss::MoveEffectAniCount()
{
	++m_MoveEffectAniCount.count;
	if (m_MoveEffectAniCount.count % 5 == 0) {
		++m_MoveEffectAniCount.index;
		if (m_MoveEffectAniCount.index == 4) {
			m_MoveEffectAniCount.index = 0;
		}
		m_MoveEffectAniCount.count = 0;
	}
}

void boss::MoveEffectAniCount2()
{
	++m_MoveEffectAniCount2.count;
	if (m_MoveEffectAniCount2.count % 5 == 0) {
		++m_MoveEffectAniCount2.index;
		if (m_MoveEffectAniCount2.index == 3) {
			m_MoveEffectAniCount2.index = 0;
		}
		m_MoveEffectAniCount2.count = 0;
	}
}

void boss::FireEffectAniCount()
{
	++m_NomalEffectDelay.count;
	if (m_NomalEffectDelay.count % 1 == 0) {
		++m_NomalEffectDelay.index;
		if (m_NomalEffectDelay.index == 18) {
			m_NomalEffectDelay.index = 0;
		}
		m_NomalEffectDelay.count = 0;
	}
}

void boss::FireEffectAniCount2()
{
	++m_RageFireAinDelay.count;
	if (m_RageFireAinDelay.count % 1 == 0) {
		++m_RageFireAinDelay.index;
		if (m_RageFireAinDelay.index == 10) {
			m_RageFireAinDelay.index = 0;
		}
		m_RageFireAinDelay.count = 0;
	}
}

void boss::fire()
{
	if (m_BulletState == NOMAL_BULLET)
	{
		m_pmissileManager->fire(m_fX + 520, m_fY + 50, m_fAngle, 5, CharInfo::i_nomalboss);
		m_pmissileManager->fire(m_fX + 230, m_fY + 25, m_fAngle, 5, CharInfo::i_nomalboss);
	}
	
	else if (m_BulletState == RAGE_BULLET)
	{
		m_pmissileManager->fire(m_fX + 650, m_fY + 200, (PI * 45) / 180, 5, CharInfo::i_rageboss);
	}
			
}

void boss::damaged(int damage)
{
	m_nCurrHP -= damage;
	if (m_nCurrHP <= 0)
	{
		m_isAlive = false;
		m_AppearEffectAniCount2.index = 0;
		m_pDieAni->start();
	}

	if (m_BossState == NOMAL && m_nCurrHP <= 5)
	{
		m_BossState = CHANGE;
		m_BulletState = RAGE_BULLET;
		m_isChange = true;
		m_pChangeBossAni->start();
	}
}

void boss::AppearAndDie()
{
	if (m_fY <= WINSIZEY / 2)
	{
		if (m_AppearEffectAniCount2.index < 2)
		{
			AppearEffectAniCount();
		}
	}
}

void boss::AppearEffectAniCount()
{
	if (m_AppearEffectAniCount2.index <= 1)
	{
		++m_AppearEffectAniCount.count;
		if (m_AppearEffectAniCount.count % 5 == 0) {

			++m_AppearEffectAniCount.index;
			if (m_AppearEffectAniCount.index == 13) {
				m_AppearEffectAniCount.index = 0;
				++m_AppearEffectAniCount2.index;
			}

			m_AppearEffectAniCount.count = 0;
		}
	}

}

boss::boss()
{
}


boss::~boss()
{
}


