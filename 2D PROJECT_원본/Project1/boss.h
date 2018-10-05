#pragma once

class missile;
class missileManager;

enum state {
	NOMAL,
	RAGE
};

enum pattern {
	IDLE,
	ATTACK,
	DOUBLEFIRE,
	CANNFIRE,
	DIE
};

enum movebing {
	MOVE, // 제라리 걸음 이동
	IDLEMOVE, // 원점으로 이동
	SMALLMOVE, // 약간 약진 이동
	RUSHMOVE, // 대쉬 이동
	BACKMOVE
};



class boss
{
private:


	
	image * m_pimgBoss;
	animation* m_pMoveAni;

	image * m_pimgbossatk;
	animation* m_pAttackAni;


	RECT	m_rc;
	float	m_fSpeed;
	float m_upspeed;

	float	m_fX;
	float	m_fY;

	int		m_nCurrFrameX;
	int		m_nCurrFrameY;
	int		m_nCount;


	// 미사일 매니저
	missileManager*	m_pMissileMgr;
	int				m_nFireCount;
	int				m_nRandFireCount;

	int				m_nCurrHP;
	int				m_nMaxHP;

	state			m_state;	// 보스의 상태를 위한 변수
	pattern			m_pattern;	// 보스의 패턴을  받는 변수
	movebing		m_move;		// 보스으 무브 패턴을 받는 변수


	bool m_isAppear;
	bool m_isAlive;
	// 타겟
	/*	플레이어클래스*	m_pTarget;*/
public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	void move();

	inline RECT getRect() { return m_rc; }
	inline float getX() { return m_fX; }
	inline float getY() { return m_fY; }
	inline void setY(float y) { m_fY = y; }
	inline missileManager* getMissileMgr() { return m_pMissileMgr; }
	

	//inline progressBar* getHPBar() { return m_pHPBar; }
	inline void setCurrHP(int hp) { m_nCurrHP = hp; }

	inline void setisAlive(bool isAlive) { m_isAlive = isAlive; }
	inline bool getisAlive() { return m_isAlive; }
	//inline void damaged(int damage) { m_nCurrHP -= damage; }
	void damaged(int damage);
	void diechack();
	boss();
	~boss();
};

