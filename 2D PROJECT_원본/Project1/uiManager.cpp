#include "stdafx.h"
#include "uiManager.h"


HRESULT uiManager::init()
{
	return S_OK;
}

void uiManager::release()
{
}

void uiManager::update()
{
	for (m_iter = m_vecUIObjects.begin();
		m_iter != m_vecUIObjects.end(); m_iter++)
	{
		if ((*m_iter)->getIsHidden() == false)
			(*m_iter)->update();
	}
}

void uiManager::render(HDC hdc)
{
	for (m_iter = m_vecUIObjects.begin();
		m_iter != m_vecUIObjects.end(); m_iter++)
	{
		if ((*m_iter)->getIsHidden() == false)
			(*m_iter)->render(hdc);
	}
}

void uiManager::addUIObject(uiObject * pUI)
{
	//((uiButton*)pUI)->setDelegate(this);
	m_vecUIObjects.push_back(pUI);
}

void uiManager::OnClick(uiButton * pSender)
{
	//if (pSender->m_nTag == 1)

}

uiManager::uiManager()
{
}


uiManager::~uiManager()
{
}
