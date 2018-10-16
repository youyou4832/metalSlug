#include "stdafx.h"
#include "boss.h"
#include "missile.h"
#include "missileManager.h"
#include "animation.h"

HRESULT boss::init()
{
	//���� ���� �ʱ�ȭ
	m_isAppear = true;
	m_isAlive = true;
	m_isChange = false;
	m_isShoot = false;

	m_BossState = NOMAL;
	m_PatternState = MOVE;
	m_BulletState = NOMAL_BULLET;

	m_pattonChack = 0;
	//���� �̹��� ����(230*207 12�� �� 7��)
	m_pimgBoss = IMAGEMANAGER->addImage("move", "image/boss/Boss.bmp",
		2760, 1449, true, RGB(255, 0, 255));
	
	m_pMoveAni = new animation;
	m_pMoveAni->init(m_pimgBoss->getWidth(), m_pimgBoss->getHeight(),
		230, 207);
	m_pMoveAni->setPlayFrame(1, 12, false, true);
	m_pMoveAni->setFPS(15);

	//���� ����
	m_pChangeBossAni = new animation;
	m_pChangeBossAni->init(m_pimgBoss->getWidth(), m_pimgBoss->getHeight(),
		230, 207);
	m_pChangeBossAni->setPlayFrame(12, 24);
	m_pChangeBossAni->setFPS(15);

	//���� NOMAL_BULLET ���� 
	m_pNomalFireAni = new animation;
	m_pNomalFireAni->init(m_pimgBoss->getWidth(), m_pimgBoss->getHeight(),
		230, 207);
	m_pNomalFireAni->setPlayFrame(48, 60);
	m_pNomalFireAni->setFPS(30);

	//���� RAGE_BULLET ���� ���
	m_pRageFireAni = new animation;
	m_pRageFireAni->init(m_pimgBoss->getWidth(), m_pimgBoss->getHeight(),
		230, 207);
	m_pRageFireAni->setPlayFrame(36, 48);
	m_pRageFireAni->setFPS(30);

	//���� �г����
	m_pRageBossAni = new animation;
	m_pRageBossAni->init(m_pimgBoss->getWidth(), m_pimgBoss->getHeight(),
		230, 207);
	m_pRageBossAni->setPlayFrame(24, 36, false , true);
	m_pRageBossAni->setFPS(15);

	//���� ����
	m_pDieAni = new animation;
	m_pDieAni->init(m_pimgBoss->getWidth(), m_pimgBoss->getHeight(),
		230, 207);
	m_pDieAni->setPlayFrame(72, 84);
	m_pDieAni->setFPS(15);

	//���� ����Ʈ
	m_pimgeffect = IMAGEMANAGER->addImage("effect", "image/boss/BossEffect.bmp",
		1056, 736, true, RGB(255, 0, 255));

	
	//���� �̻��� �����Ҵ����� ����
	m_pmissileManager = new missileManager;
	
	
	m_Speed = 5.0f;	//���� ��� ���ǵ�
	m_AppearSpeed = 3.0;	//���� ���� ���ǵ�

	//���� �ʱ� ��ġ�� ������� ���� �Ⱥ��̴� ������ ��ġ�� ����ش�.
	m_fX = -20;			// ���� �ʱ� ���� X��ġ
	m_fY = 1035;		// ���� �ʱ� ���� Y��ġ

	m_nCurrHP = m_nMaxHP = 10;

	m_fAngle = (PI * 45) / 180;

	getTimeCount = 0.0f;
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

	/*if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
			fire();
	}*/

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		damaged(1);
	}

	//m_rc = RectMake(m_fX, m_fY, (m_pimgBoss->getWidth()+400)/4, m_pimgBoss->getHeight());
	
	
	move();		//������ �������� ���� �Լ�
	shoot();


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

			m_pimgeffect->render(hdc, m_fX + 470, m_fY + 40, 0+(40*m_NomalEffectDelay.index), 648, 40, 33, 5);
			m_pimgeffect->render(hdc, m_fX + 200, m_fY-10, 0 + (40 * m_NomalEffectDelay.index), 648, 40, 33, 5);
			
		}

		else if (m_BossState == CHANGE)
		{
			m_pimgBoss->aniRender(hdc, m_fX, m_fY, m_pChangeBossAni, 4.0);
		
		}

		else if (m_BossState == RAGE && m_PatternState != BULLET_SHOOT)
		{
			m_pimgBoss->aniRender(hdc, m_fX, m_fY, m_pRageBossAni, 4.0);
		
		}

		else if(m_BossState == RAGE && m_PatternState == BULLET_SHOOT)
		{ 
			m_pimgBoss->aniRender(hdc, m_fX, m_fY, m_pRageFireAni, 4.0);
			m_pimgeffect->render(hdc, m_fX + 530, m_fY +60, 0 + (81 * m_RageFireAinCount.index), 0, 81, 89, 5);
		}

		m_pimgeffect->render(hdc, m_fX - 100, m_fY + 680, 0 + (264 * m_EffectAniCount.index),
			492 + (52 * m_EffectAniCount2.index), 264, 52, 4);

		if (m_BulletState == NOMAL_BULLET)
			m_pmissileManager->render(hdc, CharInfo::i_nomalboss);

		else if (m_BulletState == RAGE_BULLET)
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
	Boss_MoveEffectAniCount();
	Boss_MoveEffectAniCount2();
	if (m_isAppear == true && m_fY >= -10) //���� �����(����Ʈ ���� ����) 
	{
		m_fY -= m_AppearSpeed;
		m_AppearSpeed += 0.8;

		if (m_fY <= 0)
		{
			m_isAppear = false; //������ ���� �����̰� �ϱ� ����
			m_pMoveAni->start();
			
			
		}

	}

	if (m_isAlive && !m_isAppear)
	{
		if (m_BossState == NOMAL || m_BossState == RAGE)
		{
			++m_NextMoveDelay.count;
			if (m_PatternState == MOVE) // ������ ������ ��� ���ڸ� ����(��ǻ� ����)
			{
				//m_fX += m_Speed;
				
				if (m_NextMoveDelay.count%5 == 0)
				{
					++m_NextMoveDelay.index;
					if (m_NextMoveDelay.index == 10)
					{
						m_NextMoveDelay.count = 0;
						m_NextMoveDelay.index = 0;
						m_PatternState = S_BACKMOVE;
					}
				}
			}

			if (m_PatternState == S_BACKMOVE) // �ڷ� ���� �̵�
			{
				if (m_pattonChack == 0)
				{
					if (m_fX >= -900)
					{
						m_fX -= m_Speed;
					}

					else
					{
						if (m_NextMoveDelay.count % 5 == 0)
						{
							++m_NextMoveDelay.index;
							if (m_NextMoveDelay.index == 15)
							{
								m_NextMoveDelay.count = 0;
								m_NextMoveDelay.index = 0;
								m_PatternState = S_RUSHMOVE;

							}
						}
					}
				}

				if (m_pattonChack == 1)// �ڷ� ���� �̵�
				{
					if (m_fX >= -1000)
					{
						m_fX -= m_Speed;
					}

					else
					{
						if (m_NextMoveDelay.count % 5 == 0)
						{
							++m_NextMoveDelay.index;
							if (m_NextMoveDelay.index == 25)
							{
								m_NextMoveDelay.count = 0;
								m_NextMoveDelay.index = 0;
								m_PatternState = P_RUSHMOVE;

							}
						}
					}
				}
			}

			if (m_PatternState == S_RUSHMOVE) // ���ݸ� ����
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
					if (m_NextMoveDelay.count % 5 == 0)
					{
						++m_NextMoveDelay.index;
						if (m_NextMoveDelay.index == 15)
						{
							m_NextMoveDelay.count = 0;
							m_NextMoveDelay.index = 0;
							m_pattonChack = 1;
							m_PatternState = IDLEMOVE;
						}
					}
				}
			}

			if (m_PatternState == P_RUSHMOVE) // ���ϰ� ������ ����
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
					if (m_NextMoveDelay.count % 5 == 0)
					{
						++m_NextMoveDelay.index;
						if (m_NextMoveDelay.index == 15)
						{
							m_NextMoveDelay.count = 0;
							m_NextMoveDelay.index = 0;
							m_pattonChack = 0;
							m_PatternState = IDLEMOVE;
						}
					}
				}
			}

			if (m_PatternState == IDLEMOVE) // �ʱ� ��ġ�� �̵�
			{
				if (m_fX >= -20)
					m_fX -= m_Speed;
				else
				{
					if (m_NextMoveDelay.count % 5 == 0)
					{
						++m_NextMoveDelay.index;
						if (m_NextMoveDelay.index == 5)
						{
							m_NextMoveDelay.count = 0;
							m_NextMoveDelay.index = 0;
							m_PatternState = BULLET_SHOOT;
						}
					}
					
				}
				
			}

			if (m_PatternState == BULLET_SHOOT) // �Ѿ� ��
			{
				
				if (m_NextMoveDelay.count == 0)
				{
					if (m_BulletState == NOMAL_BULLET)
					{
						m_pNomalFireAni->start();
						//m_isShoot = false;
					}

					else if (m_BulletState == RAGE_BULLET)
					{
						m_pRageFireAni->start();
					}
				}

				if (m_BulletState == NOMAL_BULLET)
				{
					Boss_FireEffectAniCount();
				}

				else if (m_BulletState == RAGE_BULLET)
				{
					Boss_FireEffectAniCount2();
				}
				

				if (m_NextMoveDelay.count % 2 == 0)
				{
					++m_NextMoveDelay.index;
					if (m_NextMoveDelay.index == 4 && m_BulletState == NOMAL_BULLET)
					{
						fire();
						m_NextMoveDelay.count = 0;
						m_NextMoveDelay.index = 0;
						m_pNomalFireAni->stop();
						m_PatternState = S_BACKMOVE;
					}

					if (m_NextMoveDelay.index == 5 && m_BulletState == RAGE_BULLET)
					{
						fire();
						m_NextMoveDelay.count = 0;
						m_NextMoveDelay.index = 0;
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

			m_fX -= m_Speed;
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

void boss::Boss_MoveEffectAniCount()
{
	++m_EffectAniCount.count;
	if (m_EffectAniCount.count % 5 == 0) {
		++m_EffectAniCount.index;
		if (m_EffectAniCount.index == 4) {
			m_EffectAniCount.index = 0;
		}
		m_EffectAniCount.count = 0;
	}
}

void boss::Boss_MoveEffectAniCount2()
{
	++m_EffectAniCount2.count;
	if (m_EffectAniCount2.count % 5 == 0) {
		++m_EffectAniCount2.index;
		if (m_EffectAniCount2.index == 2) {
			m_EffectAniCount2.index = 0;
		}
		m_EffectAniCount2.count = 0;
	}
}

void boss::Boss_FireEffectAniCount()
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

void boss::Boss_FireEffectAniCount2()
{
	++m_RageFireAinCount.count;
	if (m_RageFireAinCount.count % 1 == 0) {
		++m_RageFireAinCount.index;
		if (m_RageFireAinCount.index == 10) {
			m_RageFireAinCount.index = 0;
		}
		m_RageFireAinCount.count = 0;
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

void boss::shoot()
{
	if (m_PatternState == BULLET_SHOOT)
	{
		m_isShoot = true;
	}

	else
	{
		m_isShoot = false;
		//m_pNomalFireAni->stop();
		if (m_BulletState == NOMAL_BULLET)
		{
			m_pNomalFireAni->stop();
		}

		else if (m_BulletState == RAGE_BULLET)
		{
			m_pRageFireAni->stop();
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
		m_BossState = CHANGE;
		m_BulletState = RAGE_BULLET;
		m_isChange = true;
		m_pChangeBossAni->start();
	}
}


boss::boss()
{
}


boss::~boss()
{
}


