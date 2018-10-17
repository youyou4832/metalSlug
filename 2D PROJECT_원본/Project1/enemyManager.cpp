#include "stdafx.h"
#include "enemyManager.h"


HRESULT enemyManager::init()
{
	m_totalEnemy = 0;
	return S_OK;
}

void enemyManager::release()
{
	// vector의 첫 원소부터 마지막 원소까지 순회하며 각 원소를 delete한다
	for (m_iter = m_vecEnemy.begin(); m_iter != m_vecEnemy.end(); m_iter++)
	{
		(*m_iter)->release();
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


void enemyManager::setSniper(const char * textName, float x, float y, int speed, player* player)
{
	enemy* sniper;
	enemy* sendBag;
	sniper = new enemy;
	sendBag = new enemy;
	sniper->init(textName, PointMake(x, y), x, y, speed, CharInfo::i_sniper, player);
	sendBag->init("sandbag", PointMake(x + 50, y + 140), x + 50, y + 140, speed, CharInfo::i_sandbag, player);
	
	m_vecEnemy.push_back(sendBag);
	m_vecEnemy.push_back(sniper);

	++m_totalEnemy;
}

void enemyManager::setCannon(const char * textName, float x, float y, int speed, player* player, int enemyNumber, bool isMove)
{
	enemy* cannon;
	if (isMove == true) {
		for (int i = 0; i < enemyNumber; i++) {
			cannon = new enemy;
			cannon->init(textName, PointMake(x + 100 * i, y), WINSIZEX / 2 + 100 * i, y, speed, CharInfo::i_cannon, player);
			m_vecEnemy.push_back(cannon);
		}
	}
	else {
		for (int i = 0; i < enemyNumber; i++) {
			cannon = new enemy;
			cannon->init(textName, PointMake(x + 100 * i, y), x + 100 * i, y, speed, CharInfo::i_cannon, player);
			m_vecEnemy.push_back(cannon);
		}
	}
	
	m_totalEnemy += enemyNumber;
}

void enemyManager::setNormal(const char * textName, float x, float y, int speed, player* player, int enemyNumber, bool isMove)
{
	enemy* normal;
	if (isMove == true) {
		for (int i = 0; i < enemyNumber; i++) {
			normal = new enemy;
			normal->init(textName, PointMake(x + 250 + 50 * i, y), WINSIZEX - 100 * i, y, speed, CharInfo::i_normal, player);
			m_vecEnemy.push_back(normal);
		}
	}
	else {
		for (int i = 0; i < enemyNumber; i++) {
			normal = new enemy;
			normal->init(textName, PointMake(x + 250 + 50 * i, y), x + 250 + 50 * i, y, speed, CharInfo::i_normal, player);
			m_vecEnemy.push_back(normal);
		}
	}
	
	m_totalEnemy += enemyNumber;
}

void enemyManager::setTank(const char * textName, float x, float y, int speed, player* player, bool isMove)
{
	enemy* tank;
	if (isMove == true) {
		tank = new enemy;
		tank->init(textName, PointMake(x, y), WINSIZEX - 300, y, speed, CharInfo::i_tank, player);
	}
	else {
		tank = new enemy;
		tank->init(textName, PointMake(x, y), x, y, speed, CharInfo::i_tank, player);
	}
	m_vecEnemy.push_back(tank);
	++m_totalEnemy;
}

enemyManager::enemyManager()
{
}


enemyManager::~enemyManager()
{
}
