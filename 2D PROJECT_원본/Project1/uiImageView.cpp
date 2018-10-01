#include "stdafx.h"
#include "uiImageView.h"


HRESULT uiImageView::init(const char * szImageName, float x, float y)
{
	string str = szImageName;
	m_pImg = IMAGEMANAGER->findImage(str);
	m_position.x = x;
	m_position.y = y;

	m_rc = RectMake(m_position.x, m_position.y, m_pImg->getWidth(), m_pImg->getHeight());

	return S_OK;
}

void uiImageView::update()
{
}

void uiImageView::render(HDC hdc)
{
	if (m_isHidden) return;

	m_pImg->render(hdc, m_position.x, m_position.y);

	uiObject::render(hdc);
}

uiImageView::uiImageView()
	: m_pImg(NULL)
{
}


uiImageView::~uiImageView()
{
}
