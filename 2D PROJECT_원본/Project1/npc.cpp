#include "stdafx.h"
#include "npc.h"


HRESULT npc::init(const char * szFileName, float x, float y, int speed, int charNum)
{
	string strFile = string(szFileName);
	m_pImg = IMAGEMANAGER->findImage(szFileName);
	m_itemImg = IMAGEMANAGER->findImage("item");
	m_fX = x;
	m_fY = y;
	m_speed = speed;
	m_charNum = charNum;

	m_isAlive = true;
	m_hang.isState = true;
	m_rc = RectMake(m_fX, m_fY, 64, 171);

	m_item.isState = true;
	return S_OK;
}

void npc::release()
{

}

void npc::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_SPACE)) {
		m_ropeHit.isState = true;
	}
	if (m_isAlive) {
		npcAnimation();
	}
	if (m_item.isState) {
		itemAnimation();
	}
}

void npc::render(HDC hdc)
{
	if (m_isAlive) {
		if (m_pImg) {
			Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
			Rectangle(hdc, m_itemRC.left, m_itemRC.top, m_itemRC.right, m_itemRC.bottom);
			if (m_hang.isState) {
				m_pImg->render(hdc, m_fX, m_fY, 21 * m_hang.index, 35, 21, 57, 3);
				m_pImg->render(hdc, m_fX + 9, m_fY-140, 16 * m_ropeHit.index, 92, 16, 48, 3);
			}
			else if (m_fall.isState) {
				m_pImg->render(hdc, m_fX, m_fY, 38 * m_fall.index, 171, 38, 44, 3);
			}
			else if (m_move.isState) {
				m_pImg->render(hdc, m_fX, m_fY + 40, 34 * m_move.index, 215, 34, 41, 3);
			}
		}
	}
	if (m_item.isState) {
		m_itemImg->render(hdc, m_fX - 70, m_fY + 110, 22 * m_item.index, 20, 22, 20, 3);
	}
}

void npc::npcAnimation()
{
	if (m_hang.isState) {
		++m_hang.count;
		if (m_hang.count % 8 == 0) {
			if (m_checkRotation == false)
				++m_hang.index;
			if (m_checkRotation == true)
				--m_hang.index;
			if (m_hang.index == 5) {
				m_hang.index = 4;
				m_checkRotation = true;
			}
			else if (m_hang.index == 0) {
				m_checkRotation = false;
			}
			m_hang.count = 0;
		}
	}
	else if (m_fall.isState) {
		++m_fall.count;
		if (m_fall.count % 2 == 0) {
			++m_fall.index;
			if (m_fall.index == 5) {
				m_fall.index = 0;
			}
			m_fall.count = 0;
		}
	}
	else if (m_move.isState) {
		++m_move.count;
		if (m_move.count % 5 == 0) {
			++m_move.index;
			move();
			if (m_move.index == 12) {
				m_move.index = 0;
			}
			m_move.count = 0;
		}
	}

	if (m_ropeHit.isState) {
		++m_ropeHit.count;
		if (m_ropeHit.count % 8 == 0) {
			++m_ropeHit.index;
			if (m_ropeHit.index == 7) {
				m_ropeHit.index = 7;
				m_hang.isState = false;
				m_fall.isState = true;
			}
			m_ropeHit.count = 0;
		}
	}
	
}

void npc::itemAnimation()
{
	if (m_item.isState) {
		++m_item.count;
		if (m_item.count % 5 == 0) {
			++m_item.index;
			if (++m_item.index == 4) {
				m_item.index = 0;
			}
			m_item.count = 0;
		}
		m_itemRC = RectMake(m_fX - 70, m_fY + 110, 66, 60);
	}
}

void npc::move()
{
	m_fX -= m_speed;
	if (m_fX < 0) {
		m_isAlive = false;
	}
	m_rc = RectMake(m_fX, m_fY + 40, 102, 123);
}

npc::npc()
{
}


npc::~npc()
{
}
