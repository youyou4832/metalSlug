#include "stdafx.h"
#include "enemyManager.h"


HRESULT enemyManager::init()
{
	return S_OK;
}

void enemyManager::release()
{
	// vector�� ù ���Һ��� ������ ���ұ��� ��ȸ�ϸ� �� ���Ҹ� delete�Ѵ�
	for (m_iter = m_vecEnemy.begin(); m_iter != m_vecEnemy.end(); m_iter++)
	{
		delete (*m_iter);
	}
	// vector ��ü�� �����Ѵ�
	m_vecEnemy.clear();
}

void enemyManager::update()
{
	for (m_iter = m_vecEnemy.begin(); m_iter != m_vecEnemy.end(); m_iter++)
	{
		(*m_iter)->update();
	}
}

void enemyManager::render(HDC hdc)
{
	for (m_iter = m_vecEnemy.begin(); m_iter != m_vecEnemy.end(); m_iter++)
	{
		(*m_iter)->render(hdc);
	}
}


void enemyManager::setSniper(const char * textName, float x, float y, int speed, int charNum)
{
	enemy* sniper;
	enemy* sendBag;
	sniper = new enemy;
	sendBag = new enemy;
	sniper->init(textName, PointMake(x, y), x, y, speed, charNum);
	sendBag->init("sandbag", PointMake(x + 50, y + 140), x + 50, y + 140, speed, CharInfo::i_sandbag);
	
	m_vecEnemy.push_back(sendBag);
	m_vecEnemy.push_back(sniper);
}

void enemyManager::setCannon(const char * textName, float x, float y, int speed, int charNum)
{
	enemy* cannon;
	cannon = new enemy;
	cannon->init(textName, PointMake(x, y), x, y, speed, charNum);

	m_vecEnemy.push_back(cannon);
}

enemyManager::enemyManager()
{
}


enemyManager::~enemyManager()
{
}
