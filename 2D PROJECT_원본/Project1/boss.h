#pragma once

class missile;
class missileManager;

enum state {
	NOMAL,			// 노말 상태
	CHANGE,			// 변신 상태
	RAGE			// 분노 상태
};



enum pattern {
	MOVE,			// 제라리 걸음 이동
	IDLEMOVE,		// 원점으로 이동
	S_BACKMOVE,		// 약 후진 이동
	S_RUSHMOVE,		// 약하게 대쉬 이동
	P_RUSHMOVE,		// 강하게 대쉬 이동
	BULLET_SHOOT	// 총을 쏜다 
};

enum bullet {
	NOMAL_BULLET,	// 노말 총알
	CANNON_BULLET	// 대포 총알
};

struct B_pcount {
	int index = 0;
	int count = 0;
};



class boss
{
private:


	//보스 애니메이션
	image *		m_pimgBoss;
	animation*	m_pMoveAni;		// IDLE 및 기본 이동	 애니메이션
	animation*	m_pBossFire;	// nomalboss bullet 공격 애니메이션
	animation*	m_pBossCfire;	//  rage boss 공격 애니메이션

	animation*	m_pChangeBoss;	// 보스 변신이미지 
	animation*  m_pRageBoss;	// 보스 분노모드
	animation*	m_pDieAni;		// 보스 죽음

	//보스 이펙트 애니메이션
	image *		 m_pimgeffect;	// 보스 이펙트 이미지를 담을 클래스 변수 
	

	RECT		m_rc;

	B_pcount	b_attack;		//공격 패턴 카운터
	B_pcount	b_pattern;		//움직이는 패턴
	B_pcount	b_change;		//변신 카운터
	B_pcount	b_moveeffect;	// 이동 이펙트 카운터
	B_pcount	b_smoveeffect;	// 이동 이펙트 카운터2
	B_pcount	b_nomaleffect;	// 노말 bullet 카운터
	B_pcount	b_rageefect;	// 분노 bullet 카운터

	state		m_state;		// 보스의 상태를 위한 변수
	pattern		m_pattern;		// 보스의 무브 패턴을 받는 변수
	bullet		m_bullet;		// 보스의 현재 총알 상태를 알려주는 변수

	float		m_fSpeed;		//보스 스피드
	float		m_upspeed;		//보스가 등장할때 점점 빠르게 등장하기 보이기 위해서 사용

	float		m_fX;			//보스 현재 X위치
	float		m_fY;			//보스 현재 Y위치
	float		m_fAngle;
	

	int			m_nCurrFrameX;
	int			m_nCurrFrameY;

	int		m_pattonChack;		// 특정 패턴 체크

	bool m_isChange;			//보스 변신 유무를 하기위한 변수
	bool m_isAppear;			//보스 등장씬 유무를 확인하기 위한 변수
	bool m_isAlive;				//보스가 살아있는지를 확인하기 위한 변수
	bool m_isShoot;				//보스가 총알을 솼는지 확인하기 위한 변수

	// 미사일 매니저
	missileManager*	m_pmissileManager;
	
	int				m_nCurrHP;		//보스 현재 hp
	int				m_nMaxHP;		//보스 max hp

	

	// 타겟
	/*	플레이어클래스*	m_pTarget;*/

public:
	HRESULT init();				
	void release();			
	void update();
	void render(HDC hdc);

	void fire();				//bullet 시레 발사하는 함수
	void shoot();				//bullet 발사 위해 체크 하는 함수
	void move();				//보스의 동작을 위한 함수
	void change(bool ischange);		//보스 변신씬을 체크하는 함수

	void ani_moveeffect();		//boss 움직이는 이펙트 에니메이션 동작을 위한 함수
	void ani_smoveeffect();		//boss 움직이는 이펙트 에니메이션 동작을 위한 함수2
	void ani_nomalshoot();		//boss nomal bullet 이펙트 에니메이션 동작을 위한 함수
	void ani_rageshoot();		//boss cannon bullet 이펙트 에니메이션 동작을 위한 함수

	void damaged(int damage);	// boss에 hp를 감소하는 함수
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

