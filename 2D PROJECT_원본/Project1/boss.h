#pragma once

class missile;
class missileManager;

enum BOSS_STATE{
	NOMAL,			// �븻 ����
	CHANGE,			// ���� ����
	RAGE			// �г� ����
};



enum PATTERN_STATE {
	MOVE,			// ���� ���� �̵�
	IDLEMOVE,		// �������� �̵�
	S_BACKMOVE,		// �� ���� �̵�
	S_RUSHMOVE,		// ���ϰ� �뽬 �̵�
	P_RUSHMOVE,		// ���ϰ� �뽬 �̵�
	BULLET_SHOOT	// ���� ��� 
};

enum BULLET_STATE {
	NOMAL_BULLET,	// �븻 �Ѿ�
	RAGE_BULLET	// ���� �Ѿ�
};

struct PatternDelay {
	int index = 0;
	int count = 0;
};


class boss
{
private:

	//���� �ִϸ��̼�
	image *		m_pimgBoss;
	animation*	m_pMoveAni;		// IDLE �� �⺻ �̵�	 �ִϸ��̼�
	animation*	m_pNomalFireAni;	// nomalboss bullet ���� �ִϸ��̼�
	animation*	m_pRageFireAni;	//  rage boss ���� �ִϸ��̼�

	animation*	m_pChangeBossAni;	// ���� �����̹��� 
	animation*  m_pRageBossAni;	// �г� ��� ���� IDLE �� �̵� �ִϸ��̼�
	animation*	m_pDieAni;		// ���� �״� �ִϸ��̼�

	//���� ����Ʈ �ִϸ��̼�
	image *		 m_pimgeffect;	// ���� ����Ʈ �̹����� ���� Ŭ���� ���� 
	
	RECT		m_rc;

	PatternDelay	m_NextMoveDelay;	//�����̴� ����
	PatternDelay	m_ChangeDelay;		//���� ī����
	PatternDelay	m_EffectAniCount;	// �̵� ����Ʈ ī����
	PatternDelay	m_EffectAniCount2;	// �̵� ����Ʈ ī����2
	PatternDelay	m_NomalEffectDelay;	// �븻 bullet ī����
	PatternDelay	m_RageFireAinCount;	// �г� bullet ī����

	BOSS_STATE		m_BossState;	// ������ ���¸� ���� ����
	PATTERN_STATE	m_PatternState;		// ������ ���� ������ �޴� ����
	BULLET_STATE	m_BulletState;		// ������ ���� �Ѿ� ���¸� �˷��ִ� ����

	float		m_Speed;		//���� ���ǵ�
	float		m_AppearSpeed;		//������ �����Ҷ� ���� ������ �����ϱ� ���̱� ���ؼ� ���

	float		m_fX;			//���� ���� X��ġ
	float		m_fY;			//���� ���� Y��ġ
	float		m_fAngle;
	
	int		m_pattonChack;		// Ư�� ���� üũ

	bool m_isChange;			//���� ���� ������ �ϱ����� ����
	bool m_isAppear;			//���� ����� ������ Ȯ���ϱ� ���� ����
	bool m_isAlive;				//������ ����ִ����� Ȯ���ϱ� ���� ����
	bool m_isShoot;				//������ �Ѿ��� ������ Ȯ���ϱ� ���� ����

	// �̻��� �Ŵ���
	missileManager*	m_pmissileManager;
	
	int				m_nCurrHP;		//���� ���� hp
	int				m_nMaxHP;		//���� max hp

	float getTimeCount;

	// Ÿ��
	/*	�÷��̾�Ŭ����*	m_pTarget;*/

public:
	HRESULT init();				
	void release();			
	void update();
	void render(HDC hdc);

	void fire();				//bullet �÷� �߻��ϴ� �Լ�
	void shoot();				//bullet �߻� ���� üũ �ϴ� �Լ�
	void move();				//������ ������ ���� �Լ�
	void change(bool ischange);		//���� ���ž��� üũ�ϴ� �Լ�
	void damaged(int damage);	// boss�� hp�� �����ϴ� �Լ�
	
	void Boss_MoveEffectAniCount();		//boss �����̴� ����Ʈ ���ϸ��̼� ������ ���� �Լ�
	void Boss_MoveEffectAniCount2();	//boss �����̴� ����Ʈ ���ϸ��̼� ������ ���� �Լ�2
	void Boss_FireEffectAniCount();		//boss nomal bullet ����Ʈ ���ϸ��̼� ������ ���� �Լ�
	void Boss_FireEffectAniCount2();	//boss cannon bullet ����Ʈ ���ϸ��̼� ������ ���� �Լ�

	//get & set �Լ�
	float getX() { return m_fX; }
	void setX(float x) { m_fY = x; }

	float getY() { return m_fY; }
	void setY(float y) { m_fY = y; }

	
	RECT getRect() { return m_rc; }

	inline missileManager* getMissileMgr() { return m_pmissileManager; }
	

	//inline progressBar* getHPBar() { return m_pHPBar; }
	inline void setCurrHP(int hp) { m_nCurrHP = hp; }

	inline void setisAlive(bool isAlive) { m_isAlive = isAlive; }
	inline bool getisAlive() { return m_isAlive; }
	//inline void damaged(int damage) { m_nCurrHP -= damage; }
	
	boss();
	~boss();
};

