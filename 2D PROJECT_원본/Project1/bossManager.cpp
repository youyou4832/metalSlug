#include "stdafx.h"
#include "bossManager.h"


HRESULT bossManager::init()
{
	return	S_OK;
}

void bossManager::release()
{
	
	for (m_iter = m_vecEnemy.begin(); m_iter != m_vecEnemy.end(); m_iter++)
	{
		delete (*m_iter);
	}
	m_vecEnemy.clear();
}

void bossManager::update()
{
	for (m_iter = m_vecEnemy.begin(); m_iter != m_vecEnemy.end(); m_iter++)
	{
		(*m_iter)->update();
	}
}

void bossManager::render(HDC hdc)
{
	for (m_iter = m_vecEnemy.begin(); m_iter != m_vecEnemy.end(); m_iter++)
	{
		(*m_iter)->render(hdc);
	}
}

void bossManager::setEnemy(int countX, int countY)
{
	// vector의 마지막 원소 뒤에 새로운 데이터를 추가한다
	//예시 : m_vecEnemy.push_back(m_pUfo);

}

void bossManager::damaged(int damage)
{
	m_nCurrHP -= damage;
	if (m_nCurrHP <= 0)
	{
		m_nCurrHP = 0;
	}
}

void bossManager::setTarget()
{
	for (m_iter = m_vecEnemy.begin(); m_iter != m_vecEnemy.end(); m_iter++)
	{
		//(*m_iter)->setTarget(pTarget);
	}
}

bossManager::bossManager()
{
}


bossManager::~bossManager()
{
}
