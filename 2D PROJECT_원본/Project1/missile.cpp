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

	//m_pImg = IMAGEMANAGER->findImage(szImageName);
	if (m_charNum == CharInfo::i_sniper || m_charNum == CharInfo::i_cannon) {
		m_pImg = IMAGEMANAGER->findImage("specialBullet");
	}
	else if (m_charNum == CharInfo::i_normal) {
		m_pImg = IMAGEMANAGER->findImage("normalBullet");
	}

	if (m_charNum == CharInfo::i_boss)
	{
		m_pImg = IMAGEMANAGER->findImage("firebullet");
	}

	return S_OK;
}

void missile::release()
{
}

void missile::update()
{
	move();
	if (m_charNum == CharInfo::i_sniper || m_charNum == CharInfo::i_cannon) {
		ani_specialBullet();
	}

	if (m_charNum == CharInfo::i_boss) {
		ani_nomalBullet();
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

		if (charNum == CharInfo::i_boss) {
			m_pImg->render(hdc, m_fX, m_fY, 0 + (22 * fire_bullet.index), 714, 22, 22, 4);
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
		if (m_charNum == CharInfo::i_boss)
		{
			
			if (m_fAngle >= -1.45f)
			{
				
				m_fAngle -= 0.02;
				
			}

			m_fX += cosf(m_fAngle) * m_fSpeed;
			m_fY += -sinf(m_fAngle) * m_fSpeed;
			
			if (m_fX < 0 || m_fX > WINSIZEX || m_fY > WINSIZEY) {
				m_isFire = false;
			}

		}
		
		else
		{

			m_fX += cosf(m_fAngle) * m_fSpeed;
			m_fY += -sinf(m_fAngle) * m_fSpeed;
			

			if (m_fX < 0 || m_fX > WINSIZEX || m_fY > WINSIZEY || m_fY < 0) {
				m_isFire = false;
			}
		}

		m_rc = RectMakeCenter(m_fX + 10, m_fY + 10, 20, 20);
		
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
