#pragma once

class missile;
class missileManager;

enum state {
	NOMAL,			// �븻 ����
	CHANGE,			// ���� ����
	RAGE			// �г� ����
};



enum pattern {
	MOVE,			// ���� ���� �̵�
	IDLEMOVE,		// �������� �̵�
	S_BACKMOVE,		// �� ���� �̵�
	S_RUSHMOVE,		// ���ϰ� �뽬 �̵�
	P_RUSHMOVE,		// ���ϰ� �뽬 �̵�
	BULLET_SHOOT	// ���� ��� 
};

enum bullet {
	NOMAL_BULLET,	// �븻 �Ѿ�
	CANNON_BULLET	// ���� �Ѿ�
};

struct B_pcount {
	int index = 0;
	int count = 0;
};



class boss
{
private:


	//���� �ִϸ��̼�
	image *		m_pimgBoss;
	animation*	m_pMoveAni;		// IDLE �� �⺻ �̵�
	animation*	m_pBossFire;	// IDLE �� �⺻ �̵�
	animation*	m_pBossCfire;	// IDLE �� �⺻ �̵�

	animation*	m_pChangeBoss;	// ���� �����̹��� 
	animation*  m_pRageBoss;	// ���� �г���
	animation*	m_pDieAni;		// ���� ����

	//���� ����Ʈ �ִϸ��̼�
	image *		 m_pimgeffect;
	animation*	 m_pmoveEffect;

	RECT		m_rc;

	B_pcount	b_attack;		//���� ���� ī����
	B_pcount	b_pattern;		//�����̴� ����
	B_pcount	b_change;		//���� ī����
	B_pcount	b_moveeffect;	// �̵� ����Ʈ ī����
	B_pcount	b_smoveeffect;	// �̵� ����Ʈ ī����2
	B_pcount	b_nomaleffect;	// �븻 bullet ī����
	B_pcount	b_rageefect;	// �г� bullet ī����

	state		m_state;		// ������ ���¸� ���� ����
	pattern		m_pattern;		// ������ ���� ������ �޴� ����
	bullet		m_bullet;		// ������ ���� �Ѿ� ���¸� �˷��ִ� ����

	float		m_fSpeed;
	float		m_upspeed;

	float		m_fX;
	float		m_fY;
	float		m_fAngle;
	

	int			m_nCurrFrameX;
	int			m_nCurrFrameY;

	int		m_pattonChack; // Ư�� ���� üũ

	bool m_isChange;
	bool m_isAppear;
	bool m_isAlive;
	bool m_isShoot;

	// �̻��� �Ŵ���
	missileManager*	m_pmissileManager;
	

	int				m_nCurrHP;
	int				m_nMaxHP;

	

	// Ÿ��
	/*	�÷��̾�Ŭ����*	m_pTarget;*/
public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	void fire();
	void shoot();
	void move();
	void change(bool ischange);

	void ani_moveeffect();
	void ani_smoveeffect();
	void ani_nomalshoot();
	void ani_rageshoot();
	void damaged(int damage);
	void diechack();

	inline RECT getRect() { return m_rc; }
	inline float getX() { return m_fX; }
	inline float getY() { return m_fY; }
	inline void setY(float y) { m_fY = y; }
	inline missileManager* getMissileMgr() { return m_pmissileManager     ; }
	

	//inline progressBar* getHPBar() { return m_pHPBar; }
	inline void setCurrHP(int hp) { m_nCurrHP = hp; }

	inline void setisAlive(bool isAlive) { m_isAlive = isAlive; }
	inline bool getisAlive() { return m_isAlive; }
	//inline void damaged(int damage) { m_nCurrHP -= damage; }
	
	boss();
	~boss();
};

