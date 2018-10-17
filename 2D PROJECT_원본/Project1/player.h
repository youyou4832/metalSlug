#pragma once
class missileManager;

class player
{
			/*
			186(31)-240 6�� ĳ���� ���� 0-
			124* 29(4��) ĳ���� �⺻ ����  0-
			384(32)- 28 12�� ĳ���� ��ݽ� �޸��� 0-
			160(32) -35 6�� ĳ���� ���� ��ݽ�	0-
			160(32)-35 6�� ĳ���� ������ ���� ��ݽ� 0-

			87(29)- 41 3��  ĳ���� �ɱ� ��� 0-
			124(31)-27 4�� ĳ���� ���� ���� ��� ��� 0-
			245(35)-24 7��  ĳ���� �ɾƼ� �̵� 0-

			520(52) - 29 10��	ĳ���� �⺻ ���� ��� �ϼ��� 0-
			290(29)-66 10�� ĳ���� �⺻���� �� ���� 0-
			240(60)*24 4�� ĳ���� ���� ���� 0-
			520(52)-29 10�� ĳ���� ���� ���� �⺻ ����0-
			138(23)*54 6�� ĳ���� ���� �Ʒ� ����	0-
			6*(44) * 48 6��ĳ���� �⺻ �������� ��� 0-
			168(42)-35 4�� ĳ���� �ɾƼ� ���� ���� 0-

			152(38)-29 ĳ���� ���� �⺻ ����	0-
			516(43)-31 12�� ĳ���� ���� �̵�	0-
			117(39)- 42 3�� ĳ���� ���� �ɱ� ��� 0-
			164(41)-24 4ĳ���� ���� ���� ���� ��� ���	0-
			287(41)-24 7�� ĳ���� ���� �ɾƼ� �̵�	0-

			240(60)-28 4�� ĳ���� ���� ����	0-
			324(81)-27 4�� ĳ���� ���� ���� ����	0-
			110(55)-58 2�� ĳ���� ���� ����(�߰����� ��)	0-
			96(24)-72 4�� ĳ���� ���� �� ���� 		0-
			110(55)-63 2�� ĳ���� ���� ����(������ �Ʒ�)	0-

			104(52)-58 2�� ĳ���� ���� ���� (�߰�����  �Ʒ�)	0-
			136(34)-64 4�� ĳ���� ���� �Ʒ� ����			0-
			104(52)-59 2�� ĳ���� ���� ����(�Ʒ����� ��)		0-

			156(78)-61 2�� ĳ���� ���� ���� ����(�߰����� �Ʒ�)	0-
			154(77)-61 2�� ĳ���� ���� ���� ����(�Ʒ����� ��)	0-
			268(67)-28 4�� ĳ���� ���� �ɾƼ� ����			0-

			198(33)-29 6�� ĳ���� �⺻ ��ź ������		0-
			246(41)-28 6�� ĳ���� �⺻ �ɾƼ� ��ź ������	0-
			240(40) - 29ĳ���� ����� ��ź ����		0-
			264(44) - 36ĳ���� ����� �ɾƼ� ��ź		0-

			330(55)-42_ĳ���� ����� ���� ����		0-
			360(60)-33 ĳ���� ����� �ɾ� ���� ����		0-
			384(32)-34 ĳ���� ������ Ż��			0-

			931(49)-44 19��ĳ���� ����1		0-

			84(21)* 16 (4��) ĳ���� ��� �� ���  0-
			372(31)- 20 12�� ĳ���� �޸��� �Ϲݽ� 0-
			126(26)-24 6�� ���ڸ� ���� �Ϲݽ�	0-
			198(33)-21 6�� ĳ���� �Ϲݽ� �� ����	0-
			*/

	/*
	�÷��̾� ��ü �߽��� / �÷��̾� ��ü �߽����� init�� �� �ȼ� ��ĵ�ؼ� �迭�� ����
	�̹����� ����� �� �ش� �߽����� �������� ���
		=> ���ҽ� ������ �ð��� ���� �ɷ� �Ұ���
		   ��Ǹ��� �߽���(���) ��ġ�� ���� �޶� �ȼ� ��ĵ�� ���� ���ҽ� �۾��� �ٽ� �Ϸ��� �ð��� �ʹ� �����ɸ�
	*/ 

// ��ü
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
#define UPPER_GunAtt90Y			UPPER_GunAttY + UPPER_GunAttHeight + 27				// ���� ���� ����
#define UPPER_GunAtt90Frame		8

#define UPPER_GunAtt270Width	272
#define UPPER_GunAtt270Height	64
#define UPPER_GunAtt270Y		UPPER_GunAtt90Y + UPPER_GunAtt90Height
#define UPPER_GunAtt270Frame	8

#define UPPER_GunAttSitWidth	268
#define UPPER_GunAttSitHeight	28
#define UPPER_GunAttSitY		UPPER_GunAtt270Y + UPPER_GunAtt270Height + 61		// ���� �߰�->�Ʒ�
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

// ��ü
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

// �÷��̾� �浹 ��Ʈ ������
#define PLAYER_RectWidth		60
#define PLAYER_RectHeight		100

	// ��ü (Y ������ǥ)
	enum ACT_UPPER
	{
		UPPER_Appear,		// ���� 186(31*240),		6FR
		UPPER_Idle,			// ��� 124(31*29),			4FR
		UPPER_Move,			// �̵� 384(32*28),			12FR
		UPPER_Jump,			// ���� 160(32*35),			6FR
		UPPER_JumpMove,		// ���� �̵� 160(32*35),	6FR

		UPPER_Sit,			// �ɱ� 116(29*41),			4FR
		UPPER_SitIdle,		// �ɾ� ��� 124(31*27),	4FR
		UPPER_SitMove,		// �ɾ� �̵� 245(35*24),	7FR
		
		UPPER_Att,			// ���� 520(52*29),			10FR
		UPPER_Att90,		// ���� 90�� 290(29*66),	10FR
		UPPER_Att180,		// ���� 180�� 240(60*24),	4FR
		UPPER_AttSit,		// �ɾ� ���� 520(52*29),	10FR
		UPPER_Att270,		// ���� 270�� 138(23*54),	6FR
		UPPER_Knife,		// Į�� 264(44*48),			6FR
		UPPER_KnifeSit,		// �ɾ� Į�� 168(42*35),	4FR

		UPPER_GunIdle,		// ���� ��� 152(38*29),		4FR
		UPPER_GunMove,		// ���� �̵� 516(43*31),		12FR
		UPPER_GunSit,		// ���� �ɱ� 156(39*42),		4FR
		UPPER_GunSitIdle,	// ���� �ɾ� ��� 164(41*24),	4FR
		UPPER_GunSitMove,	// ���� �ɾ� �̵� 287(41*24),	7FR

		UPPER_GunAtt,		// ���� ���� 240(60*28),		4FR
		UPPER_GunAtt270,	// ���� ���� 270�� 324(81*27),	4FR
		// �߰����� ��, ������ �Ʒ�, �߰����� �Ʒ�, �Ʒ����� ��, ���ʰ��� ����
		UPPER_GunAtt90,		// ���� ���� 90�� 96(24*72),	4FR
		UPPER_GunAttSit,	// ���� �ɾ� ���� 268(67*28),	4FR

		UPPER_Bomb,			// ��ź ���� 198(33*29),		6FR
		UPPER_BombSit,		// �ɾ� ��ź 246(41*28),		6FR
		UPPER_BombGun,		// ���� ��ź 240(40*29),		6FR
		UPPER_BombGunSit,	// ���� �ɾ� ��ź 264(44*36),	6FR

		UPPER_KnifeGun,		// ���� Į�� 330(55*42),		6FR
		UPPER_KnifeGunSit,	// ���� �ɾ� Į�� 360(60*33),	6FR
		
		UPPER_SlugEscape,	// ������ Ż�� 384(32*34),		12FR
		UPPER_Death,		// ���� 931(49*44),				19FR
	};

	// ��ü
	enum ACT_LOWER
	{
		LOWER_NULL,			// ��ü ��� �� ��
		LOWER_Idle,			// ��� 84(21*16),			4FR
		LOWER_Move,			// �̵� 372(31*20),			12FR
		LOWER_Jump,			// ���� 126(21*24),			6FR
		LOWER_JumpMove,		// ���� �̵� 198(33*21),	6FR
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
		image *		pImg;			// ������ ���
		image *		pImgReverse;	// ������ ���
		animation *	pAni;			// �ִϸ��̼�
		RECT		rc;				// �浹 RECT
	};

private:
	missileManager*	m_pMissileMgr;

	TagImg		m_upper;
	TagImg		m_lower;

	ACT_UPPER	m_ACT_UPPER;
	ACT_LOWER	m_ACT_LOWER;

	RECT	m_rcHit;			// ��Ʈ �ڽ� (�÷��̾ ���� ���ϴ� RECT)
	RECT	m_rcAtt;			// ���� �ڽ� (�÷��̾��� ������ �߻�Ǵ� ��ġ�� RECT)
	float	m_fAttX;			// ���� �ڽ� X��ǥ (���� ���� �浹 Ȯ��, �Ѿ� �߻� ��ġ)
	float	m_fAttY;			// ���� �ڽ� Y��ǥ (���� ���� �浹 Ȯ��, �Ѿ� �߻� ��ġ)

	float	m_fReplaceY;		// ��ü Y��ǥ + ���ҽ� ��� ��ġ ����
	float	m_fReplaceLowerY;	// ��ü Y��ǥ + ���ҽ� ��� ��ġ ����
	float	m_fAttReplaceX;		// ���ùڽ� X, Y ��ǥ ����
	float	m_fAttReplaceY;		// ���ùڽ� X, Y ��ǥ ����
	float	m_fSpeed;
	float	m_fAngle;

	// ����
	float	m_fGravity;
	float	m_fJumpSpeed;
	float	m_fCurrHeight;
	float	m_fFloorHeight;	// �ٴ� ����
	bool	m_isJump;		// ���� ���ΰ�
	
	// ���
	short	m_nActUpper;	// ��ü �ൿ
	short	m_nActLower;	// ��ü �ൿ
	short	m_nDir;			// ĳ���Ͱ� �ٶ󺸴� ���� (�¿�)
	short	m_nDirY;		// ĳ���Ͱ� �ٶ󺸴� ���� (����)
	bool	m_isAct;		// �ൿ�� �ߴ��� �� �ߴ��� Ȯ��
	bool	m_isGun;		// ���� ��� �ִ°�
	bool	m_isAttack;		// �������ΰ�

	// enemy �Ǵ� map �浹���� �޾ƿ;� �ϴ� ����
	bool	m_isAlive;		// ��������
	bool	m_isCollide;	// �浹���� (���� ����)

	// ������
	bool	m_isSlugIn;		// �����׿� ž�� ���ΰ�
	bool	m_isSlugEscape;	// �����׿��� Ż�� �ϴ°� (true�̸� Ż�� ��� ����)

	// ������
	short	m_nBombNum;		// ��ź ����

public:
	HRESULT init(float x, float y);
	void update();
	void move();
	void release();
	void render(HDC hdc);

	// ĳ���� ���� ����� (2018.10.14 ���ۼ�)
	void dataSave();
	void dataLoad();

	// ĳ���� ����
	void actSet();		// ĳ���� ��� ���� ���� �Լ�
	void setUpper();	// ��ü
	void setLower();	// ��ü
	void setDir();		// ����

	// ĳ���� �ൿ (����)
	void fire();			// ���� �Ѱ� ���� �Լ�
	void fireActSet();		// ���� ��� ����
	void fireAttBoxSet();	// ���ùڽ� ����

	// ĳ���� ���ҽ� ��ġ ���� �Լ� (��Ǹ��� ������� ������ ��ǥ�� �޶� ������ ������ ����� ��)
	void setResourceRect();

	// update �ʹݿ� return�ϴ� ���๮�� �����ϴ� �Լ�
	bool isReturnUpdate();	// (�����ϴ� ���߿� / �׾��� �� / �����׿� ž������ �� / �����׿��� Ż���� ��)
	
	// Getter & Setter
	inline RECT	getRectUpper() { return m_upper.rc; }
	inline RECT	getRectLower() { return m_lower.rc; }
	inline RECT getRectAttBox() { return m_rcAtt; }		// AttBox�� ���� �浹���� ��� m_isscollide = true (��������)
	inline bool getIsAttack() { return m_isAttack; }	// �÷��̾ ���������� üũ

	inline void setIsAlive(bool isAlive) { m_isAlive = isAlive; }
	inline void setCollide(bool isCollide) { m_isCollide = isCollide; }
	inline void setIsAttack(bool isAttack) { m_isAttack = isAttack; }


	player();
	~player();
};