#include "stdafx.h"
#include "missile.h"
//#include "player.h"

HRESULT missile::init(int charNum)
{
	m_fAngle = PI / 2;
	m_fRange = WINSIZEY - 72;
	m_fSpeed = 8.0f;
	m_fX = 0.0f;
	m_fY = 0.0f;
	m_fFiredX = 0.0f;
	m_fFiredY = 0.0f;
	m_isFire = false;
	m_charNum = charNum;
	//memset(&m_rc, 3, sizeof(m_rc));
	ZeroMemory(&m_rc, sizeof(m_rc));
	
	if (g_saveData.selected_player_id == 1) {
		m_pImg = IMAGEMANAGER->findImage("mutal");
	}

	return S_OK;
}

HRESULT missile::init(const char * szImageName, float speed,
	float x, float y, float angle, float range, int charNum)
{
	m_fAngle = angle;
	m_fRange = range;
	m_fSpeed = speed;
	m_fX = x;
	m_fY = y;
	m_fFiredX = x;
	m_fFiredY = y;
	m_isFire = false;
	m_charNum = charNum;
	//memset(&m_rc, 3, sizeof(m_rc));
	ZeroMemory(&m_rc, sizeof(m_rc));

	if (m_charNum == CharInfo::i_sniper || m_charNum == CharInfo::i_cannon) {
		m_pImg = IMAGEMANAGER->findImage("specialBullet");
	}
	else if (m_charNum == CharInfo::i_normal) {
		m_pImg = IMAGEMANAGER->findImage("normalBullet");
	}
	else if (m_charNum == CharInfo::i_tank) {
		m_pImg = IMAGEMANAGER->findImage("tank");
	}
	else if (m_charNum == CharInfo::i_nomalboss || m_charNum == CharInfo::i_rageboss)
	{
		m_pImg = IMAGEMANAGER->findImage("boss");
	}
	else if (m_charNum == CharInfo::i_player) {
		m_pImg = IMAGEMANAGER->findImage(szImageName);
	}

	

	return S_OK;
}

void missile::release()
{
}

void missile::update()
{
	move();
	if (m_charNum == CharInfo::i_sniper || m_charNum == CharInfo::i_cannon || m_charNum == CharInfo::i_tank) {
		ani_specialBullet();
	}

	else if (m_charNum == CharInfo::i_nomalboss) {
		ani_nomalBullet();
	}

	else if (m_charNum == CharInfo::i_rageboss)
	{
		ani_rageBullet();
	}

}

void missile::render(HDC hdc, int charNum)
{
	if (m_isFire)
	{
		//Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
		if (charNum == CharInfo::i_sniper || charNum == CharInfo::i_cannon) {
			m_pImg->render(hdc, m_fX, m_fY, 10 * special_bullet.index, 33, 10, 10, 2);
		}
		else if (charNum == CharInfo::i_normal) {
			m_pImg->render(hdc, m_fX, m_fY, 0, 0, 24, 24, 3);
		}
		else if (charNum == CharInfo::i_tank) {
			m_pImg->render(hdc, m_fX, m_fY, 46 * special_bullet.index, 374, 46, 22, 3);
		}
		else if (charNum == CharInfo::i_nomalboss) {
			m_pImg->render(hdc, m_fX, m_fY, 0 + (22 * fire_bullet.index), 714, 22, 22, 4);
		}

		else if (charNum == CharInfo::i_rageboss) {
			m_pImg->render(hdc, m_fX, m_fY, 352 - (32 * cannon_bullet.index), 681, 32, 33, 5);
		}
		else if (charNum == CharInfo::i_player) {
			m_pImg->render(hdc, m_fX, m_fY, 0, 0, 8, 8, 3);
		}
	}

	char szText[128];
	_stprintf_s(szText, "%f", m_fAngle);

	TextOut(hdc, 100, 200, szText, strlen(szText));
}

void missile::fire(float x, float y)
{
	if (!m_isFire)
	{
		m_isFire = true;
		// 시작 위치
		m_fFiredX = m_fX = x;
		m_fFiredY = m_fY = y;


		// 플레이어의 위치를 알아야 각도를 구할 수 있다
		/*if (m_pTarget)
		{
			m_fAngle = MY_UTIL::getAngle(
				m_fX, m_fY,
				m_pTarget->getX(), m_pTarget->getY());
		}*/
	}
}

void missile::move()
{
	if (m_isFire)
	{
		if (m_charNum == CharInfo::i_nomalboss || m_charNum == CharInfo::i_rageboss)
		{

			if (m_fAngle >= -1.45f)
			{

				m_fAngle -= 0.02;

			}

			m_fX += cosf(m_fAngle) * m_fSpeed;
			m_fY += -sinf(m_fAngle) * m_fSpeed;

			if (m_fX < 0 || m_fX > WINSIZEX || m_fY > WINSIZEY) {
				m_isFire = false;
				angle_count.index = 0;
			}
			m_rc = RectMakeCenter(m_fX + 50, m_fY + 10, 20, 20);
		}

		else
		{

			m_fX += cosf(m_fAngle) * m_fSpeed;
			m_fY += -sinf(m_fAngle) * m_fSpeed;


			if (m_fX < 0 || m_fX > WINSIZEX || m_fY > WINSIZEY || m_fY < 0) {
				m_isFire = false;

			}
			m_fX += cosf(m_fAngle) * m_fSpeed;
			m_fY += -sinf(m_fAngle) * m_fSpeed;
			if (m_charNum == CharInfo::i_normal) {
				m_rc = RectMakeCenter(m_fX + 40, m_fY + 35, 40, 10);
			}
			else {
				m_rc = RectMakeCenter(m_fX + 10, m_fY + 10, 20, 20);
			}
			if (m_fX < 0 || m_fX > WINSIZEX || m_fY > WINSIZEY || m_fY < 0) {
				m_isFire = false;
			}

			m_rc = RectMakeCenter(m_fX + 10, m_fY + 10, 20, 20);

		}
	}
}

void missile::ani_specialBullet()
{
	++special_bullet.count;
	if (special_bullet.count % 5 == 0) {
		++special_bullet.index;
		if (special_bullet.index == 4) {
			special_bullet.index = 0;
		}
		special_bullet.count = 0;
	}
}

void missile::ani_nomalBullet()
{
	++fire_bullet.count;
	if (fire_bullet.count % 5 == 0) {
		++fire_bullet.index;
		if (fire_bullet.index == 4) {
			fire_bullet.index = 0;
		}
		fire_bullet.count = 0;
	}
}

void missile::ani_rageBullet()
{
	 ++cannon_bullet.count;
	 if (cannon_bullet.count % 10 == 0) {
		
		 if (cannon_bullet.index != 11)
		 {
			 ++cannon_bullet.index;
		 }

		 if (m_fY >= WINSIZEY)
		 {
			 cannon_bullet.index = 0;;
		 }
		
		 cannon_bullet.count = 0;
	 }

}

void missile::angleCount()
{
	++angle_count.count;
	if (angle_count.count % 5 == 0) {
		++angle_count.index;
	
		angle_count.count = 0;
	}
}



missile::missile()
{
}


missile::~missile()
{
}
