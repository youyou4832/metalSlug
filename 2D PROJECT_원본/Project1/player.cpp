#include "stdafx.h"
#include "player.h"
#include "animation.h"
#include "timer.h"
#include "missileManager.h"

#define Jump_Height	100

// #######################################################################
// 12(금)까지 앉아서이동+앉아서공격+점프+폭탄공격+근거리공격+탈것탈출+죽음 구현
// #######################################################################

HRESULT player::init(float x, float y)
{
	// 플레이어
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
	m_lower.pAni->setPlayFrame(0, 0);
	m_lower.pAni->stop();
	m_lower.pAni->setFrameUpdateSec(0.1f);

	m_upper.pImg->setX(x);
	m_upper.pImg->setY(y);
	m_lower.pImg->setX(x);
	m_lower.pImg->setY(y);

	m_fSpeed = 3.0f;
	m_fJumpSpeed = 10.0f;
	m_fJumpHeight = 100;
	m_fCurrHeight = 0;
	m_fGravity = 0;
	m_fReplaceY = 0;
	m_fAngle = 0;
	m_fAttX = 50;
	m_fAttY = 50;
	m_nActUpper = UPPER_Appear;
	m_nActLower = LOWER_NULL;
	m_nDir = DIR_Right;
	m_nDirY = DIR_Right;
	m_isAct = false;
	m_isAlive = true;

	g_ptMouse = { WINSIZEX, WINSIZEY };

	m_upper.rc = RectMake(m_upper.pImg->getX(), m_upper.pImg->getY(), m_upper.pAni->getFrameWidth() * 3, m_upper.pAni->getFrameHeight() * 3);
	m_lower.rc = RectMake(m_lower.pImg->getX(), m_lower.pImg->getY(), m_lower.pAni->getFrameWidth() * 3, m_lower.pAni->getFrameHeight() * 3);
	ZeroMemory(&m_rcAtt, NULL);

	// 미사일
	IMAGEMANAGER->addImage("playerMissile", "image/player/playerBullet.bmp", 8, 8, true, RGB(255, 0, 255));

	m_pMissileMgr = new missileManager;
	m_pMissileMgr->init("playerMissile", WINSIZEY, 10);
	
	return S_OK;
}

void player::update()
{
	// 플레이어
	setDir();
	move();
	actSet();

	m_upper.pAni->frameUpdate(TIMEMANAGER->getTimer()->getElapsedTime());
	m_lower.pAni->frameUpdate(TIMEMANAGER->getTimer()->getElapsedTime());

	// 미사일
	m_pMissileMgr->update();
}

void player::actSet()
{
	/* ### 애니메이션 프레임 지정 ###
	등장 중일 경우 return */
	if (m_nActUpper == UPPER_Appear && m_upper.pAni->getIsPlaying() == true)	return;

	// 반복모션 제외, isPlaying == false일 경우
	else if (m_upper.pAni->getIsPlaying() == false/* && m_lower.pAni->getIsPlaying() == false*/)
	{
		if (m_nActUpper == UPPER_Appear)
			m_lower.pImg->setY(WINSIZEY / 2 + 115);

		if (m_nActUpper != UPPER_Sit && m_nActUpper != UPPER_SitMove)
		{
			m_nActUpper = UPPER_Idle;
			m_nActLower = LOWER_Idle;
			m_isAct = true;
		}
	}

	m_fAttX = m_upper.pImg->getX();
	m_fAttY = m_upper.pImg->getY();

	// ### 애니메이션 설정 ###
	if (m_isAct == true)
	{
		setUpper();
		setLower();

		m_isAct = false;
	}
}

void player::setUpper()
{
	// 상체
	switch (m_nActUpper)
	{
	case UPPER_Idle:	// 대기
		m_upper.pAni->init(UPPER_IdleWidth, UPPER_IdleHeight, UPPER_IdleWidth / UPPER_IdleFrame, UPPER_IdleHeight, UPPER_IdleY);

		if (m_isAct == true)
		{
			if (m_nDir == DIR_Left)
			{
				m_upper.pAni->setPlayFrameReverse(1, UPPER_IdleFrame, true, true);
			}
			else
				m_upper.pAni->setPlayFrame(1, UPPER_IdleFrame, true, true);

			m_fReplaceY = 25;
		}
		
		break;

	case UPPER_Sit:		// 앉기
		m_upper.pAni->init(UPPER_SitWidth, UPPER_SitHeight, UPPER_SitWidth / UPPER_SitFrame, UPPER_SitHeight, UPPER_SitY);

		if (m_nDir == DIR_Left)
			m_upper.pAni->setPlayFrameReverse(0, UPPER_SitFrame, false, false);

		else
			m_upper.pAni->setPlayFrame(1, UPPER_SitFrame, false, false);

		m_fReplaceY = 45;
		break;

	case UPPER_SitMove:
		m_upper.pAni->init(UPPER_SitMoveWidth, UPPER_SitMoveHeight, UPPER_SitMoveWidth / UPPER_SitMoveFrame, UPPER_SitMoveHeight, UPPER_SitMoveY);

		if (m_nDir == DIR_Left)
			m_upper.pAni->setPlayFrameReverse(1, UPPER_SitMove, false, true);
		else
			m_upper.pAni->setPlayFrame(1, UPPER_SitMoveFrame, false, true);
		
		m_fReplaceY = 45;
		break;

	case UPPER_Move:	// 이동
		m_upper.pAni->init(UPPER_MoveWidth, UPPER_MoveHeight, UPPER_MoveWidth / UPPER_MoveFrame, UPPER_MoveHeight, UPPER_MoveY);

		if (m_nDir == DIR_Left)
			m_upper.pAni->setPlayFrameReverse(1, UPPER_MoveFrame, false, true);

		else
			m_upper.pAni->setPlayFrame(1, UPPER_MoveFrame, false, true);

		m_fReplaceY = 25;
		break;

	case UPPER_Att:		// 공격은 fire() 함수에서
		break;

	case UPPER_AttSit:	// 앉아서 공격
		if (m_nDir == DIR_Left)
		{
			m_upper.pAni->init(UPPER_AttSitWidth, UPPER_AttSitHeight, UPPER_AttSitWidth / UPPER_AttSitFrame, UPPER_AttSitHeight, UPPER_AttSitY);
			m_upper.pAni->setPlayFrameReverse(1, UPPER_AttSitFrame, false, false);
		}

		else
		{
			m_upper.pAni->init(UPPER_AttSitWidth, UPPER_AttSitHeight, UPPER_AttSitWidth / UPPER_AttSitFrame, UPPER_AttSitHeight, UPPER_AttSitY);
			m_upper.pAni->setPlayFrame(1, UPPER_AttSitFrame, false, false);
		}

		m_nActLower = NULL;

		break;
	}

	m_upper.pAni->start();
}

void player::setLower()
{
	// 하체
	switch (m_nActLower)
	{
	case LOWER_NULL:
		m_lower.pAni->setPlayFrame(0, 0);
		break;

	case LOWER_Idle:	// 대기
		m_lower.pAni->init(LOWER_IdleWidth, LOWER_IdleHeight, LOWER_IdleWidth / LOWER_IdleFrame, LOWER_IdleHeight, LOWER_IdleY);

		if (m_nDir == DIR_Left)
		{
			m_lower.pAni->setPlayFrameReverse(1, LOWER_IdleFrame, true, true);
		}
		else
			m_lower.pAni->setPlayFrame(1, LOWER_IdleFrame, true, true);

		break;

	case LOWER_Move:	// 이동
		m_lower.pAni->init(LOWER_MoveWidth, LOWER_MoveHeight, LOWER_MoveWidth / LOWER_MoveFrame, LOWER_MoveHeight, LOWER_MoveY);

		if (m_nDir == DIR_Left)
		{
			m_lower.pAni->setPlayFrameReverse(1, LOWER_MoveFrame, false, true);
		}
		else
			m_lower.pAni->setPlayFrame(1, LOWER_MoveFrame, false, true);

		m_fReplaceLowerY = -20;

		break;
	}

	if (m_nActLower != LOWER_Move)
		m_fReplaceLowerY = 0;

	m_lower.pAni->start();
}

void player::setDir()
{
	if (m_nActUpper == UPPER_Appear)
	{
		m_nDir = DIR_Right;
		return;
	}

	// ### 캐릭터 방향 설정 ###
	else if (g_ptMouse.x <= m_upper.pImg->getX())		// 마우스 포인터가 캐릭터 왼쪽에 있을 경우 
	{
		if (m_nActUpper == UPPER_Sit)
			m_upper.pAni->setPlayFrameReverse(0, UPPER_SitFrame, false, false);

		m_nDir = DIR_Left;
		m_nDirY = NULL;
	}

	else if (g_ptMouse.x > m_upper.pImg->getX())	// 마우스 포인터가 캐릭터 오른쪽에 있을 경우
	{
		if (m_nActUpper == UPPER_Sit)
			m_upper.pAni->setPlayFrame(0, UPPER_SitFrame, false, false);

		m_nDir = DIR_Right;
		m_nDirY = NULL;
	}

	if (g_ptMouse.y <= m_upper.pImg->getY() && m_fAngle > 0.7f && m_fAngle < 2.4f)		// 마우스 포인터가 캐릭터 위에 있을 경우
	{
		m_nDirY = DIR_Up;
	}

	else if (g_ptMouse.y > m_upper.pImg->getY() && m_fAngle > 4.2f && m_fAngle < 5.5f)	// 마우스 포인터가 캐릭터 아래에 있을 경우
	{
		m_nDirY = DIR_Down;
	}
}

void player::fire()
{
	int attReplaceX = 0;	// 어택박스 X, Y 좌표 수정
	int attReplaceY = 0;

	if (m_nDir == DIR_Left)
	{
		if (m_nDirY == DIR_Up)
		{
			m_upper.pAni->init(UPPER_Att90Width, UPPER_Att90Height, UPPER_Att90Width / UPPER_Att90Frame, UPPER_Att90Height, UPPER_Att90Y);
			m_upper.pAni->setPlayFrameReverse(1, UPPER_Att90Frame, false, false);

			attReplaceX = 30;
			attReplaceY = -90;
			m_fReplaceY = 10;
		}

		else if (m_nDirY == DIR_Down)
		{
			m_upper.pAni->init(UPPER_Att270Width, UPPER_Att270Height, UPPER_Att270Width / UPPER_Att270Frame, UPPER_Att270Height, UPPER_Att270Y);
			m_upper.pAni->setPlayFrameReverse(1, UPPER_Att270Frame, false, false);

			attReplaceX = 0;
			attReplaceY = 40;
			m_fReplaceY = 110;
		}

		else
		{
			m_upper.pAni->init(UPPER_AttWidth, UPPER_AttHeight, UPPER_AttWidth / UPPER_AttFrame, UPPER_AttHeight, UPPER_AttY);
			m_upper.pAni->setPlayFrameReverse(1, UPPER_AttFrame, false, false);

			attReplaceX = -50;
			attReplaceY = -20;
			m_fReplaceY = 20;
		}
	}

	else
	{
		if (m_nDirY == DIR_Up)
		{
			m_upper.pAni->init(UPPER_Att90Width, UPPER_Att90Height, UPPER_Att90Width / UPPER_Att90Frame, UPPER_Att90Height, UPPER_Att90Y);
			m_upper.pAni->setPlayFrame(1, UPPER_Att90Frame, false, false);

			attReplaceX = 30;
			attReplaceY = -90;
			m_fReplaceY = 10;
		}

		else if (m_nDirY == DIR_Down)
		{
			m_upper.pAni->init(UPPER_Att270Width, UPPER_Att270Height, UPPER_Att270Width / UPPER_Att270Frame, UPPER_Att270Height, UPPER_Att270Y);
			m_upper.pAni->setPlayFrame(1, UPPER_Att270Frame, false, false);

			attReplaceX = 40;
			attReplaceY = 50;
			m_fReplaceY = 110;
		}

		else
		{
			m_upper.pAni->init(UPPER_AttWidth, UPPER_AttHeight, UPPER_AttWidth / UPPER_AttFrame, UPPER_AttHeight, UPPER_AttY);
			m_upper.pAni->setPlayFrame(1, UPPER_AttFrame, false, false);

			attReplaceX = 100;
			attReplaceY = -20;
			m_fReplaceY = 20;
		}
	}

	m_fAttX = m_upper.pImg->getX() + attReplaceX;
	m_fAttY = m_upper.pImg->getY() + attReplaceY;

	m_fAngle = MY_UTIL::getAngle(m_fAttX,	// 총알 발사를 위한 각도 지정
		m_fAttY,
		g_ptMouse.x, g_ptMouse.y);

	m_pMissileMgr->fire(m_fAttX,			// 총알 발사
		m_fAttY,
		m_fAngle, 10, i_player);
}

void player::move()
{
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		if (m_nActUpper != UPPER_Sit && m_nActUpper != UPPER_SitMove)
		{
			m_isAct = true;

			m_nActUpper = UPPER_Sit;
			m_nActLower = LOWER_NULL;
		}
	}

	if (KEYMANAGER->isStayKeyDown('A') && m_upper.pImg->getX() > 0)
	{
		if (m_nActUpper != UPPER_Move && m_nActUpper != UPPER_Att && m_nActUpper != UPPER_Sit && m_nActUpper != UPPER_SitMove)
		{
			m_isAct = true;
			m_nActUpper = UPPER_Move;

			if (m_nActLower != LOWER_Move && m_nActLower != LOWER_NULL)
				m_nActLower = LOWER_Move;
		}
		else if (m_nActUpper == UPPER_Sit && m_nActUpper != UPPER_SitMove)
		{
			m_isAct = true;
			m_nActUpper = UPPER_SitMove;
			m_nActLower = LOWER_NULL;
			m_fSpeed = 1.0f;
		}

		m_upper.pImg->setX(m_upper.pImg->getX() - m_fSpeed);
		m_lower.pImg->setX(m_lower.pImg->getX() - m_fSpeed);
	}
	else if (KEYMANAGER->isStayKeyDown('D') && m_upper.pImg->getX() < WINSIZEX)
	{
		if (m_nActUpper != UPPER_Move && m_nActUpper != UPPER_Att && m_nActUpper != UPPER_Sit && m_nActUpper != UPPER_SitMove)
		{
			m_isAct = true;
			m_nActUpper = UPPER_Move;

			if (m_nActLower != LOWER_Move && m_nActLower != LOWER_NULL)
				m_nActLower = LOWER_Move;
		}
		else if (m_nActUpper == UPPER_Sit && m_nActUpper != UPPER_SitMove)
		{
			m_isAct = true;
			m_nActUpper = UPPER_SitMove;
			m_nActLower = LOWER_NULL;
			m_fSpeed = 1.0f;
		}

		m_upper.pImg->setX(m_upper.pImg->getX() + m_fSpeed);
		m_lower.pImg->setX(m_lower.pImg->getX() + m_fSpeed);
	}

	// 공격 (마우스 포인터)
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		m_isAct = true;

		if (m_nActUpper == UPPER_Sit || m_nActUpper == UPPER_AttSit)
			m_nActUpper = UPPER_AttSit;

		else if (m_nActUpper != UPPER_Sit && m_nActUpper != UPPER_AttSit)
		{
			if (m_nActUpper != UPPER_Att)
				m_nActUpper = UPPER_Att;

			fire();	// 공격
		}
	}

	// 키를 뗐을 경우 행동하지 않음으로 바꿈
	if (KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('D'))
	{
		if (m_nActUpper == UPPER_SitMove || m_nActUpper == UPPER_Sit)
		{
			m_nActUpper = UPPER_Sit;
			return;
		}

		else if (m_nActUpper != UPPER_Att)
			m_nActUpper = UPPER_Idle;

		m_nActLower = LOWER_Idle;
		m_isAct = true;

		
	}

	if (KEYMANAGER->isOnceKeyUp('S'))
	{
		m_nActUpper = UPPER_Idle;
		m_nActLower = LOWER_Idle;
		m_fSpeed = 3.0f;
		m_isAct = true;
	}

	if (m_nActUpper != UPPER_Appear)
	{
		// 리소스 좌표 세팅: 다리를 중심으로, 상체를 올린다. (상체는 사이즈가 변하므로)
		// 상, 하체 위치 업데이트
		if (m_nDir == DIR_Left)
		{
			m_lower.rc = RectMake(m_lower.pImg->getX(), m_lower.pImg->getY() + m_lower.pAni->getFrameHeight() + m_fReplaceLowerY,
				m_lower.pAni->getFrameWidth() * 3, m_lower.pAni->getFrameHeight() * 3);

			m_upper.rc.right = m_lower.rc.right;
			m_upper.rc.left = m_upper.rc.right - m_upper.pAni->getFrameWidth() * 3;
			m_upper.rc.bottom = m_lower.rc.top + m_fReplaceY;
			m_upper.rc.top = m_upper.rc.bottom - m_upper.pAni->getFrameHeight() * 3;
		}
		else
		{
			m_lower.rc = RectMake(m_lower.pImg->getX(), m_lower.pImg->getY() + m_lower.pAni->getFrameHeight() + m_fReplaceLowerY,
				m_lower.pAni->getFrameWidth() * 3, m_lower.pAni->getFrameHeight() * 3);

			m_upper.rc.left = m_lower.rc.left;
			m_upper.rc.right = m_upper.rc.left + m_upper.pAni->getFrameWidth() * 3;
			m_upper.rc.bottom = m_lower.rc.top + m_fReplaceY;
			m_upper.rc.top = m_upper.rc.bottom - m_upper.pAni->getFrameHeight() * 3;
		}
	}

	if (m_isAlive == false)
	{
		//m_nActUpper = UPPER_Dead;
		m_nActLower = NULL;
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

	// 플레이어
	Rectangle(hdc, m_upper.rc.left, m_upper.rc.top, m_upper.rc.right, m_upper.rc.bottom);
	Rectangle(hdc, m_lower.rc.left, m_lower.rc.top, m_lower.rc.right, m_lower.rc.bottom);

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

	// 미사일
	m_pMissileMgr->render(hdc, i_player);

	// 테스트
	sprintf_s(szText, "%d, %d", g_ptMouse.x, g_ptMouse.y);
	TextOut(hdc, g_ptMouse.x, g_ptMouse.y + 30, szText, strlen(szText));

	_stprintf_s(szText, "Missile Angle: %f", m_fAngle);
	TextOut(hdc, 100, 100, szText, strlen(szText));

	_stprintf_s(szText, "UPPER Act: %d", m_nActUpper);
	TextOut(hdc, 100, 150, szText, strlen(szText));

	Rectangle(hdc, m_fAttX, m_fAttY, m_fAttX + 10, m_fAttY + 10);
}
player::player()
{
}


player::~player()
{
}
