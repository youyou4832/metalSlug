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

	/*
	플레이어 상체 중심점 / 플레이어 하체 중심점을 init할 때 픽셀 스캔해서 배열에 저장
	이미지를 출력할 때 해당 중심점을 기준으로 출력
		=> 리소스 문제로 시간이 많이 걸려 불가능
		   모션마다 중심점(배꼽) 위치가 전부 달라서 픽셀 스캔을 위해 리소스 작업을 다시 하려면 시간이 너무 오래걸림
	*/ 

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

#define UPPER_JumpWidth		192
#define UPPER_JumpHeight	35
#define UPPER_JumpY			UPPER_MoveY + UPPER_MoveHeight
#define UPPER_JumpFrame		6

#define UPPER_JumpMoveWidth		192
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

#define UPPER_KnifeWidth		264
#define UPPER_KnifeHeight		48
#define UPPER_KnifeY			UPPER_Att270Y + UPPER_Att270Height
#define UPPER_KnifeFrame		6

#define UPPER_KnifeSitWidth		168
#define UPPER_KnifeSitHeight	35
#define UPPER_KnifeSitY			UPPER_KnifeY + UPPER_KnifeHeight
#define UPPER_KnifeSitFrame		4

#define UPPER_GunIdleWidth		152
#define UPPER_GunIdleHeight		29
#define UPPER_GunIdleY			UPPER_KnifeSitY + UPPER_KnifeSitHeight
#define UPPER_GunIdleFrame		4

#define UPPER_GunMoveWidth		516
#define UPPER_GunMoveHeight		31
#define UPPER_GunMoveY			UPPER_GunIdleY + UPPER_GunIdleHeight
#define UPPER_GunMoveFrame		12

#define UPPER_GunSitWidth		156
#define UPPER_GunSitHeight		42
#define UPPER_GunSitY			UPPER_GunMoveY + UPPER_GunMoveHeight
#define UPPER_GunSitFrame		4

#define UPPER_GunSitIdleWidth	164
#define UPPER_GunSitIdleHeight	24
#define UPPER_GunSitIdleY		UPPER_GunSitY + UPPER_GunSitHeight
#define UPPER_GunSitIdleFrame	4

#define UPPER_GunSitMoveWidth	287
#define UPPER_GunSitMoveHeight	24
#define UPPER_GunSitMoveY		UPPER_GunSitIdleY + UPPER_GunSitIdleHeight
#define UPPER_GunSitMoveFrame	7

#define UPPER_GunAttWidth		480
#define UPPER_GunAttHeight		28
#define UPPER_GunAttY			UPPER_GunSitMoveY + UPPER_GunSitMoveHeight
#define UPPER_GunAttFrame		8

#define UPPER_GunAtt90Width		192
#define UPPER_GunAtt90Height	72
#define UPPER_GunAtt90Y			UPPER_GunAttY + UPPER_GunAttHeight + 27				// 무기 왼쪽 생략
#define UPPER_GunAtt90Frame		8

#define UPPER_GunAtt270Width	272
#define UPPER_GunAtt270Height	64
#define UPPER_GunAtt270Y		UPPER_GunAtt90Y + UPPER_GunAtt90Height
#define UPPER_GunAtt270Frame	8

#define UPPER_GunAttSitWidth	268
#define UPPER_GunAttSitHeight	28
#define UPPER_GunAttSitY		UPPER_GunAtt270Y + UPPER_GunAtt270Height + 61		// 왼쪽 중간->아래
#define UPPER_GunAttSitFrame	4

#define UPPER_BombWidth			198
#define UPPER_BombHeight		29
#define UPPER_BombY				UPPER_GunAttSitY + UPPER_GunAttSitHeight
#define UPPER_BombFrame			6

#define UPPER_BombSitWidth		246
#define UPPER_BombSitHeight		28
#define UPPER_BombSitY			UPPER_BombY + UPPER_BombHeight
#define UPPER_BombSitFrame		6

#define UPPER_BombGunWidth		240
#define UPPER_BombGunHeight		29
#define UPPER_BombGunY			UPPER_BombSitY + UPPER_BombSitHeight
#define UPPER_BombGunFrame		6

#define UPPER_BombGunSitWidth	264
#define UPPER_BombGunSitHeight	36
#define UPPER_BombGunSitY		UPPER_BombGunY + UPPER_BombGunHeight
#define UPPER_BombGunSitFrame	6

#define UPPER_KnifeGunWidth		330
#define UPPER_KnifeGunHeight	42
#define UPPER_KnifeGunY			UPPER_BombGunSitY + UPPER_BombGunSitHeight
#define UPPER_KnifeGunFrame		6

#define UPPER_KnifeGunSitWidth	360
#define UPPER_KnifeGunSitHeight	33
#define UPPER_KnifeGunSitY		UPPER_KnifeGunY + UPPER_KnifeGunHeight
#define UPPER_KnifeGunSitFrame	6

#define UPPER_SlugEscapeWidth	384
#define UPPER_SlugEscapeHeight	34
#define UPPER_SlugEscapeY		UPPER_KnifeGunSitY + UPPER_KnifeGunSitHeight
#define UPPER_SlugEscapeFrame	12

#define UPPER_DeathWidth		931
#define UPPER_DeathHeight		44
#define UPPER_DeathY			UPPER_SlugEscapeY + UPPER_SlugEscapeHeight
#define UPPER_DeathFrame		19

// 하체
#define LOWER_IdleWidth			84
#define LOWER_IdleHeight		16
#define LOWER_IdleY				1450
#define LOWER_IdleFrame			4

#define LOWER_MoveWidth			372
#define LOWER_MoveHeight		20
#define LOWER_MoveY				1466
#define LOWER_MoveFrame			12

#define LOWER_JumpWidth			138
#define LOWER_JumpHeight		24
#define LOWER_JumpY				1486
#define LOWER_JumpFrame			6 

#define LOWER_JumpMoveWidth		198
#define LOWER_JumpMoveHeight	21
#define LOWER_JumpMoveY			1510
#define LOWER_JumpMoveFrame		6

// 플레이어 충돌 렉트 사이즈
#define PLAYER_RectWidth		60
#define PLAYER_RectHeight		100

	// 상체 (Y 시작좌표)
	enum ACT_UPPER
	{
		UPPER_Appear,		// 등장 186(31*240),		6FR
		UPPER_Idle,			// 대기 124(31*29),			4FR
		UPPER_Move,			// 이동 384(32*28),			12FR
		UPPER_Jump,			// 점프 160(32*35),			6FR
		UPPER_JumpMove,		// 점프 이동 160(32*35),	6FR

		UPPER_Sit,			// 앉기 116(29*41),			4FR
		UPPER_SitIdle,		// 앉아 대기 124(31*27),	4FR
		UPPER_SitMove,		// 앉아 이동 245(35*24),	7FR
		
		UPPER_Att,			// 공격 520(52*29),			10FR
		UPPER_Att90,		// 공격 90도 290(29*66),	10FR
		UPPER_Att180,		// 공격 180도 240(60*24),	4FR
		UPPER_AttSit,		// 앉아 공격 520(52*29),	10FR
		UPPER_Att270,		// 공격 270도 138(23*54),	6FR
		UPPER_Knife,		// 칼질 264(44*48),			6FR
		UPPER_KnifeSit,		// 앉아 칼질 168(42*35),	4FR

		UPPER_GunIdle,		// 무기 대기 152(38*29),		4FR
		UPPER_GunMove,		// 무기 이동 516(43*31),		12FR
		UPPER_GunSit,		// 무기 앉기 156(39*42),		4FR
		UPPER_GunSitIdle,	// 무기 앉아 대기 164(41*24),	4FR
		UPPER_GunSitMove,	// 무기 앉아 이동 287(41*24),	7FR

		UPPER_GunAtt,		// 무기 공격 240(60*28),		4FR
		UPPER_GunAtt270,	// 무기 공격 270도 324(81*27),	4FR
		// 중간에서 위, 위에서 아래, 중간에서 아래, 아래에서 위, 왼쪽공격 생략
		UPPER_GunAtt90,		// 무기 공격 90도 96(24*72),	4FR
		UPPER_GunAttSit,	// 무기 앉아 공격 268(67*28),	4FR

		UPPER_Bomb,			// 폭탄 공격 198(33*29),		6FR
		UPPER_BombSit,		// 앉아 폭탄 246(41*28),		6FR
		UPPER_BombGun,		// 무기 폭탄 240(40*29),		6FR
		UPPER_BombGunSit,	// 무기 앉아 폭탄 264(44*36),	6FR

		UPPER_KnifeGun,		// 무기 칼질 330(55*42),		6FR
		UPPER_KnifeGunSit,	// 무기 앉아 칼질 360(60*33),	6FR
		
		UPPER_SlugEscape,	// 슬러그 탈출 384(32*34),		12FR
		UPPER_Death,		// 죽음 931(49*44),				19FR
	};

	// 하체
	enum ACT_LOWER
	{
		LOWER_NULL,			// 하체 출력 안 함
		LOWER_Idle,			// 대기 84(21*16),			4FR
		LOWER_Move,			// 이동 372(31*20),			12FR
		LOWER_Jump,			// 점프 126(21*24),			6FR
		LOWER_JumpMove,		// 점프 이동 198(33*21),	6FR
	};
	
	enum DIR
	{
		DIR_NULL,
		DIR_Right,
		DIR_Left,
		DIR_Up,
		DIR_Down,
	};

	struct TagImg
	{
		image *		pImg;			// 정방향 모션
		image *		pImgReverse;	// 역방향 모션
		animation *	pAni;			// 애니메이션
		RECT		rc;				// 충돌 RECT
	};

private:
	missileManager*	m_pMissileMgr;

	TagImg		m_upper;
	TagImg		m_lower;

	ACT_UPPER	m_ACT_UPPER;
	ACT_LOWER	m_ACT_LOWER;

	RECT	m_rcHit;			// 히트 박스 (플레이어가 공격 당하는 RECT)
	RECT	m_rcAtt;			// 어택 박스 (플레이어의 공격이 발사되는 위치의 RECT)
	float	m_fAttX;			// 어택 박스 X좌표 (적과 근접 충돌 확인, 총알 발사 위치)
	float	m_fAttY;			// 어택 박스 Y좌표 (적과 근접 충돌 확인, 총알 발사 위치)

	float	m_fReplaceY;		// 상체 Y좌표 + 리소스 출력 위치 수정
	float	m_fReplaceLowerY;	// 하체 Y좌표 + 리소스 출력 위치 수정
	float	m_fAttReplaceX;		// 어택박스 X, Y 좌표 수정
	float	m_fAttReplaceY;		// 어택박스 X, Y 좌표 수정
	float	m_fSpeed;
	float	m_fAngle;

	// 점프
	float	m_fGravity;
	float	m_fJumpSpeed;
	float	m_fCurrHeight;
	float	m_fFloorHeight;	// 바닥 높이
	bool	m_isJump;		// 점프 중인가
	
	// 모션
	short	m_nActUpper;	// 상체 행동
	short	m_nActLower;	// 하체 행동
	short	m_nDir;			// 캐릭터가 바라보는 방향 (좌우)
	short	m_nDirY;		// 캐릭터가 바라보는 방향 (상하)
	bool	m_isAct;		// 행동을 했는지 안 했는지 확인
	bool	m_isGun;		// 총을 들고 있는가
	bool	m_isAttack;		// 공격중인가

	// enemy 또는 map 충돌에서 받아와야 하는 정보
	bool	m_isAlive;		// 생존여부
	bool	m_isCollide;	// 충돌여부 (적과 근접)

	// 슬러그
	bool	m_isSlugIn;		// 슬러그에 탑승 중인가
	bool	m_isSlugEscape;	// 슬러그에서 탈출 하는가 (true이면 탈출 모션 적용)

	// 아이템
	short	m_nBombNum;		// 폭탄 갯수

public:
	HRESULT init(float x, float y);
	void update();
	void move();
	void release();
	void render(HDC hdc);

	// 캐릭터 정보 입출력 (2018.10.14 미작성)
	void dataSave();
	void dataLoad();

	// 캐릭터 세팅
	void actSet();		// 캐릭터 모션 세팅 관리 함수
	void setUpper();	// 상체
	void setLower();	// 하체
	void setDir();		// 방향

	// 캐릭터 행동 (공격)
	void fire();			// 공격 총괄 관리 함수
	void fireActSet();		// 공격 모션 세팅
	void fireAttBoxSet();	// 어택박스 세팅

	// 캐릭터 리소스 위치 수정 함수 (모션마다 사이즈와 기준점 좌표가 달라서 세팅을 별도로 해줘야 함)
	void setResourceRect();

	// update 초반에 return하는 실행문을 관리하는 함수
	bool isReturnUpdate();	// (등장하는 도중에 / 죽었을 때 / 슬러그에 탑승중일 때 / 슬러그에서 탈출할 때)
	
	// Getter & Setter
	inline RECT	getRectUpper() { return m_upper.rc; }
	inline RECT	getRectLower() { return m_lower.rc; }
	inline RECT getRectAttBox() { return m_rcAtt; }		// AttBox가 적과 충돌했을 경우 m_isscollide = true (근접공격)
	inline bool getIsAttack() { return m_isAttack; }	// 플레이어가 공격중인지 체크

	inline void setIsAlive(bool isAlive) { m_isAlive = isAlive; }
	inline void setCollide(bool isCollide) { m_isCollide = isCollide; }
	inline void setIsAttack(bool isAttack) { m_isAttack = isAttack; }


	player();
	~player();
};