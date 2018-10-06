#include "stdafx.h"
#include "enemy.h"
#include "missileManager.h"
#include "progressBar.h"

HRESULT enemy::init()
{
	m_nCount = 0;
	m_nCurrFrameX = 0;
	m_nCurrFrameY = 0;
	m_pImg = NULL;

	ZeroMemory(&m_rc, sizeof(m_rc));

	m_pMissileMgr = new missileManager;
	m_pMissileMgr->init("image/bullet.bmp", 200.0f, 10);
	m_nFireCount = 0;
	m_nRandFireCount = 10;
	m_fX = 0;
	m_fY = 0;

	return S_OK;
}

HRESULT enemy::init(const char * szFileName, POINT position, int destX, int destY, int speed, int charNum)
{
	m_nCount = 0;
	m_nCurrFrameX = 0;
	m_nCurrFrameY = 0;
	m_CharNum = charNum;
	std::string strFile = std::string(szFileName);
	m_pImg = IMAGEMANAGER->findImage(strFile);

	m_rc = RectMakeCenter(position.x, position.y,
		m_pImg->getFrameWidth(), m_pImg->getFrameHeight());

	m_pMissileMgr = new missileManager;
	m_pMissileMgr->init(szFileName, WINSIZEY, 0);
	m_nFireCount = 0;
	m_nRandFireCount = 10;
	m_fX = position.x;
	m_fY = position.y;

	m_destX = destX;
	m_destY = destY;
	m_destX2 = position.x;
	m_destY2 = position.y;

	moveAngle = MY_UTIL::getAngle(
		m_fX, m_fY,
		m_destX, m_destY);

	m_fSpeed = speed;
	isAlive = true;
	deathCN = 0;
	if (m_CharNum == CharInfo::i_sandbag) {
		m_currHP = m_MaxHP = 30;
	}
	else if(m_CharNum == CharInfo::i_sniper){
		m_currHP = m_MaxHP = 1;
	}

	return S_OK;
}

void enemy::release()
{
	if (m_pMissileMgr)
	{
		m_pMissileMgr->release();
		delete m_pMissileMgr;
	}
}

void enemy::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_RETURN)) {
		m_currHP--;
		s_Hit.isState = true;
		if (m_currHP == 15) {
			firstBreak = true;
		}
		if (m_currHP == 0) {
			secondBreak = true;
		}
	}

	if (isAlive) {
		if (m_CharNum == CharInfo::i_sniper) {
			move();
			sniperAnimation();
		}
		else if (m_CharNum == CharInfo::i_sandbag) {
			m_rc = RectMakeCenter(m_fX + 48, m_fY + 35, 40, 35 * 2);
			sandBagAnimation();
			if (s_Hit.isState == true) {
				sendBagHitAnimation();
			}
		}
	}
	//fire();
	
	if (m_pMissileMgr)
		m_pMissileMgr->update();
	
}

void enemy::render(HDC hdc)
{
	if (isAlive) {
		if (m_pImg)
		{
			//Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
			if (m_CharNum == CharInfo::i_sniper) {
				if (m_currHP > 0) {
					m_pImg->render(hdc, m_fX, m_fY, m_pImg->getFrameX()*m_pImg->getFrameWidth(), m_pImg->getFrameY(), m_pImg->getFrameWidth(), m_pImg->getHeight(), 3);
				}
				else {
					IMAGEMANAGER->findImage("enemy_death")->render(hdc, m_fX  + 120, m_fY + 90, 44 * s_Death.index, 0, 44, 39, 3);
				}
			}
			else if (m_CharNum == CharInfo::i_sandbag) {
				if (m_currHP > 15) {//������ ����� ����
					if (s_Hit.isState == false) {
						m_pImg->render(hdc, m_fX, m_fY, 0, 0, 48, 35, 2);
					}
					else if (s_Hit.isState == true) {
						m_pImg->render(hdc, m_fX, m_fY, 48 * s_Hit.index, 35, 48, 35, 2);
					}
				}
				else {//�ѹ� �μ��� �����
					if (s_Hit.isState == false && secondBreak == false) {
						m_pImg->render(hdc, m_fX, m_fY + 29, 0, 134, 48, 22, 2);
					}
					else if (s_Hit.isState == true) {
						m_pImg->render(hdc, m_fX, m_fY + 29, 48 * s_Hit.index, 156, 48, 22, 2);
					}
				}
				if (firstBreak == true) {//ó�� ����� ����
					m_pImg->render(hdc, m_fX, m_fY - 55, 48 * s_Attack.index, 70, 48, 64, 2);
				}
				if (secondBreak == true) {
					m_pImg->render(hdc, m_fX - 20, m_fY - 160, 80 * s_Attack.index, 178, 80, 119, 2);
				}

				
			}
		}

	}

	if (m_pMissileMgr)
	{
		m_pMissileMgr->render(hdc, m_CharNum);
	}
}

void enemy::move()
{
	/*m_fX += cosf(moveAngle) * m_fSpeed;
	m_fY += -sinf(moveAngle) * m_fSpeed;*/
	if (m_CharNum == CharInfo::i_sniper) {
		m_rc = RectMakeCenter(m_fX + (m_pImg->getFrameWidth() / 2) * 3 + 30, m_fY + (m_pImg->getHeight() / 2) * 3 + 30, m_pImg->getFrameWidth(), m_pImg->getHeight());
	}

	if (m_fX < 0) {
		isAlive = false;
	}

}

void enemy::fire()
{
	if (m_CharNum == CharInfo::i_sniper) {
		m_pMissileMgr->fire(m_fX+ (m_pImg->getFrameWidth() / 2)*3, m_fY + (m_pImg->getHeight() / 2) * 3,
			PI, 5, m_CharNum);
	}
}

void enemy::sniperAnimation()
{
	if (m_currHP > 0) {
		++s_Attack.count;
		if (s_Attack.count % 5 == 0) {
			++s_Attack.index;
			if (s_Attack.index == 11) {
				fire();
			}
			if (s_Attack.index == 27) {
				s_Attack.index = 0;
			}
			s_Attack.count = 0;
			m_pImg->setFrameX(s_Attack.index);
		}
	}
	else {
		++s_Death.count;
		if (s_Death.count % 8 == 0) {
			++s_Death.index;
			if (s_Death.index == 6) {
				s_Death.index = 5;
				deathCount();
			}
			s_Death.count = 0;
		}
	}
}

void enemy::sandBagAnimation()
{
	if (firstBreak == true) {
		++s_Attack.count;
		if (s_Attack.count % 5 == 0) {
			++s_Attack.index;
			if (s_Attack.index == 17) {
				s_Attack.index = 0;
				firstBreak = false;
			}
			s_Attack.count = 0;
		}
	}
	else if (secondBreak == true) {
		++s_Attack.count;
		if (s_Attack.count % 5 == 0) {
			++s_Attack.index;
			if (s_Attack.index == 20) {
				s_Attack.index = 0;
				secondBreak = false;
				isAlive = false;
			}
			s_Attack.count = 0;
		}
	}
}

void enemy::sendBagHitAnimation()
{
	if (m_currHP > 15) {
		++s_Hit.count;
		if (s_Hit.count % 8 == 0) {
			++s_Hit.index;
			if (s_Hit.index == 2) {
				s_Hit.index = 0;
				s_Hit.isState = false;
			}
			s_Hit.count = 0;
		}
	}
	else {
		++s_Hit.count;
		if (s_Hit.count % 8 == 0) {
			++s_Hit.index;
			if (s_Hit.index == 2) {
				s_Hit.index = 0;
				s_Hit.isState = false;
			}
			s_Hit.count = 0;
		}
	}
}

void enemy::deathCount()
{
	deathCN++;

	if (deathCN == 8) {
		isAlive = false;
	}
}

enemy::enemy()
{

}


enemy::~enemy()
{
}
