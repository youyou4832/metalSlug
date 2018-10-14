#include "stdafx.h"
#include "player.h"
#include "animation.h"
#include "timer.h"
#include "missileManager.h"

#define Jump_Height	100

// #######################################################################
// 13(토)까지 근거리공격(+AttBox충돌) + 탈것 탈출(슬러그에서 내릴 때 bool변수 변경, bool변수에 따라 모션 재생)
//			  죽음: update() 함수에 GameOver 씬으로 변경 실행문 추가 해야 함, 죽음 모션 추가 필요
// 14(일)까지 아이템 먹었을 때 헤비머신건
// 15(월)까지 폭탄공격(아이템을 먹으면 폭탄 갯수 증가=>아이템 클래스에서 플레이어에게 명령
//		 폭탄을 사용했을 때(갯수 > 0) 폭탄 던지는 모션 + 폭탄(미사일클래스)
//			 
// #######################################################################

HRESULT player::init(float x, float y)
{
	// 슬러그에 탑승 중이면 플레이어 update 처리 안 함 (슬러그 class에서 처리)
	if (m_isSlugIn == true)	return;

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

	// 미사일
	IMAGEMANAGER->addImage("playerMissile", "image/player/playerBullet.bmp", 8, 8, true, RGB(255, 0, 255));

	m_pMissileMgr = new missileManager;
	m_pMissileMgr->init("playerMissile", WINSIZEY, 10);
	
	return S_OK;
}

void player::update()
{
	// 슬러그에 탑승 중이면 플레이어 update 처리 안 함 (슬러그 class에서 처리)
	if (m_isSlugIn == true)	return;

	// 애니메이션
	m_upper.pAni->frameUpdate(TIMEMANAGER->getTimer()->getElapsedTime());
	m_lower.pAni->frameUpdate(TIMEMANAGER->getTimer()->getElapsedTime());

	// 등장 중일 경우 return
	if (m_nActUpper == UPPER_Appear && m_upper.pAni->getIsPlaying() == true)	return;

	// 죽었을 경우 죽음 모션 세팅 후, 애니메이션이 끝나면 GameOver 씬으로 변경
	if (m_isAlive == false)
	{
		m_nActUpper = UPPER_Death;
		m_nActLower = LOWER_NULL;

		if (m_upper.pAni->getIsPlaying() == false)
			//SCENEMANAGER->changeScene();

		return;
	}

	// 플레이어
	setDir();
	move();
	actSet();

	// 미사일
	m_pMissileMgr->update();
}

void player::actSet()
{
	// ### 모션 지정 총 관리 함수 ###
	
	// 반복모션 제외, isPlaying == false일 경우
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

	// 탈것 탈출

	// 죽음

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

	case UPPER_Att:		// 공격은 fire() 함수에서
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
		
	case LOWER_Jump:	// 점프
		m_lower.pAni->init(LOWER_JumpWidth, LOWER_JumpHeight, LOWER_JumpWidth / LOWER_JumpFrame, LOWER_JumpHeight, LOWER_JumpY);

		if (m_nDir == DIR_Left)
		{
			m_lower.pAni->setPlayFrameReverse(1, LOWER_JumpFrame, true, false);
		}
		else
			m_lower.pAni->setPlayFrame(1, LOWER_JumpFrame, true, false);

		m_fReplaceLowerY = -50;

		break;

	case LOWER_JumpMove:	// 점프 이동
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

void player::setResourceRect()
{
	// ### 리소스 좌표 세팅 ###
	// 리소스 사이즈와 위치가 일정하지 않기 때문에 세팅 필요
	if (m_nActUpper != UPPER_Appear)
	{
		// 리소스 좌표 세팅: 다리를 중심으로, 상체를 올린다. (상체는 사이즈와 기준점 위치가 변하므로)
		// 상, 하체 위치 업데이트
		m_lower.rc = RectMake(m_lower.pImg->getX(), m_lower.pImg->getY() + m_lower.pAni->getFrameHeight() + m_fReplaceLowerY,
			m_lower.pAni->getFrameWidth() * 3, m_lower.pAni->getFrameHeight() * 3);

		if (m_nDir == DIR_Left)
		{
			// 캐릭터가 왼쪽을 보고 있으면 하체의 오른쪽에 상체의 오른쪽을 맞춰야 함
			m_upper.rc.right = m_lower.rc.right;
			m_upper.rc.left = m_upper.rc.right - m_upper.pAni->getFrameWidth() * 3;
		}
		else
		{
			// 캐릭터가 오른쪽을 보고 있으면 하체의 왼쪽에 상체의 왼쪽을 맞춰야 함
			m_upper.rc.left = m_lower.rc.left;
			m_upper.rc.right = m_upper.rc.left + m_upper.pAni->getFrameWidth() * 3;
		}

		m_upper.rc.bottom = m_lower.rc.top + m_fReplaceY;
		m_upper.rc.top = m_upper.rc.bottom - m_upper.pAni->getFrameHeight() * 3;
	}
}

void player::fire()
{
	int attReplaceX = 0;	// 어택박스 X, Y 좌표 수정
	int attReplaceY = 0;

	// 모션변경
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

	// 어택박스
	m_fAttX = m_upper.pImg->getX() + attReplaceX;
	m_fAttY = m_upper.pImg->getY() + attReplaceY;

	m_fAngle = MY_UTIL::getAngle(m_fAttX,	// 총알 발사를 위한 각도 지정
		m_fAttY,
		g_ptMouse.x, g_ptMouse.y);

	m_pMissileMgr->fire(m_fAttX,			// 총알 발사
		m_fAttY,
		m_fAngle, 10, i_player);

	// 공격 할 때마다 프레임 초기화 (연속공격 모션)
	m_upper.pAni->start();
}

void player::move()
{
	// (플레이어 <- 적 총알) 충돌 RECT UPDATE
	m_rcHit.bottom = m_lower.rc.bottom;
	m_rcHit.left = m_upper.pImg->getX();
	m_rcHit.right = m_rcHit.left + PLAYER_RectWidth;

	if (m_nActUpper == UPPER_Sit || m_nActUpper == UPPER_SitMove)
		m_rcHit.top = m_rcHit.bottom - PLAYER_RectHeight + 30;
	else
		m_rcHit.top = m_rcHit.bottom - PLAYER_RectHeight;

	// 키 입력 처리
	// 앉기
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
	
	// 점프
	else if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && m_nActLower != LOWER_Jump)
	{	
		m_isAct = true;
		m_isJump = true;

		m_fCurrHeight = m_lower.pImg->getY();

		// 이동하던 도중 jump할 경우 jumpMove모션으로 변경  
		if (m_nActLower != LOWER_Jump && m_nActLower != LOWER_JumpMove &&
			m_nActLower == LOWER_Move)
		{
			m_nActUpper = UPPER_JumpMove;
			m_nActLower = LOWER_JumpMove;

			return;
		}

		// 제자리 jump 모션
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
		else if (m_lower.pImg->getY() >= m_fCurrHeight)	// 점프 당시의 높이와 현재 높이가 같을 경우 (땅에 닿았을 경우)
		{
			m_lower.pImg->setY(m_fCurrHeight);
			m_fCurrHeight = 0;
			m_isJump = false;
			m_nActUpper = UPPER_Idle;
			m_nActLower = LOWER_Idle;
			m_fGravity = 10;
		}
	}

	// 이동
	if (KEYMANAGER->isStayKeyDown('A') && m_upper.pImg->getX() > 0)			// 왼쪽 이동
	{																		//	
		if (m_nActUpper != UPPER_Move && m_nActUpper != UPPER_Att &&		// 걷기, 공격		 아닐 때
			m_nActUpper != UPPER_Sit && m_nActUpper != UPPER_SitMove &&		// 앉기, 앉아걷기	 아닐 때
			m_nActLower != LOWER_Jump && m_nActLower != LOWER_JumpMove)		// 점프, 점프걷기	 아닐 때
		{																	//
			m_isAct = true;													//
			m_nActUpper = UPPER_Move;										// 걷기 모션으로 변경한다.
		}
		else if (m_nActUpper == UPPER_Sit && m_nActUpper != UPPER_SitMove)
		{
			m_isAct = true;
			m_nActUpper = UPPER_SitMove;
			m_nActLower = LOWER_NULL;
			m_fSpeed = 1.0f;
		}
		else if (m_nActLower == LOWER_Jump || m_nActLower == LOWER_JumpMove)	// 점프 도중에 이동할 경우
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
	else if (KEYMANAGER->isStayKeyDown('D') && m_upper.pImg->getX() < WINSIZEX)	// 오른쪽 이동
	{																			//
		if (m_nActUpper != UPPER_Move && m_nActUpper != UPPER_Att &&			// 걷기, 공격		 아닐 때
			m_nActUpper != UPPER_Sit && m_nActUpper != UPPER_SitMove &&			// 앉기, 앉아걷기	 아닐 때
			m_nActLower != LOWER_Jump && m_nActLower != LOWER_JumpMove)			// 점프, 점프걷기	 아닐 때
		{																		//
			m_isAct = true;														//
			m_nActUpper = UPPER_Move;											// 걷기 모션으로 변경한다.
		}
		else if (m_nActUpper == UPPER_Sit && m_nActUpper != UPPER_SitMove)		// 앉아 있으면서 앉아걷기 모션이 아닐 때
		{																		// 앉아걷기 모션으로 변경
			m_isAct = true;
			m_nActUpper = UPPER_SitMove;
			m_nActLower = LOWER_NULL;
			m_fSpeed = 1.0f;
		}
		else if (m_nActLower == LOWER_Jump || m_nActLower == LOWER_JumpMove)	// 점프 도중에 이동할 경우
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

	// 공격 (마우스 포인터)
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && m_nActUpper != UPPER_Sit && m_nActUpper != UPPER_SitMove)
	{
		if (m_nActUpper != UPPER_Att)
		{
			m_nActUpper = UPPER_Att;
			m_isAct = true;
		}

		fire();	// 공격
	}
	
	// 키를 뗐을 경우 행동하지 않음으로 바꿈
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

	// 앉았을 때 다시 일어남
	if (KEYMANAGER->isOnceKeyUp('S') && (m_nActUpper == UPPER_Sit || m_nActUpper == UPPER_SitMove))
	{
		m_nActUpper = UPPER_Idle;
		m_nActLower = LOWER_Idle;
		m_fSpeed = 3.0f;
		m_isAct = true;
	}

	// 죽음
	if (m_isAlive == false)
	{
		//m_nActUpper = UPPER_Dead;
		m_nActLower = NULL;
	}

	// ### 리소스 좌표 수정 ###
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
	// 슬러그에 탑승 중이면 플레이어 render 처리 안 함 (슬러그 class에서 처리)
	if (m_isSlugIn == true)	return;

	char szText[128];

	// 플레이어
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

	// 미사일
	m_pMissileMgr->render(hdc, i_player);

	//// 테스트
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
