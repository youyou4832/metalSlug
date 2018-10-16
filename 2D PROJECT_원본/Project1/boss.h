#pragma once

class missile;
class missileManager;

enum BOSS_STATE{
	NOMAL,			// 노말 상태
	CHANGE,			// 변신 상태
	RAGE			// 분노 상태
};



enum PATTERN_STATE {
	MOVE,			// 제라리 걸음 이동
	IDLEMOVE,		// 원점으로 이동
	S_BACKMOVE,		// 약 후진 이동
	S_RUSHMOVE,		// 약하게 대쉬 이동
	P_RUSHMOVE,		// 강하게 대쉬 이동
	BULLET_SHOOT	// 총을 쏜다 
};

enum BULLET_STATE {
	NOMAL_BULLET,	// 노말 총알
	RAGE_BULLET	// 대포 총알
};

struct PatternDelay {
	int index = 0;
	int count = 0;
};


class boss
{
private:

	//보스 애니메이션
	image *		m_pimgBoss;
	animation*	m_pMoveAni;		// IDLE 및 기본 이동	 애니메이션
	animation*	m_pNomalFireAni;	// nomalboss bullet 공격 애니메이션
	animation*	m_pRageFireAni;	//  rage boss 공격 애니메이션

	animation*	m_pChangeBossAni;	// 보스 변신이미지 
	animation*  m_pRageBossAni;	// 분노 모드 보스 IDLE 및 이동 애니메이션
	animation*	m_pDieAni;		// 보스 죽는 애니메이션

	//보스 이펙트 애니메이션
	image *		 m_pimgeffect;	// 보스 이펙트 이미지를 담을 클래스 변수 
	
	RECT		m_rc;

	PatternDelay	m_NextPatternDelay;	//패턴 변환 딜레이
	PatternDelay	m_ChangeDelay;		//변신 딜레이 
	
	PatternDelay	m_AppearEffectAniCount;	// 등장 이펙트 카운터
	PatternDelay	m_AppearEffectAniCount2;	// 등장 이펙트 카운터

	PatternDelay	m_MoveEffectAniCount;	// 이동 이펙트 카운터
	PatternDelay	m_MoveEffectAniCount2;	// 이동 이펙트 카운터2
	

	PatternDelay	m_NomalEffectDelay;	// 노말상태 보스 bullet 
	PatternDelay	m_RageFireAinDelay;	// 분노상태 보스 bullet 

	BOSS_STATE		m_BossState;	// 보스의 상태를 위한 변수
	PATTERN_STATE	m_PatternState;		// 보스의 무브 패턴을 받는 변수
	BULLET_STATE	m_BulletState;		// 보스의 현재 총알 상태를 알려주는 변수

	int				m_nCurrHP;		//보스 현재 hp
	int				m_nMaxHP;		//보스 max hp
	int				m_pattonChack;		// 특정 패턴 체크

	
	float			m_Speed;		//보스 스피드
	float			m_AppearSpeed;	//보스 등장 스피드

	float			m_fX;			//보스 현재 X위치
	float			m_fY;			//보스 현재 Y위치
	float			m_fAngle;
	
	bool			m_iSstandBy;
	bool			m_isChange;			//보스 변신 유무를 하기위한 변수
	bool			m_isAppear;			//보스 등장씬 유무를 확인하기 위한 변수
	bool			m_isAlive;				//보스가 살아있는지를 확인하기 위한 변수

	// 미사일 매니저
	missileManager*	m_pmissileManager;

	// 타겟
	/*	플레이어클래스*	m_pTarget;*/

public:
	HRESULT init();				
	void release();			
	void update();
	void render(HDC hdc);

	void fire();				//bullet 시레 발사하는 함수
	void move();				//보스의 동작을 위한 함수
	void change(bool ischange);	//보스 변신씬을 체크하는 함수
	void damaged(int damage);	// boss에 hp를 감소하는 함수
	void AppearAndDie();
	
	void AppearEffectAniCount();	//boss 등장 씬 이펙트 애니메이션을 동작을 휘한 함수
	
	void MoveEffectAniCount();		//boss 움직이는 이펙트 에니메이션 동작을 위한 함수
	void MoveEffectAniCount2();	//boss 움직이는 이펙트 에니메이션 동작을 위한 함수2
	
	void FireEffectAniCount();		//boss nomal bullet 이펙트 에니메이션 동작을 위한 함수
	void FireEffectAniCount2();	//boss cannon bullet 이펙트 에니메이션 동작을 위한 함수

	//get & set 함수
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

