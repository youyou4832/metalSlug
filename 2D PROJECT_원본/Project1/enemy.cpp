#include "stdafx.h"
#include "enemy.h"
#include "missileManager.h"
#include "progressBar.h"
#include "player.h"
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

HRESULT enemy::init(const char * szFileName, POINT position, int destX, int destY, int speed, int charNum, player* player)
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
	m_nRandFireCount = RANDOM->getFromIntTo(30, 50);;
	m_fX = position.x;
	m_fY = position.y;

	m_destX = destX;
	m_destY = destY;
	m_destX2 = position.x;
	m_destY2 = position.y;

	/*moveAngle = MY_UTIL::getAngle(
		m_fX, m_fY,
		m_destX, m_destY);*/
	moveAngle = PI;

	m_player = player;
	
	m_fSpeed = speed;
	isAlive = true;
	deathCN = 0;
	m_bulletSpeed = 5;

	if (m_CharNum == CharInfo::i_normal) {
		m_bulletSpeed = 8;
	}
	
	if (m_CharNum == CharInfo::i_sandbag) {
		m_currHP = m_MaxHP = 30;
	}
	else if (m_CharNum == CharInfo::i_tank) {
		MaxAttack = 1;
		s_Move.isState = true;
		m_currHP = m_MaxHP = 20;
	}
	else{
		//s_Idle.isState = true;
		s_Move.isState = true;
		MaxAttack = RANDOM->getFromIntTo(2, 5);
		m_currHP = m_MaxHP = 1;
	}
	AttackCount = 0;
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
		else if (m_CharNum == CharInfo::i_cannon) {
			move();
			cannonAnimation();
		}
		else if (m_CharNum == CharInfo::i_normal) {
			move();
			normalAnimation();
		}
		else if (m_CharNum == CharInfo::i_tank) {
			move();
			tankAnimation();
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
			if (m_CharNum == CharInfo::i_sniper) {
				if (m_currHP > 0) {
					m_pImg->render(hdc, m_fX, m_fY, m_pImg->getFrameX()*m_pImg->getFrameWidth(), m_pImg->getFrameY(), m_pImg->getFrameWidth(), m_pImg->getHeight(), 3);
				}
				else {
					IMAGEMANAGER->findImage("enemy_death")->render(hdc, m_fX  + 120, m_fY + 90, 44 * s_Death.index, 0, 44, 39, 3);
				}
			}
			else if (m_CharNum == CharInfo::i_sandbag) {
				if (m_currHP > 15) {//온전한 샌드백 형태
					if (s_Hit.isState == false) {
						m_pImg->render(hdc, m_fX, m_fY, 0, 0, 48, 35, 2);
					}
					else if (s_Hit.isState == true) {
						m_pImg->render(hdc, m_fX, m_fY, 48 * s_Hit.index, 35, 48, 35, 2);
					}
				}
				else {//한번 부서진 샌드백
					if (s_Hit.isState == false && secondBreak == false) {
						m_pImg->render(hdc, m_fX, m_fY + 29, 0, 134, 48, 22, 2);
					}
					else if (s_Hit.isState == true) {
						m_pImg->render(hdc, m_fX, m_fY + 29, 48 * s_Hit.index, 156, 48, 22, 2);
					}
				}
				if (firstBreak == true) {//처음 샌드백 터짐
					m_pImg->render(hdc, m_fX, m_fY - 55, 48 * s_Attack.index, 70, 48, 64, 2);
				}
				if (secondBreak == true) {
					m_pImg->render(hdc, m_fX - 20, m_fY - 160, 80 * s_Attack.index, 178, 80, 119, 2);
				}
			}
			else if (m_CharNum == CharInfo::i_cannon) {
				if (m_currHP > 0) {
					if (s_Idle.isState == true) {
						m_pImg->render(hdc, m_fX, m_fY, 42 * s_Idle.index, 0, 42, 45, 3);
					}
					else if (s_Attack.isState == true) {
						IMAGEMANAGER->findImage("cannon_Attack")->render(hdc, m_fX - 30, m_fY - 20, 58 * s_Attack.index, 0, 58, 52, 3);
					}
					else if (s_Move.isState == true) {
						m_pImg->render(hdc, m_fX, m_fY, 48 * s_Move.index, 45, 48, 45, 3);
					}
				}
				else {
					IMAGEMANAGER->findImage("enemy_death")->render(hdc, m_fX + 70, m_fY + 20, 44 * s_Death.index, 0, 44, 39, 3);
				}
			}
			else if (m_CharNum == CharInfo::i_normal) {
				if (m_currHP > 0) {
					if (s_Idle.isState == true) {
						m_pImg->render(hdc, m_fX, m_fY, 27 * s_Idle.index, 0, 27, 38, 3);// 기본
					}
					else if (s_Attack.isState == true) {
						if (isDrawGun == false) {
							m_pImg->render(hdc, m_fX  - s_Attack.index*8, m_fY - 20, 46 * s_Attack.index, 78, 46, 44, 3); // 총꺼내기
						}
						else {
							m_pImg->render(hdc, m_fX - 100, m_fY, 61 * s_Attack.index, 122, 61, 38, 3); // 사격
						}
					}
					else if (s_Move.isState == true) {
						m_pImg->render(hdc, m_fX, m_fY, 26 * s_Move.index, 38, 26, 40, 3);
					}
				}
				else {
					IMAGEMANAGER->findImage("enemy_death")->render(hdc, m_fX + 70, m_fY + 20, 44 * s_Death.index, 0, 44, 39, 3);
				}
			}
			else if (m_CharNum == CharInfo::i_tank) {
				if (m_currHP > 0) {
					if (s_Idle.isState == true) {
						m_pImg->render(hdc, m_fX, m_fY, 71 * s_Idle.index, 0, 71, 56, 2);// 기본
					}
					else if (s_Attack.isState == true) {
						m_pImg->render(hdc, m_fX, m_fY, 71 * s_Attack.index, 168, 71, 60, 2);
					}
					else if (s_Move.isState == true) {
						m_pImg->render(hdc, m_fX, m_fY, 71 * s_Move.index, 56, 71, 56, 2);
					}
				}
				else {
					m_pImg->render(hdc, m_fX, m_fY, 96 * s_Death.index, 228, 96, 64, 2);
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
	/*if (AttackCount == MaxAttack) {
		s_Move.isState = true;
		s_Idle.isState = false;
		s_Attack.isState = false;
	}*/
	/*m_fX += cosf(moveAngle) * m_fSpeed;
	m_fY += -sinf(moveAngle) * m_fSpeed;*/
	if (m_CharNum == CharInfo::i_sniper) {
		if (m_pImg->getFrameX() < 5) {
			m_rc = RectMakeCenter(m_fX + (m_pImg->getFrameWidth() / 2) * 3 + 30, m_fY + (m_pImg->getHeight() / 2) * 3 + 50, m_pImg->getFrameWidth() - 20, m_pImg->getHeight()-30);
		}
		else {
			m_rc = RectMakeCenter(m_fX + (m_pImg->getFrameWidth() / 2) * 3 + 30, m_fY + (m_pImg->getHeight() / 2) * 3 + 30, m_pImg->getFrameWidth() - 20, m_pImg->getHeight());
		}
	}
	else if (m_CharNum == CharInfo::i_cannon) {
		if (s_Move.isState == true) {
			m_fX += cosf(moveAngle) * m_fSpeed;
			m_fY += -sinf(moveAngle) * m_fSpeed;
		}
		if ((m_fX < m_destX || m_fX - m_player->getRectLower().left < 100) && m_fX < WINSIZEX - 50 && firstMove == true) {
			firstMove = false;
			s_Move.isState = false;
			s_Idle.isState = true;
		}
		
		m_rc = RectMakeCenter(m_fX + 80, m_fY + 80, 58, 80);
	}
	else if (m_CharNum == CharInfo::i_normal) {
		if (s_Move.isState == true) {
			m_fX += cosf(moveAngle) * m_fSpeed;
			m_fY += -sinf(moveAngle) * m_fSpeed;
		}
		if ((m_fX < m_destX || m_fX - m_player->getRectLower().left < 100) && m_fX < WINSIZEX - 50 && firstMove == true) {
			firstMove = false;
			s_Move.isState = false;
			s_Idle.isState = true;
		}
		m_rc = RectMakeCenter(m_fX + 40, m_fY + 70, 54, 85);
	}
	else if (m_CharNum == CharInfo::i_tank) {
		if (s_Move.isState == true) {
			m_fX += cosf(moveAngle) * m_fSpeed;
			m_fY += -sinf(moveAngle) * m_fSpeed;
		}
		if (m_fX < m_destX && firstMove == true) {
			firstMove = false;
			s_Move.isState = false;
			s_Idle.isState = true;
		}
		m_rc = RectMakeCenter(m_fX + 70, m_fY + 70, 100, 100);
	}

	if (m_fX < 0) {
		isAlive = false;
	}

}

void enemy::fire()
{
	if (m_CharNum == CharInfo::i_sniper) {
			m_pMissileMgr->fire(m_fX + (m_pImg->getFrameWidth() / 2) * 3, m_fY + (m_pImg->getHeight() / 2) * 3,
				PI, m_bulletSpeed, m_CharNum);
	}
	else if (m_CharNum == CharInfo::i_cannon) {
		m_pMissileMgr->fire(m_fX, m_fY+30,
			PI, m_bulletSpeed, m_CharNum);
	}
	else if (m_CharNum == CharInfo::i_normal) {
		m_pMissileMgr->fire(m_fX - 50, m_fY,
			PI, m_bulletSpeed, m_CharNum);
	}
	else if (m_CharNum == CharInfo::i_tank) {
		m_pMissileMgr->fire(m_fX - 60, m_fY - 15,
			PI, m_bulletSpeed, m_CharNum);
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

void enemy::cannonAnimation()
{
	if (m_currHP > 0) {
		if (s_Idle.isState == true) {
			++s_Idle.count;
			if (s_Idle.count % 8 == 0) {
				++s_Idle.index;
				if (s_Idle.index == 6) {
					s_Idle.index = 0;
					s_Idle.isState = false;
					s_Attack.isState = true;
				}
				s_Idle.count = 0;
			}
		}
		else if (s_Attack.isState == true) {
			++s_Attack.count;
			if (s_Attack.count % 8 == 0) {
				++s_Attack.index;
				if (s_Attack.index == 3) {
					fire();
				}
				if (s_Attack.index == 14) {
					s_Attack.index = 0;
					s_Attack.isState = false;
					s_Idle.isState = true;
					AttackCount++;
				}
				s_Attack.count = 0;
			}
		}
		else if (s_Move.isState == true) {
			++s_Move.count;
			if (s_Move.count % 8 == 0) {
				++s_Move.index;
				if (s_Move.index == 11) {
					s_Move.index = 0;
				}
				s_Move.count = 0;
			}
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

void enemy::normalAnimation()
{
	if (m_currHP > 0) {
		if (s_Idle.isState == true) {
			++s_Idle.count;
			if (s_Idle.count % 10 == 0) {
				if (checkMax == false) {
					++s_Idle.index;
				}
				else if (checkMax == true) {
					--s_Idle.index;
				}
				if (s_Idle.index == 3) {
					//s_Idle.index = 0;
					checkMax = true;
					/*s_Idle.isState = false;
					s_Attack.isState = true;*/
				}
				else if (s_Idle.index == 0) {
					checkMax = false;
					AttackCN++;
					if (AttackCN == 2) {
						AttackCN = 0;
						s_Idle.isState = false;
						s_Attack.isState = true;

					}
				}
				s_Idle.count = 0;
			}
		}
		else if (s_Attack.isState == true) {
			++s_Attack.count;
			if (s_Attack.count % 8 == 0) {
				if (isHaveGun == false) {
					++s_Attack.index;
				}
				else {
					--s_Attack.index;
				}
				/*if (s_Attack.index == 3) {
					fire();
				}*/
				if (isDrawGun == false) {
					if (s_Attack.index == 8 && isHaveGun == false) {
						isDrawGun = true;
						s_Attack.index = 0;
					}
					else if (s_Attack.index == 0 && isHaveGun == true) {
						s_Attack.isState = false;
						s_Idle.isState = true;
						isHaveGun = false;
						AttackCount++;
					}
				}
				else {
					if (s_Attack.index == 1 && AttackCN == 0) {
						fire();
					}
					if (s_Attack.index == 3) {
						AttackCN++;
						if (AttackCN == 2) {
							isDrawGun = false;
							isHaveGun = true;
							AttackCN = 0;
							s_Attack.index = 7;
						}
						else {
							s_Attack.index = 0;
						}
					}
				}
				s_Attack.count = 0;
			}
		}
		else if (s_Move.isState == true) {
			++s_Move.count;
			if (s_Move.count % 8 == 0) {
				++s_Move.index;
				if (s_Move.index == 12) {
					s_Move.index = 0;
				}
				s_Move.count = 0;
			}
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

void enemy::tankAnimation()
{
	if (m_currHP > 0) {
		if (s_Idle.isState == true) {
			++s_Idle.count;
			if (s_Idle.count % 15 == 0) {
				++s_Idle.index;
				if (s_Idle.index == 2) {
					s_Idle.index = 0;
					AttackCN++;
					if (AttackCN == 3) {
						s_Attack.isState = true;
						s_Idle.isState = false;
						AttackCN = 0;
					}
				}
				s_Idle.count = 0;
			}
		}
		else if (s_Attack.isState == true) {
			++s_Attack.count;
			if (s_Attack.count % 10 == 0) {
				++s_Attack.index;
				if (s_Attack.index == 4) {
					EFFECTMANAGER->play("tankEffect", m_fX - 60, m_fY - 25);
					fire();
					s_Idle.isState = true;
					s_Attack.isState = false;
					s_Attack.index = 0;
				}
				s_Attack.count = 0;
			}
		}
		else if (s_Move.isState == true) {
			++s_Move.count;
			if (s_Move.count % 8 == 0) {
				++s_Move.index;
				if (s_Move.index == 6) {
					s_Move.index = 0;
				}
				s_Move.count = 0;
			}
		}
	}
	else {
		++s_Death.count;
		if (s_Death.count % 10 == 0) {
			++s_Death.index;
			if (s_Death.index == 6) {
				s_Death.index = 5;
				deathCount();
			}
			s_Idle.count = 0;
		}
	}
}

void enemy::deathCount()
{
	deathCN++;

	if (deathCN == 8) {
		isAlive = false;
		deathCN = 0;
	}
}

enemy::enemy()
{

}


enemy::~enemy()
{
}
