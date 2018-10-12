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
	animation*	m_pMoveAni;		// IDLE �� �⺻ �̵�	 �ִϸ��̼�
	animation*	m_pBossFire;	// nomalboss bullet ���� �ִϸ��̼�
	animation*	m_pBossCfire;	//  rage boss ���� �ִϸ��̼�

	animation*	m_pChangeBoss;	// ���� �����̹��� 
	animation*  m_pRageBoss;	// ���� �г���
	animation*	m_pDieAni;		// ���� ����

	//���� ����Ʈ �ִϸ��̼�
	image *		 m_pimgeffect;	// ���� ����Ʈ �̹����� ���� Ŭ���� ���� 
	

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

	float		m_fSpeed;		//���� ���ǵ�
	float		m_upspeed;		//������ �����Ҷ� ���� ������ �����ϱ� ���̱� ���ؼ� ���

	float		m_fX;			//���� ���� X��ġ
	float		m_fY;			//���� ���� Y��ġ
	float		m_fAngle;
	

	int			m_nCurrFrameX;
	int			m_nCurrFrameY;

	int		m_pattonChack;		// Ư�� ���� üũ

	bool m_isChange;			//���� ���� ������ �ϱ����� ����
	bool m_isAppear;			//���� ����� ������ Ȯ���ϱ� ���� ����
	bool m_isAlive;				//������ ����ִ����� Ȯ���ϱ� ���� ����
	bool m_isShoot;				//������ �Ѿ��� ������ Ȯ���ϱ� ���� ����

	// �̻��� �Ŵ���
	missileManager*	m_pmissileManager;
	
	int				m_nCurrHP;		//���� ���� hp
	int				m_nMaxHP;		//���� max hp

	

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

	void ani_moveeffect();		//boss �����̴� ����Ʈ ���ϸ��̼� ������ ���� �Լ�
	void ani_smoveeffect();		//boss �����̴� ����Ʈ ���ϸ��̼� ������ ���� �Լ�2
	void ani_nomalshoot();		//boss nomal bullet ����Ʈ ���ϸ��̼� ������ ���� �Լ�
	void ani_rageshoot();		//boss cannon bullet ����Ʈ ���ϸ��̼� ������ ���� �Լ�

	void damaged(int damage);	// boss�� hp�� �����ϴ� �Լ�
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

