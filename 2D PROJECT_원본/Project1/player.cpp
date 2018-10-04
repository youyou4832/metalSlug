#include "stdafx.h"
#include "player.h"
#include "animation.h"
#include "timer.h"

HRESULT player::init()
{
	m_upper.pAni = new animation;
	m_lower.pAni = new animation;

	m_upper.pImg = IMAGEMANAGER->addImage("image/player/player1.bmp", "image/player/player1.bmp", 931, 1531, true, RGB(255, 0, 255));
	m_lower.pImg = IMAGEMANAGER->addImage("image/player/player1.bmp", "image/player/player1.bmp", 931, 1531, true, RGB(255, 0, 255));

	m_upper.pAni->init(186, 240, 31, 240);	// UPPER_Appear
	m_upper.pAni->setFPS(FPS);
	m_upper.pAni->setPlayFrame(1, 6);
	m_upper.pAni->start();
	m_upper.pAni->setFrameUpdateSec(0.5f);

	m_lower.pAni->init(UPPER_AppearWidth, UPPER_AppearHeight, UPPER_AppearWidth / UPPER_AppearFrame, UPPER_AppearHeight, UPPER_AppearY);
	m_lower.pAni->setFPS(FPS);
	m_lower.pAni->setPlayFrame(0, 0);
	m_lower.pAni->stop();
	m_lower.pAni->setFrameUpdateSec(0.5f);

	m_upper.pImg->setX(WINSIZEX / 2);
	m_upper.pImg->setY(WINSIZEY / 2);
	m_lower.pImg->setX(WINSIZEX / 2);
	m_lower.pImg->setY(WINSIZEY / 2);

	m_upper.rc = RectMakeCenter(m_upper.pImg->getX(), m_upper.pImg->getY(), m_upper.pImg->getFrameWidth(), m_upper.pImg->getFrameHeight());
	m_lower.rc = RectMakeCenter(m_lower.pImg->getX(), m_lower.pImg->getY(), m_lower.pImg->getFrameWidth(), m_lower.pImg->getFrameHeight());

	m_fSpeed = 5.0f;
	m_fJumpSpeed = 10.0f; 
	m_fGravity = 0;
	m_nActUpper = UPPER_Appear;
	m_nActLower = LOWER_NULL;
	m_nDir = DIR_Right;
	m_isAct = false;

	ZeroMemory(&m_upper.rc, NULL);
	ZeroMemory(&m_lower.rc, NULL);

	return S_OK;
}

void player::update()
{
	m_upper.pAni->frameUpdate(TIMEMANAGER->getTimer()->getElapsedTime());
	m_lower.pAni->frameUpdate(TIMEMANAGER->getTimer()->getElapsedTime());

	move();
	actSet();

	m_upper.rc = RectMakeCenter(m_upper.pImg->getX(), m_upper.pImg->getY(), 
		m_upper.pImg->getFrameWidth(), m_upper.pImg->getFrameHeight());
	
	if(m_nActLower != LOWER_NULL)
		m_lower.rc = RectMakeCenter(m_lower.pImg->getX(), m_lower.pImg->getY(),
			m_lower.pImg->getFrameWidth(), m_lower.pImg->getFrameHeight());
}

void player::actSet()
{
	// ### ĳ���� ���� ���� ###
	if (g_ptMouse.x <= m_upper.pImg->getX())		// ���콺 �����Ͱ� ĳ���� ���ʿ� ���� ��� 
		m_nDir = DIR_Left;

	else if (g_ptMouse.x > m_upper.pImg->getX())	// ���콺 �����Ͱ� ĳ���� �����ʿ� ���� ���
		m_nDir = DIR_Right;

	// ### �ִϸ��̼� ������ ���� ###
	// ���� ���� ��� return
	if (m_nActUpper == UPPER_Appear && m_upper.pAni->getIsPlaying() == true) return;

	// ���� ����� ������
	else if ((m_nActUpper == UPPER_Appear && m_upper.pAni->getIsPlaying() == false)	// -> ���
		/*|| (m_nActUpper == UPPER_Idle && m_isAct == false)*/)					// �Ǵ� ��� ������� �ٲ���� ��� ������ ����
	{
		m_nActUpper = UPPER_Idle;
		m_nActLower = LOWER_Idle;
	}

	else if (m_isAct == true)
	{
		// ��ü
		switch (m_nActUpper)
		{
		case UPPER_Idle:	// ���
			m_upper.pAni->init(UPPER_IdleWidth, UPPER_IdleHeight, UPPER_IdleWidth / UPPER_IdleFrame, UPPER_IdleHeight, UPPER_IdleY);
			m_upper.pAni->setPlayFrame(1, UPPER_IdleFrame, true, true);

		case UPPER_Sit:		// �ɱ�
			m_upper.pAni->init(UPPER_SitWidth, UPPER_SitHeight, UPPER_SitWidth / UPPER_SitFrame, UPPER_SitY);
			m_upper.pAni->setPlayFrame(1, UPPER_SitFrame, false, true);

		case UPPER_Move:	// �̵�
			m_upper.pAni->init(UPPER_MoveWidth, UPPER_MoveHeight, UPPER_MoveWidth / UPPER_MoveFrame, UPPER_MoveY);
			m_upper.pAni->setPlayFrame(1, UPPER_MoveFrame, false, true);
		}

		// ��ü
		switch (m_nActLower)
		{
		case LOWER_Idle:	// ���
			m_lower.pAni->init(LOWER_IdleWidth, LOWER_IdleHeight, LOWER_IdleWidth / LOWER_IdleFrame, LOWER_IdleHeight, LOWER_IdleY);
			m_lower.pAni->setPlayFrame(1, LOWER_IdleFrame, true, true);

		case LOWER_Move:	// �̵�
			m_lower.pAni->init(LOWER_MoveWidth, LOWER_MoveHeight, LOWER_MoveWidth / LOWER_MoveFrame, LOWER_MoveHeight, LOWER_MoveY);
			m_lower.pAni->setPlayFrame(1, LOWER_MoveFrame, false, true);
		}

		m_upper.pAni->start();
		m_lower.pAni->start();
		m_isAct = false;
	}
}

void player::move()
{
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		if (m_isAct == false)
			m_isAct = true;

		m_nActUpper = UPPER_Sit;
		m_nActLower = LOWER_NULL;
	}
	else if (KEYMANAGER->isStayKeyDown('A') && m_upper.pImg->getX() > 0)
	{
		if (m_isAct == true)
			m_isAct = false;

		m_nActUpper = UPPER_Move;
		m_nActLower = LOWER_Move;

		m_upper.pImg->setX(m_upper.pImg->getX() - m_fSpeed); 

		if (m_nActLower != LOWER_NULL)
			m_lower.pImg->setX(m_lower.pImg->getX() - m_fSpeed);
	}
	else if (KEYMANAGER->isStayKeyDown('D') && m_upper.pImg->getX() < WINSIZEX)
	{
		if (m_isAct == true)
			m_isAct = false;

		m_nActUpper = UPPER_Move;
		m_nActLower = LOWER_Move;

		m_upper.pImg->setX(m_upper.pImg->getX() + m_fSpeed);

		if (m_nActLower != LOWER_NULL)
			m_lower.pImg->setX(m_lower.pImg->getX() + m_fSpeed);
	}

	// Ű�� ���� ��� �ൿ���� �������� �ٲ�
	if (KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('D'))
	{
		m_nActUpper = UPPER_Idle;
		m_nActLower = LOWER_Idle;
		m_isAct = false;
	}
	// ���� (���콺 ������)
}

void player::release()
{
	SAFE_DELETE(m_upper.pAni);
	SAFE_DELETE(m_lower.pAni);
}

void player::render(HDC hdc)
{
	if (m_upper.pAni->getIsPlaying() == true)
		m_upper.pImg->aniRender(hdc, m_upper.pImg->getX(), m_upper.pImg->getY(), m_upper.pAni);

	if (m_lower.pAni->getIsPlaying() == true)
		m_lower.pImg->aniRender(hdc, m_lower.pImg->getX(), m_upper.pImg->getY() + m_upper.pAni->getFrameHeight(), m_lower.pAni);
}
player::player()
{
}


player::~player()
{
}
