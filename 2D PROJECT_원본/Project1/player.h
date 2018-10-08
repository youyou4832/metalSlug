#pragma once
class missileManager;

class player
{
			/*
			186(31)-240 6개 캐릭터 등장 0-
			124* 29(4개) 캐릭터 기본 상태  0-
			384(32)- 28 12개 캐릭터 상반신 달리기 0-
			160(32) -35 6개 캐릭터 점프 상반신	0-
			160(32)-35 6개 캐릭터 앞으로 점프 상반신 0-

			87(29)- 41 3개  캐릭터 앉기 모션 0-
			124(31)-27 4개 캐릭터 앉은 상태 대기 모션 0-
			245(35)-24 7개  캐릭터 앉아서 이동 0-

			520(52) - 29 10개	캐릭터 기본 공격 모션 완성본 0-
			290(29)-66 10개 캐릭터 기본무기 위 공격 0-
			240(60)*24 4개 캐릭터 왼쪽 공격 0-
			520(52)-29 10개 캐릭터 앉은 상태 기본 공격0-
			138(23)*54 6개 캐릭터 점프 아래 공격	0-
			6*(44) * 48 6개캐릭터 기본 근접공격 모션 0-
			168(42)-35 4개 캐릭터 앉아서 근접 공격 0-

			152(38)-29 캐릭터 무기 기본 상태	0-
			516(43)-31 12개 캐릭터 무기 이동	0-
			117(39)- 42 3개 캐릭터 무기 앉기 모션 0-
			164(41)-24 4캐릭터 무기 앉은 상태 대기 모션	0-
			287(41)-24 7개 캐릭터 무기 앉아서 이동	0-

			240(60)-28 4개 캐릭터 무기 공격	0-
			324(81)-27 4개 캐릭터 무기 왼쪽 공격	0-
			110(55)-58 2개 캐릭터 무기 공격(중간에서 위)	0-
			96(24)-72 4개 캐릭터 무기 위 공격 		0-
			110(55)-63 2개 캐릭터 무기 공격(위에서 아래)	0-

			104(52)-58 2개 캐릭터 무기 공격 (중간에서  아래)	0-
			136(34)-64 4개 캐릭터 무기 아래 공격			0-
			104(52)-59 2개 캐릭터 무기 공격(아래에서 위)		0-

			156(78)-61 2개 캐릭터 무기 왼쪽 공격(중간에서 아래)	0-
			154(77)-61 2개 캐릭터 무기 왼쪽 공격(아래에서 위)	0-
			268(67)-28 4개 캐릭터 무기 앉아서 공격			0-

			198(33)-29 6개 캐릭터 기본 폭탄 던지기		0-
			246(41)-28 6개 캐릭터 기본 앉아서 폭탄 던지기	0-
			240(40) - 29캐릭터 무기든 폭탄 공격		0-
			264(44) - 36캐릭터 무기든 앉아서 폭탄		0-

			330(55)-42_캐릭터 무기든 근접 공격		0-
			360(60)-33 캐릭터 무기든 앉아 근접 공격		0-
			384(32)-34 캐릭터 슬러그 탈출			0-

			931(49)-44 19개캐릭터 죽음1		0-

			84(21)* 16 (4개) 캐릭터 대기 하 모션  0-
			372(31)- 20 12개 캐릭터 달리기 하반신 0-
			126(26)-24 6개 제자리 점프 하반신	0-
			198(33)-21 6개 캐릭터 하반신 앞 점프	0-
			*/


	// 플레이어 상체 중심점 / 플레이어 하체 중심점을 init할 때 스캔해서 배열에 저장
	// 이미지를 출력할 때 해당 중심점에서 n만큼 떨어진 거리를 이미지의 중심으로 잡은 후 출력

// 상체
#define UPPER_AppearWidth	186
#define UPPER_AppearHeight	240
#define UPPER_AppearY		0
#define UPPER_AppearFrame	6

#define UPPER_IdleWidth		124
#define UPPER_IdleHeight	29
#define UPPER_IdleY			UPPER_AppearY + UPPER_AppearHeight
#define UPPER_IdleFrame		4

#define UPPER_MoveWidth		384
#define UPPER_MoveHeight	28
#define UPPER_MoveY			UPPER_IdleY + UPPER_IdleHeight
#define UPPER_MoveFrame		12

#define UPPER_JumpWidth		160
#define UPPER_JumpHeight	35
#define UPPER_JumpY			UPPER_MoveY + UPPER_MoveHeight
#define UPPER_JumpFrame		6

#define UPPER_JumpMoveWidth		160
#define UPPER_JumpMoveHeight	35
#define UPPER_JumpMoveY			UPPER_JumpY + UPPER_JumpHeight
#define UPPER_JumpMoveFrame		6

#define UPPER_SitWidth			116
#define UPPER_SitHeight			41
#define UPPER_SitY				UPPER_JumpMoveY + UPPER_JumpMoveHeight
#define UPPER_SitFrame			4

#define UPPER_SitIdleWidth		124
#define UPPER_SitIdleHeight		27
#define UPPER_SitIdleY			UPPER_SitY + UPPER_SitHeight
#define UPPER_SitIdleFrame		4

#define UPPER_SitMoveWidth		245
#define UPPER_SitMoveHeight		24
#define UPPER_SitMoveY			UPPER_SitIdleY + UPPER_SitIdleHeight
#define UPPER_SitMoveFrame		7


#define UPPER_AttWidth			520
#define UPPER_AttHeight			29
#define UPPER_AttY				UPPER_SitMoveY + UPPER_SitMoveHeight
#define UPPER_AttFrame			10

#define UPPER_Att90Width		290
#define UPPER_Att90Height		66
#define UPPER_Att90Y			UPPER_AttY + UPPER_AttHeight
#define UPPER_Att90Frame		10

#define UPPER_Att180Width		240
#define UPPER_Att180Height		24
#define UPPER_Att180Y			UPPER_Att90Y + UPPER_Att90Height
#define UPPER_Att180Frame		4

#define UPPER_AttSitWidth		520
#define UPPER_AttSitHeight		29
#define UPPER_AttSitY			UPPER_Att180Y + UPPER_Att180Height
#define UPPER_AttSitFrame		10

#define UPPER_Att270Width		138
#define UPPER_Att270Height		54
#define UPPER_Att270Y			UPPER_AttSitY + UPPER_AttSitHeight
#define UPPER_Att270Frame		6

	/*
	UPPER_Att90,
	UPPER_Att180,
	UPPER_AttSit,
	UPPER_Att270,
	UPPER_Knife,
	UPPER_KnifeSit
	*/


// 하체
#define LOWER_IdleWidth			84
#define LOWER_IdleHeight		16
#define LOWER_IdleY				1450
#define LOWER_IdleFrame			4

#define LOWER_MoveWidth			372
#define LOWER_MoveHeight		20
#define LOWER_MoveY				1466
#define LOWER_MoveFrame			12

#define LOWER_JumpWidth			126
#define LOWER_JumpHeight		24
#define LOWER_JumpY				1486
#define LOWER_JumpFrame			6

#define LOWER_JumpMoveWidth		198
#define LOWER_JumpMoveHeight	21
#define LOWER_JumpMoveY			1510
#define LOWER_JumpMoveFrame		6

	// 상체 (Y 시작좌표)
	enum ACT_UPPER
	{
		UPPER_Appear,		// 등장 186(31*240),		6FR
		UPPER_Idle,			// 대기 124(31*29),		4FR
		UPPER_Move,			// 이동 384(32*28),		12FR
		UPPER_Jump,			// 점프 160(32*35),		6FR
		UPPER_JumpMove,		// 점프 이동 160(32*35),	6FR

		UPPER_Sit,			// 앉기 116(29*41),		4FR
		UPPER_SitIdle,		// 앉아 대기 124(31*27),	4FR
		UPPER_SitMove,		// 앉아 이동 245(35*24),	7FR
		
		UPPER_Att,			// 공격 520(52*29),			10FR
		UPPER_Att90,		// 공격 90도 290(29*66),		10FR
		UPPER_Att180,		// 공격 180도 240(60*24),	4FR
		UPPER_AttSit,		// 앉아 공격 520(52*29),		10FR
		UPPER_Att270,		// 공격 270도 138(23*54),	6FR
		UPPER_Knife,		// 칼질 264(44*48),			6FR
		UPPER_KnifeSit,		// 앉아 칼질 168(42*35),		4FR

		UPPER_GunIdle,		// 무기 대기 152(38*29),		4FR
		UPPER_GunMove,		// 무기 이동 516(43*31),		12FR
		UPPER_GunSit,		// 무기 앉기 156(39*42),		4FR
		UPPER_GunSitIdle,	// 무기 앉아 대기 164(41*24),	4FR
		UPPER_GunSitMove,	// 무기 앉아 이동 287(41*24),	7FR

		UPPER_GunAtt,		// 무기 공격 240(60*28),			4FR
		UPPER_GunAtt270,	// 무기 공격 270도 324(81*27),	4FR
		// 무기 공격 (중간에서 위) 이후 작성 필요
	};

	// 하체
	enum ACT_LOWER
	{
		LOWER_NULL,			// 하체 출력 안 함
		LOWER_Idle,			// 대기 84(21*16),		4FR
		LOWER_Move,			// 이동 372(31*20),		12FR
		LOWER_Jump,			// 점프 126(21*24),		6FR
		LOWER_JumpMove,		// 점프 이동 198(33*21),	6FR
	};
	
	enum DIR
	{
		DIR_Right,
		DIR_Left,
		DIR_Up,
		DIR_Down,
	};

	struct TagImg
	{
		image *		pImg;
		image *		pImgReverse;
		animation *	pAni;
		RECT		rc;
	};

private:
	missileManager*	m_pMissileMgr;

	TagImg		m_upper;
	TagImg		m_lower;

	ACT_UPPER	m_ACT_UPPER;
	ACT_LOWER	m_ACT_LOWER;

	float	m_fReplaceY;
	float	m_fSpeed;
	float	m_fJumpSpeed;
	float	m_fGravity;

	short	m_nActUpper;	// 상체 행동
	short	m_nActLower;	// 하체 행동
	short	m_nDir;			// 캐릭터가 바라보는 방향 (좌우)
	short	m_nDirY;		// 캐릭터가 바라보는 방향 (상하)

	bool	m_isAct;		// 행동을 했는지 안 했는지 확인
	bool	m_isAlive;		// 생존여부

public:
	HRESULT init(float x, float y);
	void update();
	void actSet();
	void move();
	void release();
	void render(HDC hdc);

	inline RECT getRectUpper() { return m_upper.rc; }
	inline RECT getRectLower() { return m_lower.rc; }

	player();
	~player();
};