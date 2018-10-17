#include "stdafx.h"
#include "player.h"
#include "animation.h"
#include "timer.h"
#include "missileManager.h"

#define Jump_Speed		0.3f
#define Move_Speed		3.0f
#define Sit_Speed		1.0f

// #######################################################################
// �ٰŸ�����(+AttBox�浹) �ۼ��ؾ� ��
// 
// ������ �Ծ��� �� ���ӽŰ� ������ (��ü reverse ������ ���� ���ҽ� ����
// 15(��)���� dataSave() �Լ� �ۼ��ؾ� �� (�� �̵� �� init ��� dataLoad �̿�)
//			  + ��ź����(�������� ������ ��ź ���� ����=>������ Ŭ�������� �÷��̾�� ���, ��ź�� missileManager���� �߻�)
//		 ��ź�� ������� ��(���� > 0) ��ź ������ ��� + ��ź(�̻���Ŭ����)
// #######################################################################

HRESULT player::init(float x, float y)
{
	// �����׿� ž�� ���̸� �÷��̾� update ó�� �� �� (������ class���� ó��)
	if (m_isSlugIn == true)	return S_OK;

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

	m_fSpeed = Move_Speed;
	m_fJumpSpeed = Jump_Speed;
	m_fCurrHeight = 0;
	m_fFloorHeight = 0;
	m_fGravity = 10.0f;

	m_fReplaceX = 0;
	m_fReplaceY = 0;
	m_fAttReplaceX = 0;
	m_fAttReplaceY = 0;
	m_fAngle = 0;
	m_fAttX = 50;
	m_fAttY = 50;
	m_nBombNum = 0;

	m_nActUpper = UPPER_Appear;
	m_nActLower = LOWER_NULL;
	m_nDir = DIR_Right;
	m_nDirY = DIR_Right;

	m_isAct = false;
	m_isAlive = true;
	m_isJump = false;
	m_isSlugEscape = false;
	m_isSlugIn = false;
	m_isAttack = false;

	g_ptMouse = { WINSIZEX, WINSIZEY };

	m_upper.rc = RectMake(m_upper.pImg->getX(), m_upper.pImg->getY(), m_upper.pAni->getFrameWidth() * 3, m_upper.pAni->getFrameHeight() * 3);
	m_lower.rc = RectMake(m_lower.pImg->getX(), m_lower.pImg->getY(), m_lower.pAni->getFrameWidth() * 3, m_lower.pAni->getFrameHeight() * 3);
	m_rcHit = RectMake(m_upper.pImg->getX(), m_upper.pImg->getY(), 50, 50);

	ZeroMemory(&m_rcAtt, NULL);

	// �̻���
	IMAGEMANAGER->addImage("playerMissile", "image/player/playerBullet.bmp", 8, 8, true, RGB(255, 0, 255));

	m_pMissileMgr = new missileManager;
	m_pMissileMgr->init("playerMissile", WINSIZEY, 10);

	m_bulletSpeed = 10;
	
	return S_OK;
}

void player::update()
{
	// ######### �׽�Ʈ ##########
	if (KEYMANAGER->isOnceKeyDown(VK_DELETE))	// ����
		m_isAlive = false;
	if (KEYMANAGER->isOnceKeyDown(VK_END))		// ������ Ż��
		m_isSlugEscape = true;
	if (KEYMANAGER->isOnceKeyDown(VK_INSERT))	// �� ����
		m_isGun = true;
	if (KEYMANAGER->isOnceKeyDown(VK_HOME))		// �� ����
		m_isGun = false;
	// ######### �׽�Ʈ ##########



	// update �ʹݿ� return �ϴ� ���๮�� �����ϴ� �Լ�
	if (isReturnUpdate() == false)	return;

	// �÷��̾�

	setDir();
	actSet();
	move();

	// �̻���
	m_pMissileMgr->update();
}

void player::actSet()
{
	/*// ### ��� ���� �� ���� �Լ� ###

	// ������(Ż��) Ż�� ���� ��� ��� ����
	if (m_isSlugEscape == true)
	{
		if (m_nActUpper != UPPER_SlugEscape)
		{
			m_fCurrHeight = m_lower.pImg->getY();

			m_nActUpper = UPPER_SlugEscape;
			m_nActLower = LOWER_NULL;
			m_isJump = true;
			m_isAct = true;
		}
		else if (m_upper.pAni->getIsPlaying() == false)
		{
			m_isSlugEscape = false;
			m_isAct = true;
		}
	}

	// isPlaying == false�� ��� Idle ���·� ���� (�ݺ���� ����)
	if (m_nActUpper == UPPER_Att90 || m_nActUpper == UPPER_Att270)
		m_fReplaceY = 100;

	else if (m_upper.pAni->getIsPlaying() == false && 
		m_nActUpper != UPPER_Death && m_nActUpper != UPPER_SlugEscape &&
		m_nActUpper != UPPER_Appear)
	{
		if (m_nActUpper != UPPER_Sit && m_nActUpper != UPPER_SitMove &&
			m_nActUpper != UPPER_Jump && m_nActUpper != UPPER_JumpMove &&
			m_nActLower != LOWER_Jump && m_nActLower != LOWER_JumpMove &&
			m_nActUpper != UPPER_GunSit && m_nActUpper != UPPER_GunSitMove)
		{
			if (m_isAttack == true)
				m_isAttack = false;

			if (m_isGun == true)
				m_nActUpper = UPPER_GunIdle;

			else
				m_nActUpper = UPPER_Idle;

			m_nActLower = LOWER_Idle;
			m_isAct = true;
		}
	}

	// ������ ���� �ƴϸ� AttBox�� �÷��̾� ��ġ�� ����ٴ�
	if (m_isAttack == false)
	{
		m_fAttX = m_upper.pImg->getX();
		m_fAttY = m_upper.pImg->getY();
		m_rcAtt = RectMake(m_fAttX, m_fAttY, 20, 20);
	}

	// ### �ִϸ��̼� ���� ###
	if (m_isAct == true)
	{
		setUpper();
		setLower();

		m_isAct = false;
	}
	
	// �ִϸ��̼� ������ ������Ʈ
	m_upper.pAni->frameUpdate(TIMEMANAGER->getTimer()->getElapsedTime());
	m_lower.pAni->frameUpdate(TIMEMANAGER->getTimer()->getElapsedTime());*/

	
	// ### ��� ���� �� ���� �Լ� ###

	// �ִϸ��̼� ������ ������Ʈ
	m_upper.pAni->frameUpdate(TIMEMANAGER->getTimer()->getElapsedTime());
	m_lower.pAni->frameUpdate(TIMEMANAGER->getTimer()->getElapsedTime());

	// ������(Ż��) Ż�� ���� ��� ��� ����
	if (m_isSlugEscape == true)
	{
		if (m_nActUpper != UPPER_SlugEscape)
		{
			m_fCurrHeight = m_lower.pImg->getY();

			m_nActUpper = UPPER_SlugEscape;
			m_nActLower = LOWER_NULL;
			m_isJump = true;
			m_isAct = true;
		}
		else if (m_upper.pAni->getIsPlaying() == false)
		{
			m_isSlugEscape = false;
			m_isAct = true;
		}
	}

	// isPlaying == false�� ��� Idle ���·� ���� (�ݺ���� ����)
	else if (m_upper.pAni->getIsPlaying() == false &&
		m_nActUpper != UPPER_Death && m_nActUpper != UPPER_SlugEscape &&
		m_nActUpper != UPPER_Appear)
	{
		if (m_nActUpper != UPPER_Sit && m_nActUpper != UPPER_SitMove &&
			m_nActUpper != UPPER_Jump && m_nActUpper != UPPER_JumpMove &&
			m_nActLower != LOWER_Jump && m_nActLower != LOWER_JumpMove &&
			m_nActUpper != UPPER_GunSit && m_nActUpper != UPPER_GunSitMove)
		{
			if (m_isAttack == true)
				m_isAttack = false;

			if (m_isGun == true)
				m_nActUpper = UPPER_GunIdle;

			else
				m_nActUpper = UPPER_Idle;

			m_nActLower = LOWER_Idle;
			m_isAct = true;
		}
	}

	// ������ ���� �ƴϸ� AttBox�� �÷��̾� ��ġ�� ����ٴ�
	if (m_isAttack == false)
	{
		m_fAttX = m_upper.pImg->getX();
		m_fAttY = m_upper.pImg->getY();
		m_rcAtt = RectMake(m_fAttX, m_fAttY, 20, 20);
	}

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
		// ### ������ ���� �ʾ��� �� ��� ###

	case UPPER_Idle:		// ���
		m_upper.pAni->init(UPPER_IdleWidth, UPPER_IdleHeight, UPPER_IdleWidth / UPPER_IdleFrame, UPPER_IdleHeight, UPPER_IdleY);

		if (m_nDir == DIR_Left)
			m_upper.pAni->setPlayFrameReverse(1, UPPER_IdleFrame, true, true);

		else
			m_upper.pAni->setPlayFrame(1, UPPER_IdleFrame, true, true);

		if (m_nActUpper != UPPER_Att90 && m_nActUpper != UPPER_Att270)
			m_fReplaceY = 25;

		break;

	case UPPER_Sit:			// �ɱ�
		m_upper.pAni->init(UPPER_SitWidth, UPPER_SitHeight, UPPER_SitWidth / UPPER_SitFrame, UPPER_SitHeight, UPPER_SitY);

		if (m_nDir == DIR_Left)
			m_upper.pAni->setPlayFrameReverse(1, UPPER_SitFrame, false, false);

		else
			m_upper.pAni->setPlayFrame(1, UPPER_SitFrame, false, false);

		m_fReplaceY = 45;

		break;

	case UPPER_SitMove:		// �ɾ� �ȱ�
		m_upper.pAni->init(UPPER_SitMoveWidth, UPPER_SitMoveHeight, UPPER_SitMoveWidth / UPPER_SitMoveFrame, UPPER_SitMoveHeight, UPPER_SitMoveY);

		if (m_nDir == DIR_Left)
			m_upper.pAni->setPlayFrameReverse(1, UPPER_SitMoveFrame, false, true);

		else
			m_upper.pAni->setPlayFrame(1, UPPER_SitMoveFrame, false, true);

		m_fReplaceY = 45;

		break;

	case UPPER_Move:		// �̵�
		m_upper.pAni->init(UPPER_MoveWidth, UPPER_MoveHeight, UPPER_MoveWidth / UPPER_MoveFrame, UPPER_MoveHeight, UPPER_MoveY);

		if (m_nDir == DIR_Left)
			m_upper.pAni->setPlayFrameReverse(1, UPPER_MoveFrame, false, true);

		else
			m_upper.pAni->setPlayFrame(1, UPPER_MoveFrame, false, true);

		m_fReplaceY = 25;

		break;

	case UPPER_Jump:		// ����
		m_upper.pAni->init(UPPER_JumpWidth, UPPER_JumpHeight, UPPER_JumpWidth / UPPER_JumpFrame, UPPER_JumpHeight, UPPER_JumpY);

		if (m_nDir == DIR_Left)
			m_upper.pAni->setPlayFrameReverse(1, UPPER_JumpFrame, true, false);

		else
			m_upper.pAni->setPlayFrame(1, UPPER_JumpFrame, true, false);

		m_fReplaceY = 45;

		break;

	case UPPER_JumpMove:	// ���� �̵�
		m_upper.pAni->init(UPPER_JumpMoveWidth, UPPER_JumpMoveHeight, UPPER_JumpMoveWidth / UPPER_JumpMoveFrame, UPPER_JumpMoveHeight, UPPER_JumpMoveY);

		if (m_nDir == DIR_Left)
			m_upper.pAni->setPlayFrameReverse(1, UPPER_JumpMoveFrame, true, false);

		else
			m_upper.pAni->setPlayFrame(1, UPPER_JumpMoveFrame, true, false);

		m_fReplaceY = 45;

		break;

	case UPPER_Death:		// ����
		m_upper.pAni->init(UPPER_DeathWidth, UPPER_DeathHeight, UPPER_DeathWidth / UPPER_DeathFrame, UPPER_DeathHeight, UPPER_DeathY);

		if (m_nDir == DIR_Left)
			m_upper.pAni->setPlayFrameReverse(1, UPPER_DeathFrame, false, false);

		else
			m_upper.pAni->setPlayFrame(1, UPPER_DeathFrame, false, false);

		m_fReplaceY = 70;

		break;

	case UPPER_SlugEscape:	// ������ Ż��
		m_upper.pAni->init(UPPER_SlugEscapeWidth, UPPER_SlugEscapeHeight, UPPER_SlugEscapeWidth / UPPER_SlugEscapeFrame, UPPER_SlugEscapeHeight, UPPER_SlugEscapeY);

		if (m_nDir == DIR_Left)
			m_upper.pAni->setPlayFrameReverse(1, UPPER_SlugEscapeFrame, false, false);

		else
			m_upper.pAni->setPlayFrame(1, UPPER_SlugEscapeFrame, false, false);

		m_fReplaceY = 60;

		break;


		// ### ������ �Ծ��� �� ��� ###

	case UPPER_GunIdle:		// �� ���
		m_upper.pAni->init(UPPER_GunIdleWidth, UPPER_GunIdleHeight, UPPER_GunIdleWidth / UPPER_GunIdleFrame, UPPER_GunIdleHeight, UPPER_GunIdleY);

		if (m_nDir == DIR_Left)
			m_upper.pAni->setPlayFrameReverse(1, UPPER_GunIdleFrame, true, true);

		else
			m_upper.pAni->setPlayFrame(1, UPPER_GunIdleFrame, true, true);

		m_fReplaceY = 25;

		break;

	case UPPER_GunMove:		// �� �ȱ�
		m_upper.pAni->init(UPPER_GunMoveWidth, UPPER_GunMoveHeight, UPPER_GunMoveWidth / UPPER_GunMoveFrame, UPPER_GunMoveHeight, UPPER_GunMoveY);

		if (m_nDir == DIR_Left)
			m_upper.pAni->setPlayFrameReverse(1, UPPER_GunMoveFrame, false, true);

		else
			m_upper.pAni->setPlayFrame(1, UPPER_GunMoveFrame, false, true);

		m_fReplaceY = 25;

		break;

	case UPPER_GunSit:		 // �� �ɱ�
		m_upper.pAni->init(UPPER_GunSitWidth, UPPER_GunSitHeight, UPPER_GunSitWidth / UPPER_GunSitFrame, UPPER_GunSitHeight, UPPER_GunSitY);

		if (m_nDir == DIR_Left)
			m_upper.pAni->setPlayFrameReverse(1, UPPER_GunSitFrame, false, false);

		else
			m_upper.pAni->setPlayFrame(1, UPPER_GunSitFrame, false, false);

		m_fReplaceY = 45;

		break;

	case UPPER_GunSitIdle:	// �� �ɾ� ���
		m_upper.pAni->init(UPPER_GunSitIdleWidth, UPPER_GunSitIdleHeight, UPPER_GunSitIdleWidth / UPPER_GunSitIdleFrame, UPPER_GunSitIdleHeight, UPPER_GunSitIdleY);

		if (m_nDir == DIR_Left)
			m_upper.pAni->setPlayFrameReverse(1, UPPER_GunSitIdleFrame, true, true);

		else
			m_upper.pAni->setPlayFrame(1, UPPER_GunSitIdleFrame, true, true);

		m_fReplaceY = 45;

		break;

	case UPPER_GunSitMove:	// �� �ɾ� �ȱ�
		m_upper.pAni->init(UPPER_GunSitMoveWidth, UPPER_GunSitMoveHeight, UPPER_GunSitMoveWidth / UPPER_GunSitMoveFrame, UPPER_GunSitMoveHeight, UPPER_GunSitMoveY);

		if (m_nDir == DIR_Left)
			m_upper.pAni->setPlayFrameReverse(1, UPPER_GunSitMoveFrame, false, true);

		else
			m_upper.pAni->setPlayFrame(1, UPPER_GunSitMoveFrame, false, true);

		m_fReplaceY = 45;

		break;

	case UPPER_Att:			// �⺻ ����
		m_upper.pAni->init(UPPER_AttWidth, UPPER_AttHeight, UPPER_AttWidth / UPPER_AttFrame, UPPER_AttHeight, UPPER_AttY);
		m_upper.pAni->setPlayFrameReverse(1, UPPER_AttFrame, false, false);

		if (m_nDir == DIR_Left)
		{
			m_upper.pAni->setPlayFrameReverse(1, UPPER_AttFrame, false, false);

			m_fAttReplaceX = -50;
			m_fAttReplaceY = -20;
			m_fReplaceY = 20;
		}

		else
		{
			m_upper.pAni->setPlayFrame(1, UPPER_AttFrame, false, false);

			m_fAttReplaceX = 100;
			m_fAttReplaceY = -20;
			m_fReplaceY = 20;
		}

		break;

		// ### ���� ��� ###
	case UPPER_Att90:		// �⺻ ���� (��)
		m_upper.pAni->init(UPPER_Att90Width, UPPER_Att90Height, UPPER_Att90Width / UPPER_Att90Frame, UPPER_Att90Height, UPPER_Att90Y);
		m_upper.pAni->setPlayFrameReverse(1, UPPER_Att90Frame, false, false);

		if (m_nDir == DIR_Left)
			m_upper.pAni->setPlayFrameReverse(1, UPPER_Att90Frame, false, false);

		else
			m_upper.pAni->setPlayFrame(1, UPPER_Att90Frame, false, false);

		break;

	case UPPER_Att270:		// �⺻ ���� (��)
		m_upper.pAni->init(UPPER_Att270Width, UPPER_Att270Height, UPPER_Att270Width / UPPER_Att270Frame, UPPER_Att270Height, UPPER_Att270Y);
		m_upper.pAni->setPlayFrameReverse(1, UPPER_Att270Frame, false, false);

		if (m_nDir == DIR_Left)
			m_upper.pAni->setPlayFrameReverse(1, UPPER_Att270Frame, false, false);

		else
			m_upper.pAni->setPlayFrame(1, UPPER_Att270Frame, false, false);

		break;

	case UPPER_GunAtt:		// �� ����
		m_upper.pAni->init(UPPER_GunAttWidth, UPPER_GunAttHeight, UPPER_GunAttWidth / UPPER_GunAttFrame, UPPER_GunAttHeight, UPPER_GunAttY);
		m_upper.pAni->setPlayFrameReverse(1, UPPER_GunAttFrame, false, false);

		if (m_nDir == DIR_Left)
			m_upper.pAni->setPlayFrameReverse(1, UPPER_GunAttFrame, false, false);

		else
			m_upper.pAni->setPlayFrame(1, UPPER_GunAttFrame, false, false);

		break;

	case UPPER_GunAtt90:	// �� ���� (��)
		m_upper.pAni->init(UPPER_GunAtt90Width, UPPER_GunAtt90Height, UPPER_GunAtt90Width / UPPER_GunAtt90Frame, UPPER_GunAtt90Height, UPPER_GunAtt90Y);
		m_upper.pAni->setPlayFrameReverse(1, UPPER_GunAtt90Frame, false, false);

		if (m_nDir == DIR_Left)
			m_upper.pAni->setPlayFrameReverse(1, UPPER_GunAtt90Frame, false, false);

		else
			m_upper.pAni->setPlayFrame(1, UPPER_GunAtt90Frame, false, false);

		break;

	case UPPER_GunAtt270:	// �� ���� (��)
		m_upper.pAni->init(UPPER_GunAtt270Width, UPPER_GunAtt270Height, UPPER_GunAtt270Width / UPPER_GunAtt270Frame, UPPER_GunAtt270Height, UPPER_GunAtt270Y);
		m_upper.pAni->setPlayFrameReverse(1, UPPER_GunAtt270Frame, false, false);

		if (m_nDir == DIR_Left)
			m_upper.pAni->setPlayFrameReverse(1, UPPER_GunAtt270Frame, false, false);

		else
			m_upper.pAni->setPlayFrame(1, UPPER_GunAtt270Frame, false, false);

		break;

	case UPPER_Knife:		// �⺻ ���� ����
		m_upper.pAni->init(UPPER_KnifeWidth, UPPER_KnifeHeight, UPPER_KnifeWidth / UPPER_KnifeFrame, UPPER_KnifeHeight, UPPER_KnifeY);
		m_upper.pAni->setPlayFrameReverse(1, UPPER_KnifeFrame, false, false);

		if (m_nDir == DIR_Left)
			m_upper.pAni->setPlayFrameReverse(1, UPPER_KnifeFrame, false, false);

		else
			m_upper.pAni->setPlayFrame(1, UPPER_KnifeFrame, false, false);

		m_fReplaceY = 30;

		break;

	case UPPER_KnifeGun:	// �� ���� ����
		m_upper.pAni->init(UPPER_KnifeGunWidth, UPPER_KnifeGunHeight, UPPER_KnifeGunWidth / UPPER_KnifeGunFrame, UPPER_KnifeGunHeight, UPPER_KnifeGunY);

		if (m_nDir == DIR_Left)
			m_upper.pAni->setPlayFrameReverse(1, UPPER_KnifeGunFrame, false, false);

		else
			m_upper.pAni->setPlayFrame(1, UPPER_KnifeGunFrame, false, false);

		m_fReplaceY = 50;

		break;
	}

	m_fReplaceX = 0;

	// �ִϸ��̼� ���
	m_upper.pAni->start();
}

void player::setLower()
{
	// ��ü
	switch (m_nActLower)
	{
	case LOWER_NULL:		// ��ü ����
		m_lower.pAni->setPlayFrame(0, 0);
		break;

	case LOWER_Idle:		// ���
		m_lower.pAni->init(LOWER_IdleWidth, LOWER_IdleHeight, LOWER_IdleWidth / LOWER_IdleFrame, LOWER_IdleHeight, LOWER_IdleY);

		if (m_nDir == DIR_Left)
			m_lower.pAni->setPlayFrameReverse(1, LOWER_IdleFrame, true, true);

		else
			m_lower.pAni->setPlayFrame(1, LOWER_IdleFrame, true, true);

		m_fReplaceLowerY = 0;

		break;

	case LOWER_Move:		// �̵�
		m_lower.pAni->init(LOWER_MoveWidth, LOWER_MoveHeight, LOWER_MoveWidth / LOWER_MoveFrame, LOWER_MoveHeight, LOWER_MoveY);

		if (m_nDir == DIR_Left)
			m_lower.pAni->setPlayFrameReverse(1, LOWER_MoveFrame, false, true);

		else
			m_lower.pAni->setPlayFrame(1, LOWER_MoveFrame, false, true);

		m_fReplaceLowerY = -20;

		break;

	case LOWER_Jump:		// ����
		m_lower.pAni->init(LOWER_JumpWidth, LOWER_JumpHeight, LOWER_JumpWidth / LOWER_JumpFrame, LOWER_JumpHeight, LOWER_JumpY);

		if (m_nDir == DIR_Left)
			m_lower.pAni->setPlayFrameReverse(1, LOWER_JumpFrame, true, false);

		else
			m_lower.pAni->setPlayFrame(1, LOWER_JumpFrame, true, false);

		m_fReplaceLowerY = -50;

		break;

	case LOWER_JumpMove:	// ���� �̵�
		m_lower.pAni->init(LOWER_JumpMoveWidth, LOWER_JumpMoveHeight, LOWER_JumpMoveWidth / LOWER_JumpMoveFrame, LOWER_JumpMoveHeight, LOWER_JumpMoveY);

		if (m_nDir == DIR_Left)
			m_lower.pAni->setPlayFrameReverse(1, LOWER_JumpMoveFrame, true, false);

		else
			m_lower.pAni->setPlayFrame(1, LOWER_JumpMoveFrame, true, false);

		m_fReplaceLowerY = -50;

		break;
	}

	// �ִϸ��̼� ���
	m_lower.pAni->start();
}

void player::setDir()
{
	// ### ĳ���� ���� ���� ###

	m_fAngle = MY_UTIL::getAngle(m_upper.pImg->getX(),
		m_upper.pImg->getY(),
		g_ptMouse.x, g_ptMouse.y);

	// ���� ���� ��� ������ ������
	if (m_nActUpper == UPPER_Appear)
	{
		m_nDir = DIR_Right;
		return;
	}

	// ���콺 ������ ��ġ�� ���� ���� ���� (������ Ż��, ���� ��� �߿��� ������ ������� ����)
	if (m_nActUpper != UPPER_Death && m_nActUpper != UPPER_SlugEscape)
	{
		if (g_ptMouse.x <= m_upper.pImg->getX())			// ���콺 �����Ͱ� ĳ���� ���ʿ� ���� ���
		{
			if (m_nActUpper == UPPER_Sit)
				m_upper.pAni->setPlayFrameReverse(0, UPPER_SitFrame, false, false);

			else if (m_nActUpper == UPPER_GunSit)
				m_upper.pAni->setPlayFrameReverse(0, UPPER_GunSitFrame, false, false);

			m_nDir = DIR_Left;
			m_nDirY = DIR_NULL;
		}

		else if (g_ptMouse.x > m_upper.pImg->getX())		// ���콺 �����Ͱ� ĳ���� �����ʿ� ���� ���
		{
			if (m_nActUpper == UPPER_Sit)
				m_upper.pAni->setPlayFrame(0, UPPER_SitFrame, false, false);

			else if (m_nActUpper == UPPER_GunSit)
				m_upper.pAni->setPlayFrame(0, UPPER_GunSitFrame, false, false);

			m_nDir = DIR_Right;
			m_nDirY = DIR_NULL;
		}

		// ��, �� ��� ����
		// ���콺 �����Ͱ� ĳ���� ���� ���� ���
		if (g_ptMouse.y <= m_upper.pImg->getY() && m_fAngle > 0.7f && m_fAngle < 2.4f)
			m_nDirY = DIR_Up;

		// ���콺 �����Ͱ� ĳ���� �Ʒ��� ���� ���
		else if (g_ptMouse.y > m_upper.pImg->getY() && m_fAngle > 4.2f && m_fAngle < 5.5f)
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
			m_upper.rc.left = m_upper.rc.right - m_upper.pAni->getFrameWidth() * 3 + m_fReplaceX;
		}
		else
		{
			// ĳ���Ͱ� �������� ���� ������ ��ü�� ���ʿ� ��ü�� ������ ����� ��
			m_upper.rc.left = m_lower.rc.left;
			m_upper.rc.right = m_upper.rc.left + m_upper.pAni->getFrameWidth() * 3 + m_fReplaceX;
		}

		m_upper.rc.bottom = m_lower.rc.top + m_fReplaceY;
		m_upper.rc.top = m_upper.rc.bottom - m_upper.pAni->getFrameHeight() * 3;
	}
}

bool player::isReturnUpdate()
{
	// ### update �ʹݿ� return �ϴ� ���๮���� �����ϴ� �Լ� ###

	// �����׿� ž�� ���̸� �÷��̾� update ó�� �� �� (������ class���� ó��)
	if (m_isSlugIn == true)	return false;

	// �ִϸ��̼� ������ ������Ʈ
	m_upper.pAni->frameUpdate(TIMEMANAGER->getTimer()->getElapsedTime());
	m_lower.pAni->frameUpdate(TIMEMANAGER->getTimer()->getElapsedTime());

	// ���� ���� ��� return
	if (m_nActUpper == UPPER_Appear && m_upper.pAni->getIsPlaying() == true)	return false;

	// ������ ������ ��� ��� ���� (return true)
	else if (m_nActUpper == UPPER_Appear)
	{
		m_lower.pImg->setY(WINSIZEY / 2 + 115);
		m_fFloorHeight = WINSIZEY / 2 + 115;

		m_nActUpper = UPPER_Idle;
		m_nActLower = LOWER_Idle;
		m_isAct = true;

		return true;
	}

	else if (m_isCollide == true && (m_nActUpper == UPPER_Knife || m_nActUpper == UPPER_KnifeGun))
	{
		return false;
	}

	// �׾��� ��� ���� ��� ���� ��, �ִϸ��̼��� ������ GameOver ������ ����
	else if (m_isAlive == false)
	{
		if (m_nActUpper != UPPER_Death)
		{
			m_nActUpper = UPPER_Death;
			m_nActLower = LOWER_NULL;
			m_isAct = true;
			m_fGravity = 0;
		}

		else if (m_upper.pAni->getIsPlaying() == true && 
			m_lower.pImg->getY() + m_lower.pAni->getFrameHeight() < m_fFloorHeight)	// �÷��̾ �ٴڰ� ������ ���� ��
		{
			m_fGravity += 0.2f;
			m_lower.pImg->setY(m_lower.pImg->getY() + m_fGravity); 

			if (m_lower.pImg->getY() + m_lower.pAni->getFrameHeight() >= m_fFloorHeight + 30)
			{
				m_lower.pImg->setY(m_fFloorHeight + m_lower.pAni->getFrameHeight() + 60);
				m_isJump = false;
			}
		}

		// �׽�Ʈ
		else if (m_upper.pAni->getIsPlaying() == false)
		{
			Sleep(1000);
			//SCENEMANAGER->changeScene();
			return false;
		}	
		
		/*//����
		else if (m_upper.pAni->getIsPlaying() == false)
		{
			SCENEMANAGER->changeScene("GameOverScene");
			return;
		}	*/
	}
}

void player::fire()
{
	// ���� ��� ����
	fireActSet();

	// ���ùڽ� ����
	m_fAttX = m_upper.pImg->getX() + m_fAttReplaceX;
	m_fAttY = m_upper.pImg->getY() + m_fAttReplaceY;
	m_rcAtt = RectMakeCenter(m_fAttX, m_fAttY, 100, 50);

	// �Ѿ� �߻縦 ���� ���� ����
	m_fAngle = MY_UTIL::getAngle(m_fAttX,	
		m_fAttY,
		g_ptMouse.x, g_ptMouse.y);

	if (m_isCollide == true)
	{
		m_isCollide = false;
		m_isAttack = false;
	}
	// �Ѿ� �߻�
	if (m_isAttack == true && (m_nActUpper != UPPER_Knife || m_nActUpper != UPPER_KnifeGun))
	{
		m_pMissileMgr->fire(m_fAttX,			
			m_fAttY,
			m_fAngle, 10, i_player);
	}

	// ���� �� ������ ������ �ʱ�ȭ (���Ӱ��� ���)
	if (m_nActUpper != UPPER_Knife && m_nActUpper != UPPER_KnifeGun)
		m_upper.pAni->start();

	/*// �Ѿ� �߻�
	if (m_isCollide == false)
	{
		m_pMissileMgr->fire(m_fAttX,
			m_fAttY,
			m_fAngle, 10, i_player);
	}

	// ���� ��� ����
	fireActSet();

	// ���ùڽ� ����
	if (m_nActUpper == UPPER_Att || m_nActUpper == UPPER_Att90 || m_nActUpper == UPPER_Att270 ||
		m_nActUpper == UPPER_GunAtt || m_nActUpper == UPPER_GunAtt90 || m_nActUpper == UPPER_GunAtt270)
	{
		if (m_nDir == DIR_Left)
		{
			if (m_nActUpper == UPPER_Att90 || m_nActUpper == UPPER_GunAtt90 || 
				m_nActUpper == UPPER_KnifeGun || m_nActUpper == UPPER_Knife)
			{
				m_fAttReplaceX = 30;
				m_fAttReplaceY = -90;
				m_fReplaceY = 10;
			}

			else if (m_nActUpper == UPPER_Att270 || m_nActUpper == UPPER_GunAtt270)
			{
				m_fAttReplaceX = 0;
				m_fAttReplaceY = 40;

				if (m_nActUpper == UPPER_Att270)
					m_fReplaceY = 110;

				else if (m_nActUpper == UPPER_GunAtt270)
					m_fReplaceY = 140;
			}

			else if (m_nActUpper == UPPER_Att || m_nActUpper == UPPER_GunAtt)
			{
				m_fAttReplaceX = -50;
				m_fAttReplaceY = -20;
				m_fReplaceY = 20;
			}
		}

		else if (m_nDir == DIR_Right)
		{
			if (m_nActUpper == UPPER_Att90 || m_nActUpper == UPPER_GunAtt90 ||
				m_nActUpper == UPPER_KnifeGun || m_nActUpper == UPPER_Knife)
			{
				m_fAttReplaceX = 30;
				m_fAttReplaceY = -90;
				m_fReplaceY = 10;
			}
			else if (m_nActUpper == UPPER_Att270 || m_nActUpper == UPPER_GunAtt270)
			{
				m_fAttReplaceX = 40;
				m_fAttReplaceY = 50;

				if (m_nActUpper == UPPER_Att270)
					m_fReplaceY = 110;

				else if (m_nActUpper == UPPER_GunAtt270)
					m_fReplaceY = 140;
			}
			else if (m_nActUpper == UPPER_Att || m_nActUpper == UPPER_GunAtt)
			{
				m_fAttReplaceX = 100;
				m_fAttReplaceY = -20;
				m_fReplaceY = 20;
			}
		}

		m_fAttX = m_upper.pImg->getX() + m_fAttReplaceX;
		m_fAttY = m_upper.pImg->getY() + m_fAttReplaceY;
		m_rcAtt = RectMake(m_fAttX, m_fAttY, 20, 20);

		m_fAngle = MY_UTIL::getAngle(m_fAttX,	// �Ѿ� �߻縦 ���� ���� ����
			m_fAttY,
			g_ptMouse.x, g_ptMouse.y);
	}

	// ���� �� ������ ������ �ʱ�ȭ (���Ӱ��� ���)
	if (m_nActUpper != UPPER_Knife && m_nActUpper != UPPER_KnifeGun)
		m_upper.pAni->start();*/
}

void player::fireActSet()
{
	if (m_nActUpper != UPPER_Att)
	{
		if (m_isAttack == false && m_nActUpper != UPPER_Att90 && m_nActUpper != UPPER_Att270 &&
			m_nActUpper != UPPER_Knife && m_nActUpper != UPPER_KnifeGun)
		{
			m_nActUpper = UPPER_Att;
			m_isAttack = true;
		}
		else
			m_isAttack = false;

		m_isAct = true;
	}

	// ��, �� ��� ����
	// ��� ���� : ����
	if (m_nDir == DIR_Left)
		fireActSetLeft();

	// ��� ���� : ������
	else
		fireActSetRight();

	/*// �⺻ ����
	if (m_isGun == false && m_isCollide == false)
	{
		if (m_nDirY == DIR_Up)				// ��
			m_nActUpper = UPPER_Att90;

		else if (m_nDirY == DIR_Down)		// �Ʒ�
			m_nActUpper = UPPER_Att270;

		else
			m_nActUpper = UPPER_Att;		// ��, ��
	}

	// �� ����
	else if (m_isGun == true && m_isCollide == false)
	{
		if (m_nDirY == DIR_Up)				// ��
			m_nActUpper = UPPER_GunAtt90;

		else if (m_nDirY == DIR_Down)		// �Ʒ�
			m_nActUpper = UPPER_GunAtt270;

		else
			m_nActUpper = UPPER_GunAtt;		// ��, ��
	}

	// ���� ���� ���� �� �浹 ����
	else if (m_isCollide == true)
	{
		if (m_isGun == true)				// ��
			m_nActUpper = UPPER_KnifeGun;

		else if (m_isGun == false)			// �⺻
			m_nActUpper = UPPER_Knife;

		m_isCollide = false;
	}*/
}

void player::fireActSetLeft()
{
	// ���� ��, ���콺 ���� ���
	if (m_isGun == true)
	{
		// �������� (�� ��� ����)
		if (m_isCollide == true)
		{
			m_upper.pAni->init(UPPER_KnifeGunWidth, UPPER_KnifeGunHeight, UPPER_KnifeGunWidth / UPPER_KnifeGunFrame, UPPER_KnifeGunHeight, UPPER_KnifeGunY);
			m_upper.pAni->setPlayFrameReverse(1, UPPER_KnifeGunFrame, false, false);

			m_fAttReplaceX = 30;
			m_fAttReplaceY = -90;
			m_fReplaceX = 0;
			m_fReplaceY = 50;
		}

		else if (m_nDirY == DIR_Up)
		{
			// UPPER_GunAtt90
			m_upper.pAni->init(UPPER_GunAtt90Width, UPPER_GunAtt90Height, UPPER_GunAtt90Width / UPPER_GunAtt90Frame, UPPER_GunAtt90Height, UPPER_GunAtt90Y);
			m_upper.pAni->setPlayFrameReverse(1, UPPER_GunAtt90Frame, false, false);

			m_fAttReplaceX = 30;
			m_fAttReplaceY = -90;
			m_fReplaceX = 0;
			m_fReplaceY = 10;
		}

		else if (m_nDirY == DIR_Down)
		{
			// UPPER_GunAtt270
			m_upper.pAni->init(UPPER_GunAtt270Width, UPPER_GunAtt270Height, UPPER_GunAtt270Width / UPPER_GunAtt270Frame, UPPER_GunAtt270Height, UPPER_GunAtt270Y);
			m_upper.pAni->setPlayFrameReverse(1, UPPER_GunAtt270Frame, false, false);

			m_fAttReplaceX = 0;
			m_fAttReplaceY = 40;
			m_fReplaceX = 0;
			m_fReplaceY = 140;
		}

		else
		{
			// UPPER_GunAtt
			m_upper.pAni->init(UPPER_GunAttWidth, UPPER_GunAttHeight, UPPER_GunAttWidth / UPPER_GunAttFrame, UPPER_GunAttHeight, UPPER_GunAttY);
			m_upper.pAni->setPlayFrameReverse(1, UPPER_GunAttFrame, false, false);

			m_fAttReplaceX = -50;
			m_fAttReplaceY = -20;
			m_fReplaceX = 0;
			m_fReplaceY = 20;
		}
	}

	// ���� ���� ����, ���콺 ���� ���
	else
	{
		// �������� (�� X, ����)
		if (m_isCollide == true)
		{
			m_upper.pAni->init(UPPER_KnifeWidth, UPPER_KnifeHeight, UPPER_KnifeWidth / UPPER_KnifeFrame, UPPER_KnifeHeight, UPPER_KnifeY);
			m_upper.pAni->setPlayFrameReverse(1, UPPER_KnifeFrame, false, false);

			m_fAttReplaceX = 30;
			m_fAttReplaceY = -90;
			m_fReplaceX = 30;
			m_fReplaceY = 30;
		}

		else if (m_nDirY == DIR_Up)
		{
			// UPPER_Att90
			m_upper.pAni->init(UPPER_Att90Width, UPPER_Att90Height, UPPER_Att90Width / UPPER_Att90Frame, UPPER_Att90Height, UPPER_Att90Y);
			m_upper.pAni->setPlayFrameReverse(1, UPPER_Att90Frame, false, false);

			m_fAttReplaceX = 30;
			m_fAttReplaceY = -90;
			m_fReplaceX = 0;
			m_fReplaceY = 10;
		}

		else if (m_nDirY == DIR_Down)
		{
			// UPPER_Att270
			m_upper.pAni->init(UPPER_Att270Width, UPPER_Att270Height, UPPER_Att270Width / UPPER_Att270Frame, UPPER_Att270Height, UPPER_Att270Y);
			m_upper.pAni->setPlayFrameReverse(1, UPPER_Att270Frame, false, false);

			m_fAttReplaceX = 0;
			m_fAttReplaceY = 40;
			m_fReplaceX = 0;
			m_fReplaceY = 110;
		}

		else
		{
			// UPPER_Att
			m_upper.pAni->init(UPPER_AttWidth, UPPER_AttHeight, UPPER_AttWidth / UPPER_AttFrame, UPPER_AttHeight, UPPER_AttY);
			m_upper.pAni->setPlayFrameReverse(1, UPPER_AttFrame, false, false);

			m_fAttReplaceX = -50;
			m_fAttReplaceY = -20;
			m_fReplaceX = 0;
			m_fReplaceY = 20;
		}
	}
}

void player::fireActSetRight()
{
	// ���� ��, ���콺 ������ ���
	if (m_isGun == true)
	{
		// �������� (�� ��� ������)
		if (m_isCollide == true)
		{
			m_upper.pAni->init(UPPER_KnifeGunWidth, UPPER_KnifeGunHeight, UPPER_KnifeGunWidth / UPPER_KnifeGunFrame, UPPER_KnifeGunHeight, UPPER_KnifeGunY);
			m_upper.pAni->setPlayFrame(1, UPPER_KnifeGunFrame, false, false);

			m_fAttReplaceX = 30;
			m_fAttReplaceY = -90;
			m_fReplaceX = 0;
			m_fReplaceY = 50;
		}

		else if (m_nDirY == DIR_Up)
		{
			// UPPER_GunAtt90
			m_upper.pAni->init(UPPER_GunAtt90Width, UPPER_GunAtt90Height, UPPER_GunAtt90Width / UPPER_GunAtt90Frame, UPPER_GunAtt90Height, UPPER_GunAtt90Y);
			m_upper.pAni->setPlayFrame(1, UPPER_GunAtt90Frame, false, false);

			m_fAttReplaceX = 30;
			m_fAttReplaceY = -90;
			m_fReplaceX = 0;
			m_fReplaceY = 10;
		}

		else if (m_nDirY == DIR_Down)
		{
			// UPPER_GunAtt270
			m_upper.pAni->init(UPPER_GunAtt270Width, UPPER_GunAtt270Height, UPPER_GunAtt270Width / UPPER_GunAtt270Frame, UPPER_GunAtt270Height, UPPER_GunAtt270Y);
			m_upper.pAni->setPlayFrame(1, UPPER_GunAtt270Frame, false, false);

			m_fAttReplaceX = 40;
			m_fAttReplaceY = 50;
			m_fReplaceX = 0;
			m_fReplaceY = 140;
		}

		else
		{
			// UPPER_GunAtt
			m_upper.pAni->init(UPPER_GunAttWidth, UPPER_GunAttHeight, UPPER_GunAttWidth / UPPER_GunAttFrame, UPPER_GunAttHeight, UPPER_GunAttY);
			m_upper.pAni->setPlayFrame(1, UPPER_GunAttFrame, false, false);

			m_fAttReplaceX = 100;
			m_fAttReplaceY = -20;
			m_fReplaceX = 0;
			m_fReplaceY = 20;
		}
	}

	// ���� ���� ����, ���콺 ������ ���
	else
	{
		// �������� (�� X, ������)
		if (m_isCollide == true)
		{
			m_upper.pAni->init(UPPER_KnifeWidth, UPPER_KnifeHeight, UPPER_KnifeWidth / UPPER_KnifeFrame, UPPER_KnifeHeight, UPPER_KnifeY);
			m_upper.pAni->setPlayFrame(1, UPPER_KnifeFrame, false, false);

			m_fAttReplaceX = 30;
			m_fAttReplaceY = -90;
			m_fReplaceX = -30;
			m_fReplaceY = 30;
		}

		else if (m_nDirY == DIR_Up)
		{
			// UPPER_Att90
			m_upper.pAni->init(UPPER_Att90Width, UPPER_Att90Height, UPPER_Att90Width / UPPER_Att90Frame, UPPER_Att90Height, UPPER_Att90Y);
			m_upper.pAni->setPlayFrame(1, UPPER_Att90Frame, false, false);

			m_fAttReplaceX = 30;
			m_fAttReplaceY = -90;
			m_fReplaceX = 0;
			m_fReplaceY = 10;
		}

		else if (m_nDirY == DIR_Down)
		{
			// UPPER_Att270
			m_upper.pAni->init(UPPER_Att270Width, UPPER_Att270Height, UPPER_Att270Width / UPPER_Att270Frame, UPPER_Att270Height, UPPER_Att270Y);
			m_upper.pAni->setPlayFrame(1, UPPER_Att270Frame, false, false);

			m_fAttReplaceX = 40;
			m_fAttReplaceY = 50;
			m_fReplaceX = 0;
			m_fReplaceY = 110;
		}

		else
		{
			// UPPER_Att
			m_upper.pAni->init(UPPER_AttWidth, UPPER_AttHeight, UPPER_AttWidth / UPPER_AttFrame, UPPER_AttHeight, UPPER_AttY);
			m_upper.pAni->setPlayFrame(1, UPPER_AttFrame, false, false);

			m_fAttReplaceX = 100;
			m_fAttReplaceY = -20;
			m_fReplaceX = 0;
			m_fReplaceY = 20;
		}
	}
}

void player::move()
{
	// (�÷��̾� <- �� �Ѿ�) �浹 RECT UPDATE
	m_rcHit.bottom = m_lower.rc.bottom;
	m_rcHit.left = m_upper.pImg->getX();
	m_rcHit.right = m_rcHit.left + PLAYER_RectWidth;
	if (g_saveData.isMoveMap == false) {
		if (m_nActUpper == UPPER_Sit || m_nActUpper == UPPER_SitMove)
			m_rcHit.top = m_rcHit.bottom - PLAYER_RectHeight + 30;
		else
			m_rcHit.top = m_rcHit.bottom - PLAYER_RectHeight;

	// Ű �Է� ó��
	// �ɱ�
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		if ((m_nActUpper != UPPER_Sit && m_nActUpper != UPPER_SitMove) &&
			(m_nActLower != LOWER_Jump && m_nActLower != LOWER_JumpMove) &&
			(m_nActUpper != UPPER_GunSit && m_nActUpper != UPPER_GunSitMove))
		{
			if (m_isGun == true)
				m_nActUpper = UPPER_GunSit;

			else
				m_nActUpper = UPPER_Sit;

			m_nActLower = LOWER_NULL;
			m_isAct = true;
		}
	}

	// Ű�� �� ��� �ɾ��� �� �ٽ� �Ͼ
	if (KEYMANAGER->isOnceKeyUp('S') &&
		(m_nActUpper == UPPER_Sit || m_nActUpper == UPPER_SitMove ||
		m_nActUpper == UPPER_GunSit || m_nActUpper == UPPER_GunSitMove))
	{
		if (m_isGun == true)
			m_nActUpper = UPPER_GunIdle;
		else
			m_nActUpper = UPPER_Idle;

		m_nActLower = LOWER_Idle;
		m_fSpeed = Move_Speed;
		m_isAct = true;
	}

	// ����
	else if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && m_nActLower != LOWER_Jump && m_nActLower != LOWER_JumpMove)
	{
		// �̵��ϴ� ���� jump�� ��� jumpMove������� ����  
		if (m_nActLower == LOWER_Move)
		{
			if (m_isGun == true)				// �� ����� ��ü �����̵� => GunMove
				m_nActUpper = UPPER_GunMove;
			else
				m_nActUpper = UPPER_JumpMove;

			m_nActLower = LOWER_JumpMove;

			m_fCurrHeight = m_lower.pImg->getY();	// ���� Y��ǥ ����
			m_isAct = true;
			m_isJump = true;

			return;
		}

		// ���ڸ� jump ���
		else if (m_nActUpper != UPPER_Jump)
		{
			if (m_isGun == true)				// �� ����� ��ü ���� => GunIdle
				m_nActUpper = UPPER_GunIdle;
			else
				m_nActUpper = UPPER_Jump;

			m_nActLower = LOWER_Jump;

			m_fCurrHeight = m_lower.pImg->getY();	// ���� Y��ǥ ����
			m_isAct = true;
			m_isJump = true;
		}
	}

	// ���� => ���
	if ((m_nActLower == LOWER_Jump || m_nActLower == LOWER_JumpMove ||
		m_nActUpper == UPPER_SlugEscape) && m_isJump == true)			// ������ Ż�⵵ ���� ����
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

	// ���� => �ϰ�
	if ((m_nActLower == LOWER_Jump || m_nActLower == LOWER_JumpMove ||
		m_nActUpper == UPPER_SlugEscape) && m_isJump == false)			// ������ Ż�⵵ ���� ����
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

			if (m_isGun == true)
				m_nActUpper = UPPER_GunIdle;

			else
				m_nActUpper = UPPER_Idle;

			m_nActLower = LOWER_Idle;
			m_fGravity = 10;
			m_isAct = true;
		}
	}

	// �̵� => ��
	if (KEYMANAGER->isStayKeyDown('A') && m_upper.pImg->getX() > 0 &&
		m_nActUpper != UPPER_SlugEscape && m_nActUpper != UPPER_Death)			// ���� �̵�
	{																			//	
		if (m_nActUpper != UPPER_Move && m_nActUpper != UPPER_Att &&			// �ȱ�, ����			�ƴ� ��
			m_nActUpper != UPPER_Sit && m_nActUpper != UPPER_SitMove &&			// �ɱ�, �ɾưȱ�		�ƴ� ��
			m_nActLower != LOWER_Jump && m_nActLower != LOWER_JumpMove &&		// ����, �����ȱ�		�ƴ� ��
			m_nActUpper != UPPER_SlugEscape && m_nActUpper != UPPER_Death &&	// ������ Ż��, ����	�ƴ� ��
			m_nActUpper != UPPER_GunMove &&
			m_nActUpper != UPPER_GunSit && m_nActUpper != UPPER_GunSitMove &&
			m_nActUpper != UPPER_Knife && m_nActUpper != UPPER_KnifeGun)		// �� ����, �� �ɱ�, �� �ɾưȱ� �ƴ� ��				
		{																		//
			if (m_isGun == true)												// �� �����
				m_nActUpper = UPPER_GunMove;
			else
				m_nActUpper = UPPER_Move;										// �ȱ� ������� �����Ѵ�.

			m_isAct = true;
		}

		else if ((m_nActUpper == UPPER_Sit && m_nActUpper != UPPER_SitMove) ||	// �ɾ� �����鼭 �ɾưȱ� ����� �ƴ� ��
			(m_nActUpper == UPPER_GunSit && m_nActUpper != UPPER_GunSitMove))
		{
			if (m_isGun == true)
				m_nActUpper = UPPER_GunSitMove;									// �� �����
			else
				m_nActUpper = UPPER_SitMove;									// �ɾưȱ� ������� ����

			m_isAct = true;
			m_nActLower = LOWER_NULL;
			m_fSpeed = Sit_Speed;
		}

		else if (m_nActLower == LOWER_Jump || m_nActLower == LOWER_JumpMove)	// ���� ���߿� �̵��� ���
		{
			if (m_isGun == true)												// �� ����� ��ü ���� => GunIdle
				m_nActUpper = UPPER_GunIdle;
			else
				m_nActUpper = UPPER_JumpMove;

			// ��ü ���� ��� ����
			if (m_nActLower != LOWER_JumpMove)
			{
				m_nActLower = LOWER_JumpMove;
				m_isAct = true;
			}
		}

		if (m_nActLower != LOWER_Move && m_nActLower != LOWER_NULL &&
			m_nActLower != LOWER_Jump && m_nActLower != LOWER_JumpMove)
				m_nActLower = LOWER_Move;

		m_upper.pImg->setX(m_upper.pImg->getX() - m_fSpeed);
		m_lower.pImg->setX(m_lower.pImg->getX() - m_fSpeed);
	}

	// �̵� => ��
	else if (KEYMANAGER->isStayKeyDown('D') && m_upper.pImg->getX() < WINSIZEX &&
		m_nActUpper != UPPER_SlugEscape && m_nActUpper != UPPER_Death)			// ������ �̵�
	{																			//
		if (m_nActUpper != UPPER_Move && m_nActUpper != UPPER_Att &&			// �ȱ�, ����		�ƴ� ��
			m_nActUpper != UPPER_Sit && m_nActUpper != UPPER_SitMove &&			// �ɱ�, �ɾưȱ�		�ƴ� ��
			m_nActLower != LOWER_Jump && m_nActLower != LOWER_JumpMove &&		// ����, �����ȱ�		�ƴ� ��
			m_nActUpper != UPPER_SlugEscape && m_nActUpper != UPPER_Death &&	// ������ Ż��, ����	�ƴ� ��
			m_nActUpper != UPPER_GunMove &&
			m_nActUpper != UPPER_GunSit && m_nActUpper != UPPER_GunSitMove &&
			m_nActUpper != UPPER_Knife && m_nActUpper != UPPER_KnifeGun)		// �� ����, �� �ɱ�, �� �ɾưȱ� �ƴ� ��		)		// �� ����, �� �ɱ�, �� �ɾưȱ� �ƴ� ��
		{																		//
			if (m_isGun == true)												// �� �����
				m_nActUpper = UPPER_GunMove;
			else
				m_nActUpper = UPPER_Move;										// �ȱ� ������� �����Ѵ�.

			m_isAct = true;
		}

		else if ((m_nActUpper == UPPER_Sit && m_nActUpper != UPPER_SitMove) ||	// �ɾ� �����鼭 �ɾưȱ� ����� �ƴ� ��
			(m_nActUpper == UPPER_GunSit && m_nActUpper != UPPER_GunSitMove))
		{
			if (m_isGun == true)
				m_nActUpper = UPPER_GunSitMove;									// �� �����
			else
				m_nActUpper = UPPER_SitMove;									// �ɾưȱ� ������� ����

			m_isAct = true;
			m_nActLower = LOWER_NULL;
			m_fSpeed = Sit_Speed;
		}

		else if (m_nActLower == LOWER_Jump || m_nActLower == LOWER_JumpMove)	// ���� ���߿� �̵��� ���
		{
			if (m_isGun == true)												// �� ����� ��ü ���� => GunIdle
				m_nActUpper = UPPER_GunIdle;
			else
				m_nActUpper = UPPER_JumpMove;

			// ��ü ���� ��� ����
			if (m_nActLower != LOWER_JumpMove)
			{
				m_nActLower = LOWER_JumpMove;
				m_isAct = true;
			}
		}

		if (m_nActLower != LOWER_Move && m_nActLower != LOWER_NULL &&
			m_nActLower != LOWER_Jump && m_nActLower != LOWER_JumpMove)
				m_nActLower = LOWER_Move;

			m_upper.pImg->setX(m_upper.pImg->getX() + m_fSpeed);
			m_lower.pImg->setX(m_lower.pImg->getX() + m_fSpeed);
		}

	// ���� (���콺 ������)
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) &&
		m_nActUpper != UPPER_Sit && m_nActUpper != UPPER_SitMove &&
		m_nActUpper != UPPER_SlugEscape && m_nActUpper != UPPER_Death && m_nActUpper )
	{
		fire();	// ����
	}

	// Ű�� �� ��� �ൿ���� �������� �ٲ�
	if (KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('D') &&
		m_nActUpper != UPPER_SlugEscape && m_nActUpper != UPPER_Death)
	{
		// �ɾƼ� �����̰� �־��� ��� '�ɾƴ��' ���·� ����
		if (m_nActUpper == UPPER_SitMove || m_nActUpper == UPPER_Sit ||
			m_nActUpper == UPPER_GunSitMove || m_nActUpper == UPPER_GunSit)
		{
			if (m_isGun == true)
				m_nActUpper = UPPER_GunSit;

			else
				m_nActUpper = UPPER_Sit;

			m_nActLower = LOWER_NULL;
			m_isAct = true;

				return;
			}

		// ���־��� ��� 'Idle'�� ����
		else if (m_nActUpper != UPPER_GunAtt && m_nActUpper != UPPER_GunSit && m_nActUpper != UPPER_GunSitMove && m_isGun == true)
			m_nActUpper = UPPER_GunIdle;

		else if (m_nActUpper != UPPER_Att && m_nActUpper != UPPER_Sit && m_nActUpper != UPPER_SitMove && m_isGun == false)
			m_nActUpper = UPPER_Idle;

		if (m_nActLower != LOWER_Jump && m_nActLower != LOWER_JumpMove && m_isJump == false)
		{
			m_nActLower = LOWER_Idle;
			m_isAct = true;
		}
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
	/*Rectangle(hdc, m_upper.rc.left, m_upper.rc.top, m_upper.rc.right, m_upper.rc.bottom);
	Rectangle(hdc, m_lower.rc.left, m_lower.rc.top, m_lower.rc.right, m_lower.rc.bottom);
	Rectangle(hdc, m_rcHit.left, m_rcHit.top, m_rcHit.right, m_rcHit.bottom);*/
	Rectangle(hdc, m_rcAtt.left, m_rcAtt.top, m_rcAtt.right, m_rcAtt.bottom);

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
	/*Rectangle(hdc, m_rcAtt.left, m_rcAtt.top, m_rcAtt.right, m_rcAtt.bottom);
	sprintf_s(szText, "isAttack: %d, m_isGun: %d", m_isAttack, m_isGun);
	TextOut(hdc, g_ptMouse.x, g_ptMouse.y + 30, szText, strlen(szText));*/
	_stprintf_s(szText, "m_nActUpper: %d", m_nActUpper);
	TextOut(hdc, 100, 100, szText, strlen(szText));
	_stprintf_s(szText, "m_nActLower: %d", m_nActLower);
	TextOut(hdc, 100, 150, szText, strlen(szText));
}

void player::dataSave()
{
	vector<string> vSaveData;

	TXTDATA->txtSave("data/playerData.txt", vSaveData);
}

void player::dataLoad()
{
	TXTDATA->txtLoadInt("data/playerData.txt");
}


player::player()
{
}


player::~player()
{
}
