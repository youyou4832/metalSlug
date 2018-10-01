#include "stdafx.h"
#include "uiObject.h"
#include "uiButton.h"

HRESULT uiObject::init()
{
	return E_NOTIMPL;
}

void uiObject::release()
{
	m_iter = m_vecChild.begin();

	for (; m_iter != m_vecChild.end(); m_iter++)
	{
		delete (*m_iter);
	}
	m_vecChild.clear();
}

void uiObject::update()
{
	if (m_isHidden)	return;

	// TODO : ui update

	m_iter = m_vecChild.begin();
	for (; m_iter != m_vecChild.end(); m_iter++)
	{
		(*m_iter)->update();
	}
}

void uiObject::render(HDC hdc)
{
	if (m_isHidden)	return;

	// TODO : ui render

	m_iter = m_vecChild.begin();
	for (; m_iter != m_vecChild.end(); m_iter++)
	{
		(*m_iter)->render(hdc);
	}
}

void uiObject::addChild(uiObject * pChild)
{
	pChild->setParent(this);
	m_vecChild.push_back(pChild);
}

void uiObject::OnClick(uiButton * pSender)
{
	if (pSender->getTag() == 0)
	{
		for (auto p : m_vecChild)	// 원소들을 전부 p에 한 번씩 넣어줌. (반복문) p는 void 포인터 같은 거임.
		{
			if (p->getTag() == 3)
			{
				p->setIsHidden(true);
			}
		}
	}
}

uiObject::uiObject()
	: m_isHidden(false)
	, m_nTag(0)
	, m_pParent(NULL)
{
	m_position.x = 0;
	m_position.y = 0;

	m_rc = { 0, 0 };
}


uiObject::~uiObject()
{
}
