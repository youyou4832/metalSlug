#include "stdafx.h"
#include "effectManager.h"
#include "effect.h"


HRESULT effectManager::init()
{
	return S_OK;
}

void effectManager::release()
{
	vector<effect*>::iterator iterVE;
	vector<effect*> vecE;

	// m_mapEffects < key, value >
	// key : string / (iterator->first)
	// value ; vector<effect*> / (iterator->second)
	// m_iter : m_mapEffects을 구성하는 원소 (pair : key, value)를 담고 있는 
	//			메모리의 주소 ( == 포인터)

	m_iter = m_mapEffects.begin();

	for (; m_iter != m_mapEffects.end();)
	{
		vecE = (m_iter->second);

		// iterVE : vecE( vector <effect*> )를 구성하는 원소를 담고 있는 메모리의 주소
		for (iterVE = vecE.begin();
			iterVE != vecE.end();
			++iterVE)
		{
			if ((*iterVE))
			{
				(*iterVE)->release();	// effect의 animation 동적할당 해제
				SAFE_DELETE((*iterVE));	// addEffect 함수의 effect 동적할당 해제
			}
		}
		vecE.clear();
		m_iter = m_mapEffects.erase(m_iter);
	}

	m_mapEffects.clear();
}

void effectManager::update()
{
	for (m_iter = m_mapEffects.begin(); m_iter != m_mapEffects.end(); m_iter++)
	{
		vecEffect::iterator iter;
		//이펙트형 포인터를 원소로 갖는 벡터
		for (iter = m_iter->second.begin(); iter != m_iter->second.end(); iter++)
		{
			(*iter)->update();
		}

	}
}

void effectManager::render(HDC hdc , int scalar)
{
	for (m_iter = m_mapEffects.begin(); m_iter != m_mapEffects.end(); m_iter++)
	{
		vecEffect::iterator iter;
		for (iter = m_iter->second.begin(); iter != m_iter->second.end(); iter++)
		{
			(*iter)->render(hdc, scalar);
		}

	}
}

void effectManager::addEffect(string effectName, const char * imageName, int imageWidth, int imageHeight, int frameWidth, int frameHeight, int fps, float elapsedTime, int bufferCount)
{
	image* pImage = IMAGEMANAGER->addImage(effectName, imageName, imageWidth, imageHeight, true, RGB(255, 0, 255));

	vecEffect vecEffects;
	for (int i = 0; i < bufferCount; ++i)
	{
		effect* pEffect = new effect;
		pEffect->init(pImage, frameWidth, frameHeight, fps, elapsedTime);

		vecEffects.push_back(pEffect);
	}

	m_mapEffects.insert(pair<string, vecEffect>(effectName, vecEffects));
}

void effectManager::play(string effectName, int x, int y)
{
	m_iter = m_mapEffects.find(effectName);

	if (m_iter != m_mapEffects.end())
	{
		vecEffect::iterator iter;
		for (iter = m_iter->second.begin(); iter != m_iter->second.end(); iter++)
		{
			if ((*iter)->getIsAlive()) continue;

			(*iter)->startEffect(x, y);
			return;
		}
	}
}

effectManager::effectManager()
{
}


effectManager::~effectManager()
{
}
