#include "stdafx.h"
#include "uiButton.h"

HRESULT uiButton::init(const char * szImageName, int x, int y,
	POINT ptBtnDown, POINT ptBtnUp, POINT ptBtnWait)
{
	m_strImgName = szImageName;

	// ������ �ϴ� �̹��� �ε� ���
	// m_pImg = IMAGEMANAGER->addImage(m_strImgName, szImageName, )

	// �̹��� �ε�� ���ε忡�� ��� ó��
	m_pImg = IMAGEMANAGER->findImage(m_strImgName);
	m_fX = x;
	m_fY = y;

	m_rc = RectMake(x, y, m_pImg->getWidth(), m_pImg->getHeight());

	m_ptBtnDown = ptBtnDown;
	m_ptBtnUp = ptBtnUp;
	m_ptBtnWait = ptBtnWait;
	m_state = ButtonState::IDLE;

	return S_OK;
}

void uiButton::release()
{
}

void uiButton::update()
{
	if (PtInRect(&m_rc, g_ptMouse))
	{
		// ���콺�� ����� ���� ���´� ���⿡ �߰��ϸ� �� �� ��.
		// enum�� ���콺 ����� �� ���� �߰�.
		m_state = ButtonState::WAIT;

		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			m_state = ButtonState::DOWN;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			m_state = ButtonState::UP;

			if (m_pDelegate)
				m_pDelegate->OnClick(this);
		}
	}
	else
	{
		m_state = ButtonState::IDLE;
	}
}

void uiButton::render(HDC hdc)
{
	switch (m_state)
	{
	case ButtonState::IDLE:
	case ButtonState::UP:
		m_pImg->frameRender(hdc, m_rc.left, m_rc.top, m_ptBtnUp.x, m_ptBtnUp.y);
		break;
	case ButtonState::WAIT:
		m_pImg->frameRender(hdc, m_rc.left, m_rc.top, m_ptBtnWait.x, m_ptBtnWait.y);
		break;
	case ButtonState::DOWN:
		m_pImg->frameRender(hdc, m_rc.left, m_rc.top, m_ptBtnDown.x, m_ptBtnDown.y);
		break;
	}
}

uiButton::uiButton()
{
}


uiButton::~uiButton()
{
}
