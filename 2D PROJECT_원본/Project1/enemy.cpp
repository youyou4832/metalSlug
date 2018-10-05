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
	if (m_CharNum == CharInfo::sandbag) {
		m_currHP = m_MaxHP = 30;
	}
	else if(m_CharNum == CharInfo::sniper){
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
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) {
		m_currHP--;
	}
	if (isAlive) {
		if (m_CharNum == CharInfo::sniper) {
			move();
			sniperAnimation();
		}
		else if (m_CharNum == CharInfo::sandbag) {
			m_rc = RectMakeCenter(m_fX + 48, m_fY + 35, 40, 35 * 2);
			//sandBagAnimation();
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
			Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
			if (m_CharNum == CharInfo::sniper) {
				if (m_currHP > 0) {
					m_pImg->render(hdc, m_fX, m_fY, m_pImg->getFrameX()*m_pImg->getFrameWidth(), m_pImg->getFrameY(), m_pImg->getFrameWidth(), m_pImg->getHeight(), 3);
				}
				else {
					IMAGEMANAGER->findImage("enemy_death")->render(hdc, m_fX  + 120, m_fY + 90, 44 * s_Death.index, 0, 44, 39, 3);
				}
			}
			else if (m_CharNum == CharInfo::sandbag) {
				m_pImg->render(hdc, m_fX, m_fY, 0, 0, 48, 35, 2);

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
	if (m_CharNum == CharInfo::sniper) {
		m_rc = RectMakeCenter(m_fX + (m_pImg->getFrameWidth() / 2) * 3 + 30, m_fY + (m_pImg->getHeight() / 2) * 3 + 30, m_pImg->getFrameWidth(), m_pImg->getHeight());
	}

	if (m_fX < 0) {
		isAlive = false;
	}

}

void enemy::fire()
{
	/*m_nFireCount++;
	if (m_nFireCount % m_nRandFireCount == 0)
	{
		m_pMissileMgr->fire(m_fX, m_fY,
			PI, 5, m_CharNum);

		m_nFireCount = 0;
		m_nRandFireCount = RANDOM->getFromIntTo(150, 250);
	}*/
	if (m_CharNum == CharInfo::sniper) {
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

	if (m_currHP <= 15) {
		++s_Attack.count;
		if (s_Attack.count % 5 == 0) {
			++s_Attack.index;
			if (s_Attack.index == 17) {
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
