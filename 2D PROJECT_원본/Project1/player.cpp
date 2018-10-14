#include "stdafx.h"
#include "player.h"
#include "animation.h"
#include "timer.h"
#include "missileManager.h"

#define Jump_Height	100

// #######################################################################
// 13(��)���� �ٰŸ�����(+AttBox�浹) + Ż�� Ż��(�����׿��� ���� �� bool���� ����, bool������ ���� ��� ���)
//			  ����: update() �Լ��� GameOver ������ ���� ���๮ �߰� �ؾ� ��, ���� ��� �߰� �ʿ�
// 14(��)���� ������ �Ծ��� �� ���ӽŰ�
// 15(��)���� ��ź����(�������� ������ ��ź ���� ����=>������ Ŭ�������� �÷��̾�� ���
//		 ��ź�� ������� ��(���� > 0) ��ź ������ ��� + ��ź(�̻���Ŭ����)
//			 
// #######################################################################

HRESULT player::init(float x, float y)
{
	// �����׿� ž�� ���̸� �÷��̾� update ó�� �� �� (������ class���� ó��)
	if (m_isSlugIn == true)	return;

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
	m_upper.pAni->setFrameUpdateSec(0.08f);

	m_lower.pAni->init(1, 1, 1, 1);
	m_lower.pAni->setFPS(FPS);
	m_lower.pAni->setPlayFrame(0, 0);
	m_lower.pAni->stop();
	m_lower.pAni->setFrameUpdateSec(0.08f);

	m_upper.pImg->setX(x);
	m_upper.pImg->setY(y);
	m_lower.pImg->setX(x);
	m_lower.pImg->setY(y);

	m_fSpeed = 3.0f;
	m_fJumpSpeed = 0.3f;
	m_fCurrHeight = 0;
	m_fGravity = 10.0f;
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
	m_isJump = false;
	
	g_ptMouse = { WINSIZEX, WINSIZEY };

	m_upper.rc = RectMake(m_upper.pImg->getX(), m_upper.pImg->getY(), m_upper.pAni->getFrameWidth() * 3, m_upper.pAni->getFrameHeight() * 3);
	m_lower.rc = RectMake(m_lower.pImg->getX(), m_lower.pImg->getY(), m_lower.pAni->getFrameWidth() * 3, m_lower.pAni->getFrameHeight() * 3);
	m_rcHit = RectMake(m_upper.pImg->getX(), m_upper.pImg->getY(), 50, 50);

	ZeroMemory(&m_rcAtt, NULL);

	// �̻���
	IMAGEMANAGER->addImage("playerMissile", "image/player/playerBullet.bmp", 8, 8, true, RGB(255, 0, 255));

	m_pMissileMgr = new missileManager;
	m_pMissileMgr->init("playerMissile", WINSIZEY, 10);
	
	return S_OK;
}

void player::update()
{
	// �����׿� ž�� ���̸� �÷��̾� update ó�� �� �� (������ class���� ó��)
	if (m_isSlugIn == true)	return;

	// �ִϸ��̼�
	m_upper.pAni->frameUpdate(TIMEMANAGER->getTimer()->getElapsedTime());
	m_lower.pAni->frameUpdate(TIMEMANAGER->getTimer()->getElapsedTime());

	// ���� ���� ��� return
	if (m_nActUpper == UPPER_Appear && m_upper.pAni->getIsPlaying() == true)	return;

	// �׾��� ��� ���� ��� ���� ��, �ִϸ��̼��� ������ GameOver ������ ����
	if (m_isAlive == false)
	{
		m_nActUpper = UPPER_Death;
		m_nActLower = LOWER_NULL;

		if (m_upper.pAni->getIsPlaying() == false)
			//SCENEMANAGER->changeScene();

		return;
	}

	// �÷��̾�
	setDir();
	move();
	actSet();

	// �̻���
	m_pMissileMgr->update();
}

void player::actSet()
{
	// ### ��� ���� �� ���� �Լ� ###
	
	// �ݺ���� ����, isPlaying == false�� ���
	if (m_upper.pAni->getIsPlaying() == false)
	{
		if (m_nActUpper == UPPER_Appear)
			m_lower.pImg->setY(WINSIZEY / 2 + 115);

		if (m_nActUpper != UPPER_Sit && m_nActUpper != UPPER_SitMove && 
			m_nActUpper != UPPER_Jump && m_nActUpper != UPPER_JumpMove &&
			m_nActLower != LOWER_Jump && m_nActLower != LOWER_JumpMove)
		{
			m_nActUpper = UPPER_Idle;
			m_nActLower = LOWER_Idle;
			m_isAct = true;
		}
	}

	// Ż�� Ż��

	// ����

	m_fAttX = m_upper.pImg->getX();
	m_fAttY = m_upper.pImg->getY();

	// ### �ִϸ��̼� ���� ###
	if (m_isAct == true)
	{
		setUpper();
		setLower();

		m_isAct = false;
	}
}

void player::setUpper()
{
	// ��ü
	switch (m_nActUpper)
	{
	case UPPER_Idle:	// ���
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

	case UPPER_Sit:		// �ɱ�
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

	case UPPER_Move:	// �̵�
		m_upper.pAni->init(UPPER_MoveWidth, UPPER_MoveHeight, UPPER_MoveWidth / UPPER_MoveFrame, UPPER_MoveHeight, UPPER_MoveY);

		if (m_nDir == DIR_Left)
			m_upper.pAni->setPlayFrameReverse(1, UPPER_MoveFrame, false, true);

		else
			m_upper.pAni->setPlayFrame(1, UPPER_MoveFrame, false, true);

		m_fReplaceY = 25;

		break;

	case UPPER_Jump:
		m_upper.pAni->init(UPPER_JumpWidth, UPPER_JumpHeight, UPPER_JumpWidth / UPPER_JumpFrame, UPPER_JumpHeight, UPPER_JumpY);

		if (m_nDir == DIR_Left)
			m_upper.pAni->setPlayFrameReverse(1, UPPER_JumpFrame, true, false);

		else
			m_upper.pAni->setPlayFrame(1, UPPER_JumpFrame, true, false);

		m_fReplaceY = 45;

		break;
	
	case UPPER_JumpMove:
		m_upper.pAni->init(UPPER_JumpMoveWidth, UPPER_JumpMoveHeight, UPPER_JumpMoveWidth / UPPER_JumpMoveFrame, UPPER_JumpMoveHeight, UPPER_JumpMoveY);

		if (m_nDir == DIR_Left)
			m_upper.pAni->setPlayFrameReverse(1, UPPER_JumpMoveFrame, true, false);

		else
			m_upper.pAni->setPlayFrame(1, UPPER_JumpMoveFrame, true, false);

		m_fReplaceY = 45;

		break;

	case UPPER_Death:
		m_upper.pAni->init(UPPER_DeathWidth, UPPER_DeathHeight, UPPER_DeathWidth / UPPER_DeathFrame, UPPER_DeathHeight, UPPER_DeathY);

		m_upper.pAni->setPlayFrame(1, UPPER__DeathFrame, false , false);

		m_fReplaceY = 0;
		break;

	case UPPER_Att:		// ������ fire() �Լ�����
		break;
	}

	m_upper.pAni->start();
}

void player::setLower()
{
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

		break;

	case LOWER_Move:	// �̵�
		m_lower.pAni->init(LOWER_MoveWidth, LOWER_MoveHeight, LOWER_MoveWidth / LOWER_MoveFrame, LOWER_MoveHeight, LOWER_MoveY);

		if (m_nDir == DIR_Left)
		{
			m_lower.pAni->setPlayFrameReverse(1, LOWER_MoveFrame, false, true);
		}
		else
			m_lower.pAni->setPlayFrame(1, LOWER_MoveFrame, false, true);

		m_fReplaceLowerY = -20;

		break;
		
	case LOWER_Jump:	// ����
		m_lower.pAni->init(LOWER_JumpWidth, LOWER_JumpHeight, LOWER_JumpWidth / LOWER_JumpFrame, LOWER_JumpHeight, LOWER_JumpY);

		if (m_nDir == DIR_Left)
		{
			m_lower.pAni->setPlayFrameReverse(1, LOWER_JumpFrame, true, false);
		}
		else
			m_lower.pAni->setPlayFrame(1, LOWER_JumpFrame, true, false);

		m_fReplaceLowerY = -50;

		break;

	case LOWER_JumpMove:	// ���� �̵�
		m_lower.pAni->init(LOWER_JumpMoveWidth, LOWER_JumpMoveHeight, LOWER_JumpMoveWidth / LOWER_JumpMoveFrame, LOWER_JumpMoveHeight, LOWER_JumpMoveY);

		if (m_nDir == DIR_Left)
		{
			m_lower.pAni->setPlayFrameReverse(1, LOWER_JumpMoveFrame, true, false);
		}
		else
			m_lower.pAni->setPlayFrame(1, LOWER_JumpMoveFrame, true, false);

		m_fReplaceLowerY = -50;

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

	// ### ĳ���� ���� ���� ###
	else if (g_ptMouse.x <= m_upper.pImg->getX())		// ���콺 �����Ͱ� ĳ���� ���ʿ� ���� ��� 
	{
		if (m_nActUpper == UPPER_Sit)
			m_upper.pAni->setPlayFrameReverse(0, UPPER_SitFrame, false, false);

		m_nDir = DIR_Left;
		m_nDirY = NULL;
	}

	else if (g_ptMouse.x > m_upper.pImg->getX())	// ���콺 �����Ͱ� ĳ���� �����ʿ� ���� ���
	{
		if (m_nActUpper == UPPER_Sit)
			m_upper.pAni->setPlayFrame(0, UPPER_SitFrame, false, false);

		m_nDir = DIR_Right;
		m_nDirY = NULL;
	}

	if (g_ptMouse.y <= m_upper.pImg->getY() && m_fAngle > 0.7f && m_fAngle < 2.4f)		// ���콺 �����Ͱ� ĳ���� ���� ���� ���
	{
		m_nDirY = DIR_Up;
	}

	else if (g_ptMouse.y > m_upper.pImg->getY() && m_fAngle > 4.2f && m_fAngle < 5.5f)	// ���콺 �����Ͱ� ĳ���� �Ʒ��� ���� ���
	{
		m_nDirY = DIR_Down;
	}
}

void player::setResourceRect()
{
	// ### ���ҽ� ��ǥ ���� ###
	// ���ҽ� ������� ��ġ�� �������� �ʱ� ������ ���� �ʿ�
	if (m_nActUpper != UPPER_Appear)
	{
		// ���ҽ� ��ǥ ����: �ٸ��� �߽�����, ��ü�� �ø���. (��ü�� ������� ������ ��ġ�� ���ϹǷ�)
		// ��, ��ü ��ġ ������Ʈ
		m_lower.rc = RectMake(m_lower.pImg->getX(), m_lower.pImg->getY() + m_lower.pAni->getFrameHeight() + m_fReplaceLowerY,
			m_lower.pAni->getFrameWidth() * 3, m_lower.pAni->getFrameHeight() * 3);

		if (m_nDir == DIR_Left)
		{
			// ĳ���Ͱ� ������ ���� ������ ��ü�� �����ʿ� ��ü�� �������� ����� ��
			m_upper.rc.right = m_lower.rc.right;
			m_upper.rc.left = m_upper.rc.right - m_upper.pAni->getFrameWidth() * 3;
		}
		else
		{
			// ĳ���Ͱ� �������� ���� ������ ��ü�� ���ʿ� ��ü�� ������ ����� ��
			m_upper.rc.left = m_lower.rc.left;
			m_upper.rc.right = m_upper.rc.left + m_upper.pAni->getFrameWidth() * 3;
		}

		m_upper.rc.bottom = m_lower.rc.top + m_fReplaceY;
		m_upper.rc.top = m_upper.rc.bottom - m_upper.pAni->getFrameHeight() * 3;
	}
}

void player::fire()
{
	int attReplaceX = 0;	// ���ùڽ� X, Y ��ǥ ����
	int attReplaceY = 0;

	// ��Ǻ���
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

	// ���ùڽ�
	m_fAttX = m_upper.pImg->getX() + attReplaceX;
	m_fAttY = m_upper.pImg->getY() + attReplaceY;

	m_fAngle = MY_UTIL::getAngle(m_fAttX,	// �Ѿ� �߻縦 ���� ���� ����
		m_fAttY,
		g_ptMouse.x, g_ptMouse.y);

	m_pMissileMgr->fire(m_fAttX,			// �Ѿ� �߻�
		m_fAttY,
		m_fAngle, 10, i_player);

	// ���� �� ������ ������ �ʱ�ȭ (���Ӱ��� ���)
	m_upper.pAni->start();
}

void player::move()
{
	// (�÷��̾� <- �� �Ѿ�) �浹 RECT UPDATE
	m_rcHit.bottom = m_lower.rc.bottom;
	m_rcHit.left = m_upper.pImg->getX();
	m_rcHit.right = m_rcHit.left + PLAYER_RectWidth;

	if (m_nActUpper == UPPER_Sit || m_nActUpper == UPPER_SitMove)
		m_rcHit.top = m_rcHit.bottom - PLAYER_RectHeight + 30;
	else
		m_rcHit.top = m_rcHit.bottom - PLAYER_RectHeight;

	// Ű �Է� ó��
	// �ɱ�
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		if (m_nActUpper != UPPER_Sit && m_nActUpper != UPPER_SitMove && 
			m_nActLower != LOWER_Jump && m_nActLower != LOWER_JumpMove)
		{
			m_isAct = true;

			m_nActUpper = UPPER_Sit;
			m_nActLower = LOWER_NULL;
		}
	}
	
	// ����
	else if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && m_nActLower != LOWER_Jump)
	{	
		m_isAct = true;
		m_isJump = true;

		m_fCurrHeight = m_lower.pImg->getY();

		// �̵��ϴ� ���� jump�� ��� jumpMove������� ����  
		if (m_nActLower != LOWER_Jump && m_nActLower != LOWER_JumpMove &&
			m_nActLower == LOWER_Move)
		{
			m_nActUpper = UPPER_JumpMove;
			m_nActLower = LOWER_JumpMove;

			return;
		}

		// ���ڸ� jump ���
		m_nActUpper = UPPER_Jump;
		m_nActLower = LOWER_Jump;
	}
	
	if ((m_nActLower == LOWER_Jump || m_nActLower == LOWER_JumpMove) && m_isJump == true)
	{
		if (m_fGravity > 0)
		{
			m_fGravity -= m_fJumpSpeed; 
			m_lower.pImg->setY(m_lower.pImg->getY() - m_fGravity);
		}
		else 
		{
			m_isJump = false;
			m_fGravity = 0;
		}
	}
	
	if ((m_nActLower == LOWER_Jump || m_nActLower == LOWER_JumpMove) && m_isJump == false)
	{
		if (m_fGravity <= 10.0f)
		{
			m_fGravity += m_fJumpSpeed;
			m_lower.pImg->setY(m_lower.pImg->getY() + m_fGravity);
		}
		else if (m_lower.pImg->getY() >= m_fCurrHeight)	// ���� ����� ���̿� ���� ���̰� ���� ��� (���� ����� ���)
		{
			m_lower.pImg->setY(m_fCurrHeight);
			m_fCurrHeight = 0;
			m_isJump = false;
			m_nActUpper = UPPER_Idle;
			m_nActLower = LOWER_Idle;
			m_fGravity = 10;
		}
	}

	// �̵�
	if (KEYMANAGER->isStayKeyDown('A') && m_upper.pImg->getX() > 0)			// ���� �̵�
	{																		//	
		if (m_nActUpper != UPPER_Move && m_nActUpper != UPPER_Att &&		// �ȱ�, ����		 �ƴ� ��
			m_nActUpper != UPPER_Sit && m_nActUpper != UPPER_SitMove &&		// �ɱ�, �ɾưȱ�	 �ƴ� ��
			m_nActLower != LOWER_Jump && m_nActLower != LOWER_JumpMove)		// ����, �����ȱ�	 �ƴ� ��
		{																	//
			m_isAct = true;													//
			m_nActUpper = UPPER_Move;										// �ȱ� ������� �����Ѵ�.
		}
		else if (m_nActUpper == UPPER_Sit && m_nActUpper != UPPER_SitMove)
		{
			m_isAct = true;
			m_nActUpper = UPPER_SitMove;
			m_nActLower = LOWER_NULL;
			m_fSpeed = 1.0f;
		}
		else if (m_nActLower == LOWER_Jump || m_nActLower == LOWER_JumpMove)	// ���� ���߿� �̵��� ���
		{
			m_nActUpper = UPPER_JumpMove;
			m_nActLower = LOWER_JumpMove;
		}

		if (m_nActLower != LOWER_Move && m_nActLower != LOWER_NULL && 
			m_nActLower != LOWER_Jump && m_nActLower != LOWER_JumpMove)
			m_nActLower = LOWER_Move;

		m_upper.pImg->setX(m_upper.pImg->getX() - m_fSpeed);
		m_lower.pImg->setX(m_lower.pImg->getX() - m_fSpeed);
	}
	else if (KEYMANAGER->isStayKeyDown('D') && m_upper.pImg->getX() < WINSIZEX)	// ������ �̵�
	{																			//
		if (m_nActUpper != UPPER_Move && m_nActUpper != UPPER_Att &&			// �ȱ�, ����		 �ƴ� ��
			m_nActUpper != UPPER_Sit && m_nActUpper != UPPER_SitMove &&			// �ɱ�, �ɾưȱ�	 �ƴ� ��
			m_nActLower != LOWER_Jump && m_nActLower != LOWER_JumpMove)			// ����, �����ȱ�	 �ƴ� ��
		{																		//
			m_isAct = true;														//
			m_nActUpper = UPPER_Move;											// �ȱ� ������� �����Ѵ�.
		}
		else if (m_nActUpper == UPPER_Sit && m_nActUpper != UPPER_SitMove)		// �ɾ� �����鼭 �ɾưȱ� ����� �ƴ� ��
		{																		// �ɾưȱ� ������� ����
			m_isAct = true;
			m_nActUpper = UPPER_SitMove;
			m_nActLower = LOWER_NULL;
			m_fSpeed = 1.0f;
		}
		else if (m_nActLower == LOWER_Jump || m_nActLower == LOWER_JumpMove)	// ���� ���߿� �̵��� ���
		{
			m_nActUpper = UPPER_JumpMove;
			m_nActLower = LOWER_JumpMove;
		}

		if (m_nActLower != LOWER_Move && m_nActLower != LOWER_NULL && 
			m_nActLower != LOWER_Jump && m_nActLower != LOWER_JumpMove)
			m_nActLower = LOWER_Move;

		m_upper.pImg->setX(m_upper.pImg->getX() + m_fSpeed);
		m_lower.pImg->setX(m_lower.pImg->getX() + m_fSpeed);
	}

	// ���� (���콺 ������)
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && m_nActUpper != UPPER_Sit && m_nActUpper != UPPER_SitMove)
	{
		if (m_nActUpper != UPPER_Att)
		{
			m_nActUpper = UPPER_Att;
			m_isAct = true;
		}

		fire();	// ����
	}
	
	// Ű�� ���� ��� �ൿ���� �������� �ٲ�
	if (KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('D'))
	{
		if (m_nActUpper == UPPER_SitMove || m_nActUpper == UPPER_Sit)
		{
			m_nActUpper = UPPER_Sit;
			m_nActLower = LOWER_NULL;
			m_isAct = true; 

			return;
		}

		else if (m_nActUpper != UPPER_Att)
			m_nActUpper = UPPER_Idle;

		if (m_nActLower != LOWER_Jump && m_nActLower != LOWER_JumpMove)
		{
			m_nActLower = LOWER_Idle;
			m_isAct = true;
		}
	}

	// �ɾ��� �� �ٽ� �Ͼ
	if (KEYMANAGER->isOnceKeyUp('S') && (m_nActUpper == UPPER_Sit || m_nActUpper == UPPER_SitMove))
	{
		m_nActUpper = UPPER_Idle;
		m_nActLower = LOWER_Idle;
		m_fSpeed = 3.0f;
		m_isAct = true;
	}

	// ����
	if (m_isAlive == false)
	{
		//m_nActUpper = UPPER_Dead;
		m_nActLower = NULL;
	}

	// ### ���ҽ� ��ǥ ���� ###
	setResourceRect();
}

void player::release()
{
	SAFE_DELETE(m_upper.pAni);
	SAFE_DELETE(m_lower.pAni);
	SAFE_DELETE(m_pMissileMgr);
}

void player::render(HDC hdc)
{
	// �����׿� ž�� ���̸� �÷��̾� render ó�� �� �� (������ class���� ó��)
	if (m_isSlugIn == true)	return;

	char szText[128];

	// �÷��̾�
	Rectangle(hdc, m_upper.rc.left, m_upper.rc.top, m_upper.rc.right, m_upper.rc.bottom);
	Rectangle(hdc, m_lower.rc.left, m_lower.rc.top, m_lower.rc.right, m_lower.rc.bottom);
	/*Rectangle(hdc, m_rcHit.left, m_rcHit.top, m_rcHit.right, m_rcHit.bottom);*/

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

	//// �׽�Ʈ
	//sprintf_s(szText, "%d, %d", g_ptMouse.x, g_ptMouse.y);
	//TextOut(hdc, g_ptMouse.x, g_ptMouse.y + 30, szText, strlen(szText));

	//_stprintf_s(szText, "Missile Angle: %f", m_fAngle);
	//TextOut(hdc, 100, 100, szText, strlen(szText));

	_stprintf_s(szText, "m_fCurrHeight: %f", m_fCurrHeight);
	TextOut(hdc, 100, 150, szText, strlen(szText));

	//Rectangle(hdc, m_fAttX, m_fAttY, m_fAttX + 10, m_fAttY + 10);
}

void player::dataSave()
{
}


player::player()
{
}


player::~player()
{
}
