#include "stdafx.h"
#include "enemyManager.h"


HRESULT enemyManager::init()
{
	return S_OK;
}

void enemyManager::release()
{
	// vector의 첫 원소부터 마지막 원소까지 순회하며 각 원소를 delete한다
	for (m_iter = m_vecEnemy.begin(); m_iter != m_vecEnemy.end(); m_iter++)
	{
		delete (*m_iter);
	}
	// vector 자체를 삭제한다
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

void enemyManager::setEnemy(int enemyNum, int speed, const char * textName, int charNum)
{
	enemy* pEnemy;
	enemy* pSendBag;
	pEnemy = new enemy;
	pSendBag = new enemy;
	pEnemy->init(textName, PointMake(WINSIZEX / 2, WINSIZEY/2 - 30), WINSIZEX / 2 , WINSIZEY / 2 - 30, speed, charNum);
	pSendBag->init("sandbag", PointMake(WINSIZEX / 2 + 50, WINSIZEY / 2 + 110), WINSIZEX / 2 + 50, WINSIZEY / 2 + 110, speed, CharInfo::sandbag);
	m_vecEnemy.push_back(pEnemy);
	m_vecEnemy.push_back(pSendBag);
}

enemyManager::enemyManager()
{
}


enemyManager::~enemyManager()
{
}
