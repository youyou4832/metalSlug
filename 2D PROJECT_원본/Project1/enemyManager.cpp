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

void enemyManager::setEnemy(int enemyNum, int speed, const char * textName, int charNum)
{
	enemy* pEnemy;
	enemy* pSendBag;
	pEnemy = new enemy;
	pSendBag = new enemy;
	pEnemy->init(textName, PointMake(WINSIZEX / 2, WINSIZEY/2 - 30), WINSIZEX / 2 , WINSIZEY / 2 - 30, speed, charNum);
	pSendBag->init("sandbag", PointMake(WINSIZEX / 2 + 50, WINSIZEY / 2 + 110), WINSIZEX / 2 + 50, WINSIZEY / 2 + 110, speed, CharInfo::i_sandbag);
	
	m_vecEnemy.push_back(pSendBag);
	m_vecEnemy.push_back(pEnemy);
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

enemyManager::enemyManager()
{
}


enemyManager::~enemyManager()
{
}
