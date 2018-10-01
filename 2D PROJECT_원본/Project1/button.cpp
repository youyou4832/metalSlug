#include "stdafx.h"
#include "button.h"


HRESULT button::init(const char * szImageName, int x, int y, POINT ptBtnDown, POINT ptBtnUp, POINT ptBtnWait, CALLBACK_FUNC cb)
{
	m_strImgName = szImageName;

	m_pImg = IMAGEMANAGER->findImage(m_strImgName);
	m_fX = x;
	m_fY = y;

	m_rc = RectMakeCenter(x, y, m_pImg->getWidth(), m_pImg->getHeight());

	m_ptBtnDown = ptBtnDown;
	m_ptBtnUp = ptBtnUp;
	m_ptBtnWait = ptBtnWait;

	m_callbackFunction = cb;

	m_state = BUTTON_STATE::IDLE;

	return S_OK;
}

void button::release()
{
}

void button::update()
{
	if (PtInRect(&m_rc, g_ptMouse))
	{
		// 마우스가 닿았을 때의 상태는 여기에 추가하면 될 듯 함.
		// enum에 마우스 닿았을 때 상태 추가.
		m_state = BUTTON_STATE::WAIT;

		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			m_state = BUTTON_STATE::DOWN;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			m_state = BUTTON_STATE::UP;
			m_callbackFunction();
		}
	}
	else
	{
		m_state = BUTTON_STATE::IDLE;
	}
}

void button::render(HDC hdc)
{
	switch (m_state)
	{
	case BUTTON_STATE::IDLE:
	case BUTTON_STATE::UP:
		m_pImg->frameRender(hdc, m_rc.left, m_rc.top, m_ptBtnUp.x, m_ptBtnUp.y);
		break;
	case BUTTON_STATE::WAIT:
		m_pImg->frameRender(hdc, m_rc.left, m_rc.top, m_ptBtnWait.x, m_ptBtnWait.y);
		break;
	case BUTTON_STATE::DOWN:
		m_pImg->frameRender(hdc, m_rc.left, m_rc.top, m_ptBtnDown.x, m_ptBtnDown.y);
		break;
	}
}

button::button()
{
}


button::~button()
{
}
