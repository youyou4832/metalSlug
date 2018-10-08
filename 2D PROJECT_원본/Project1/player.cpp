#include "stdafx.h"
#include "player.h"
#include "animation.h"
#include "timer.h"
#include "missileManager.h"

HRESULT player::init(float x, float y)
{
	// �÷��̾�
	m_upper.pAni = new animation;
	m_lower.pAni = new animation;

	m_upper.pImg = IMAGEMANAGER->addImage("image/player/player1.bmp", "image/player/player1.bmp", 931, 1531, true, RGB(255, 0, 255));
	m_lower.pImg = IMAGEMANAGER->addImage("image/player/player1.bmp", "image/player/player1.bmp", 931, 1531, true, RGB(255, 0, 255));
	m_upper.pImgReverse = IMAGEMANAGER->addImage("image/player/player2.bmp", "image/player/player2.bmp", 931, 1531, true, RGB(255, 0, 255));
	m_lower.pImgReverse = IMAGEMANAGER->addImage("image/player/player2.bmp", "image/player/player2.bmp", 931, 1531, true, RGB(255, 0, 255));

	m_upper.pAni->init(UPPER_AppearWidth, UPPER_AppearHeight, UPPER_AppearWidth / UPPER_AppearFrame, UPPER_AppearHeight, UPPER_AppearY);
	m_upper.pAni->setFPS(FPS);
	m_upper.pAni->setPlayFrame(1, UPPER_AppearFrame);
	m_upper.pAni->start();
	m_upper.pAni->setFrameUpdateSec(0.1f);

	m_lower.pAni->init(1, 1, 1, 1);
	m_lower.pAni->setFPS(FPS);
	m_lower.pAni->setPlayFrame(1, 1);
	m_lower.pAni->stop();
	m_lower.pAni->setFrameUpdateSec(0.1f);

	m_upper.pImg->setX(x);
	m_upper.pImg->setY(y);
	m_lower.pImg->setX(x);
	m_lower.pImg->setY(y);

	m_fSpeed = 3.0f;
	m_fJumpSpeed = 10.0f; 
	m_fGravity = 0;
	m_fReplaceY = 0;
	m_nActUpper = UPPER_Appear;
	m_nActLower = LOWER_NULL;
	m_nDir = DIR_Right;
	m_nDirY = DIR_Right;
	m_isAct = false;

	g_ptMouse = { WINSIZEX, WINSIZEY };

	ZeroMemory(&m_upper.rc, NULL);
	ZeroMemory(&m_lower.rc, NULL);


	// �̻���
	IMAGEMANAGER->addImage("playerMissile", "image/player/playerBullet.bmp", 8, 8, true, RGB(255, 0, 255));

	m_pMissileMgr = new missileManager;
	m_pMissileMgr->init("playerMissile", WINSIZEY, 10);



	return S_OK;
}

void player::update()
{
	// �÷��̾�
	move();
	actSet();
	m_upper.pAni->frameUpdate(TIMEMANAGER->getTimer()->getElapsedTime());
	m_lower.pAni->frameUpdate(TIMEMANAGER->getTimer()->getElapsedTime());

	// �̻���
	m_pMissileMgr->update();
}

void player::actSet()
{
	// ### ĳ���� ���� ���� ###
	if (g_ptMouse.x <= m_upper.pImg->getX())		// ���콺 �����Ͱ� ĳ���� ���ʿ� ���� ��� 
		m_nDir = DIR_Left;

	else if (g_ptMouse.x > m_upper.pImg->getX())	// ���콺 �����Ͱ� ĳ���� �����ʿ� ���� ���
		m_nDir = DIR_Right;


	/* ### �ִϸ��̼� ������ ���� ###
	���� ���� ��� return */
	if (m_nActUpper == UPPER_Appear && m_upper.pAni->getIsPlaying() == true) return;

	// �ݺ���� ����, isPlaying == false�� ���
	else if (m_upper.pAni->getIsPlaying() == false && m_lower.pAni->getIsPlaying() == false)
	{
		if (m_nActUpper == UPPER_Appear)
			m_lower.pImg->setY(WINSIZEY / 2 + 60);

		m_nActUpper = UPPER_Idle;
		m_nActLower = LOWER_Idle; 
		m_isAct = true;
	}

	if (m_isAct == true)
	{
		// ��ü
		switch (m_nActUpper)
		{
		case UPPER_Idle:	// ���
			m_upper.pAni->init(UPPER_IdleWidth, UPPER_IdleHeight, UPPER_IdleWidth / UPPER_IdleFrame, UPPER_IdleHeight, UPPER_IdleY);
			
			if (m_nDir == DIR_Left)
			{
				m_upper.pAni->setPlayFrameReverse(1, UPPER_IdleFrame, true, true);
			}
			else
				m_upper.pAni->setPlayFrame(1, UPPER_IdleFrame, true, true);

			break;

		case UPPER_Sit:		// �ɱ�
			m_upper.pAni->init(UPPER_SitWidth, UPPER_SitHeight, UPPER_SitWidth / UPPER_SitFrame, UPPER_SitHeight, UPPER_SitY);

			if (m_nDir == DIR_Left)
			{
				m_upper.pAni->setPlayFrameReverse(0, UPPER_SitFrame, false, false);
			}
			else
				m_upper.pAni->setPlayFrame(1, UPPER_SitFrame, false, false);

			break;

		case UPPER_Move:	// �̵�
			m_upper.pAni->init(UPPER_MoveWidth, UPPER_MoveHeight, UPPER_MoveWidth / UPPER_MoveFrame, UPPER_MoveHeight, UPPER_MoveY);

			if (m_nDir == DIR_Left)
				m_upper.pAni->setPlayFrameReverse(1, UPPER_MoveFrame, false, true);
			else
				m_upper.pAni->setPlayFrame(1, UPPER_MoveFrame, false, true);

			break;
			
		case UPPER_Att:
			m_upper.pAni->init(UPPER_AttWidth, UPPER_AttHeight, UPPER_AttWidth / UPPER_AttFrame, UPPER_AttHeight, UPPER_AttY);

			if (m_nDir == DIR_Left)
				m_upper.pAni->setPlayFrameReverse(1, UPPER_AttFrame, false, false);
			else
				m_upper.pAni->setPlayFrame(1, UPPER_AttFrame, false, false);

			break;
		}

		// ��ü
		switch (m_nActLower)
		{
		case LOWER_NULL:
			m_lower.pAni->setPlayFrame(0, 0);
			break;

		case LOWER_Idle:	// ���
			m_lower.pAni->init(LOWER_IdleWidth, LOWER_IdleHeight, LOWER_IdleWidth / LOWER_IdleFrame, LOWER_IdleHeight, LOWER_IdleY);

			if (m_nDir == DIR_Left)
			{
				m_lower.pAni->setPlayFrameReverse(1, LOWER_IdleFrame, true, true);
			}
			else
				m_lower.pAni->setPlayFrame(1, LOWER_IdleFrame, true, true);

			m_fReplaceY = 50;	// ��ü Y ��ǥ ����

			break;

		case LOWER_Move:	// �̵�
			m_lower.pAni->init(LOWER_MoveWidth, LOWER_MoveHeight, LOWER_MoveWidth / LOWER_MoveFrame, LOWER_MoveHeight, LOWER_MoveY);

			if (m_nDir == DIR_Left)
			{
				m_lower.pAni->setPlayFrameReverse(1, LOWER_MoveFrame, false, true);
			}
			else
				m_lower.pAni->setPlayFrame(1, LOWER_MoveFrame, false, true);
			
			m_fReplaceY = 35;	// ��ü Y ��ǥ ����
			
			break;
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
		if (m_nActUpper != UPPER_Sit)
		{
			m_isAct = true;

			m_nActUpper = UPPER_Sit;
			m_nActLower = LOWER_NULL;
		}
	}
	else if (KEYMANAGER->isStayKeyDown('A') && m_upper.pImg->getX() > 0)
	{
		if (m_nActUpper != UPPER_Move && m_nActUpper != UPPER_Att)
		{
			m_isAct = true;
			m_nActUpper = UPPER_Move;
		}

		if (m_nActLower != LOWER_Move)
			m_nActLower = LOWER_Move;

		m_upper.pImg->setX(m_upper.pImg->getX() - m_fSpeed);
		m_lower.pImg->setX(m_lower.pImg->getX() - m_fSpeed);
	}
	else if (KEYMANAGER->isStayKeyDown('D') && m_upper.pImg->getX() < WINSIZEX)
	{
		if (m_nActUpper != UPPER_Move && m_nActUpper != UPPER_Att)
		{
			m_isAct = true;
			m_nActUpper = UPPER_Move;
		}

		if (m_nActLower != LOWER_Move)
			m_nActLower = LOWER_Move;

		m_upper.pImg->setX(m_upper.pImg->getX() + m_fSpeed);
		m_lower.pImg->setX(m_lower.pImg->getX() + m_fSpeed);
	}

	// Ű�� ���� ��� �ൿ���� �������� �ٲ�
	if (KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('D') || KEYMANAGER->isOnceKeyUp('S'))
	{
		m_nActUpper = UPPER_Idle;
		m_nActLower = LOWER_Idle;
		m_isAct = true;
	}

	// ���� (���콺 ������)
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (m_nActUpper != UPPER_Att)
		{
			m_isAct = true;
			m_nActUpper = UPPER_Att;
		}

		float fireAngle = MY_UTIL::getAngle(m_upper.rc.right, m_upper.rc.top / 2, g_ptMouse.x, g_ptMouse.y);

		//if (g_ptMouse.y <= m_upper.pImg->getY())		// ���콺 �����Ͱ� ĳ���� ���ʿ� ���� ��� 
		//	m_nDirY = DIR_Up;

		//else if (g_ptMouse.y > m_upper.pImg->getY())	// ���콺 �����Ͱ� ĳ���� �����ʿ� ���� ���
		//	m_nDirY = DIR_Down;

		m_pMissileMgr->fire(m_upper.pImg->getX() + m_upper.pAni->getFrameWidth() / 2,
			m_upper.pImg->getY() + m_upper.pAni->getFrameHeight() + 30,
			fireAngle, 10, i_player);
	}
	
	// ��ü ��ġ ������Ʈ
	m_upper.rc = RectMake(m_upper.pImg->getX(), m_upper.pImg->getY(),
		m_upper.pAni->getFrameWidth() * 3, m_upper.pAni->getFrameHeight() * 3);

	// ��ü ��ġ ������Ʈ
	if (m_nDir == DIR_Left)
	{
		m_lower.pImg->setY(m_upper.pImg->getY());

		m_lower.rc = RectMake(0, m_lower.pImg->getY() + m_lower.pAni->getFrameHeight() + m_fReplaceY,
			m_lower.pAni->getFrameWidth() * 3, m_lower.pAni->getFrameHeight() * 3);

		m_lower.rc.right = m_upper.rc.right;
		m_lower.rc.left = m_upper.rc.right - m_lower.pAni->getFrameWidth() * 3;
	}
	else
	{
		m_lower.pImg->setY(m_upper.pImg->getY());
		m_lower.rc = RectMake(m_lower.pImg->getX(), m_lower.pImg->getY() + m_lower.pAni->getFrameHeight() + m_fReplaceY,
			m_lower.pAni->getFrameWidth() * 3, m_lower.pAni->getFrameHeight() * 3);
	}
}

void player::release()
{
	SAFE_DELETE(m_upper.pAni);
	SAFE_DELETE(m_lower.pAni);
	SAFE_DELETE(m_pMissileMgr);
}

void player::render(HDC hdc)
{
	char szText[128];

	// �÷��̾�
	//Rectangle(hdc, m_upper.rc.left, m_upper.rc.top, m_upper.rc.right, m_upper.rc.bottom);
	//Rectangle(hdc, m_lower.rc.left, m_lower.rc.top, m_lower.rc.right, m_lower.rc.bottom);

	if (m_nDir == DIR_Left)
	{
		if (m_nActLower != LOWER_NULL)
			m_lower.pImgReverse->aniRender(hdc, m_lower.rc.left, m_lower.rc.top, m_lower.pAni, 3);

		m_upper.pImgReverse->aniRender(hdc, m_upper.rc.left, m_upper.rc.top, m_upper.pAni, 3);
	}
	else if (m_nDir == DIR_Right)
	{
		if (m_nActLower != LOWER_NULL)
			m_lower.pImg->aniRender(hdc, m_lower.rc.left, m_lower.rc.top, m_lower.pAni, 3);

		m_upper.pImg->aniRender(hdc, m_upper.rc.left, m_upper.rc.top, m_upper.pAni, 3);
	}

	// �̻���
	m_pMissileMgr->render(hdc, i_player);

	// �׽�Ʈ
	sprintf_s(szText, "%d, %d", g_ptMouse.x, g_ptMouse.y);
	TextOut(hdc, g_ptMouse.x, g_ptMouse.y + 30, szText, strlen(szText));
}
player::player()
{
}


player::~player()
{
}
