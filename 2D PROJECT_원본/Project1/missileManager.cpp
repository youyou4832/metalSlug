#include "stdafx.h"
#include "missileManager.h"


HRESULT missileManager::init(const char* szImageName, float range, int maxCount)
{
	m_fRange = range;
	m_nMaxCount = maxCount;
	m_szImageName = szImageName;
	//m_vecMissile.resize(m_nMaxCount);
	m_vecMissile.reserve(m_nMaxCount);

	// º¤ÅÍÀÇ ¿ø¼ÒÀÇ °¹¼ö
	//int size = m_vecMissile.size();

	return S_OK;
}

HRESULT missileManager::init(int maxCount)
{
	m_nMaxCount = maxCount;
	//m_vecMissile.resize(m_nMaxCount);
	m_vecMissile.reserve(m_nMaxCount);

	// º¤ÅÍÀÇ ¿ø¼ÒÀÇ °¹¼ö
	//int size = m_vecMissile.size();

	return S_OK;
}

void missileManager::release()
{
	for (m_iter = m_vecMissile.begin();
		m_iter != m_vecMissile.end(); m_iter++)
	{
		delete (*m_iter);
	}
	m_vecMissile.clear();
}

void missileManager::update()
{
	for (m_iter = m_vecMissile.begin(); m_iter != m_vecMissile.end(); m_iter++)
	{
		(*m_iter)->update();
	}
}

void missileManager::render(HDC hdc, int charNum)
{
	for (m_iter = m_vecMissile.begin(); m_iter != m_vecMissile.end(); m_iter++)
	{
		(*m_iter)->render(hdc, charNum);
	}
}

void missileManager::fire(float x, float y, float angle, float speed, int charNum) // ¿¡³Ê¹Ì ÃÑ¾Ë init
{
	vector<missile*>::iterator iter;
	missile* pMissile;
	pMissile = NULL;

	for (iter = m_vecMissile.begin(); iter != m_vecMissile.end(); iter++) {
		if ((*iter) != NULL) {
			if (!(*iter)->getIsFire())
			{
				pMissile = (*iter);
				pMissile->init(m_szImageName, speed, x, y, angle, m_fRange, charNum);
			}
		}
	}

	if (pMissile == NULL) {
		pMissile = new missile;
		pMissile->init(m_szImageName, speed, x, y, angle, m_fRange, charNum);
		m_vecMissile.push_back(pMissile);
	}
	pMissile->fire(x, y);

}

void missileManager::fire(float x, float y, int charNum) // ÇÃ·¹ÀÌ¾î ÃÑ¾Ë init
{
	vector<missile*>::iterator iter;
	missile* pMissile;
	pMissile = NULL;

	for (iter = m_vecMissile.begin(); iter != m_vecMissile.end(); iter++) {
		if ((*iter) != NULL) {
			if (!(*iter)->getIsFire())
			{
				pMissile = (*iter);
			}
		}
	}

	if (pMissile == NULL) {
		pMissile = new missile;
		pMissile->init(charNum);
		m_vecMissile.push_back(pMissile);
	}
	pMissile->setisFind(false);
	pMissile->setAngle(PI / 2);
	pMissile->setMaxCN(2);
	pMissile->fire(x, y);

}

void missileManager::move()
{
}

missileManager::missileManager()
{
}


missileManager::~missileManager()
{
}
