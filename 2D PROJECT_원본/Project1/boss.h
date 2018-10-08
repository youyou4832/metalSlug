#pragma once

class missile;
class missileManager;

enum state {
	NOMAL,
	CHANGE,
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
	S_BACKMOVE, // 약 후진 이동
	S_RUSHMOVE, // 약하게 대쉬 이동
	P_RUSHMOVE	// 강하게 대쉬 이동
};

struct B_pcount {
	int index = 0;
	int count = 0;
};



class boss
{
private:


	
	image *		m_pimgBoss;
	animation*	m_pMoveAni; // IDLE 및 기본 이동
	animation*	m_pBossFire; // IDLE 및 기본 이동
	animation*	m_pBossCfire; // IDLE 및 기본 이동

	animation*	m_pChangeBoss; // 보스 변신이미지 
	animation*  m_pRageBoss; // 보스 분노모드
	animation*	m_pDieAni; // 보스 죽음


	RECT		m_rc;

	B_pcount	b_attack; //공격 패턴 카운터
	B_pcount	b_pattern;	//움직이는 패턴
	B_pcount	b_change; //변신 카운터

	float		m_fSpeed;
	float		m_upspeed;

	float		m_fX;
	float		m_fY;
	float		m_fAngle;
	

	int			m_nCurrFrameX;
	int			m_nCurrFrameY;

	int		m_pattonChack; // 특정 패턴 체크

	bool m_isChange;
	bool m_isAppear;
	bool m_isAlive;

	// 미사일 매니저
	missileManager*	m_pmissileManager;
	

	int				m_nCurrHP;
	int				m_nMaxHP;

	state			m_state;	// 보스의 상태를 위한 변수
	pattern			m_pattern;	// 보스의 패턴을  받는 변수
	movebing		m_move;		// 보스으 무브 패턴을 받는 변수

	// 타겟
	/*	플레이어클래스*	m_pTarget;*/
public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	void fire();
	void move();
	void change(bool ischange);

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
	void damaged(int damage);
	void diechack();
	boss();
	~boss();
};

