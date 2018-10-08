#pragma once
class missileManager;

struct E_tagState {
	int index = 0;
	int count = 0;
	bool isState = false;
};
class enemy
{
private:
	image * m_pImg;
	RECT	m_rc;

	E_tagState s_Attack;
	E_tagState s_Death;
	E_tagState s_Hit;//샌드백 히트 애니
	E_tagState s_Idle;
	int deathCN = 0;
	bool firstBreak = false;
	bool secondBreak = false;

	int		m_nCurrFrameX;
	int		m_nCurrFrameY;
	int		m_nCount;
	int		m_CharNum;
	float	m_fX;
	float	m_fY;

	float m_destX;
	float m_destY;
	int m_destX2;
	int m_destY2;
	float m_fSpeed;
	float moveAngle;
	bool isAlive;

	// 미사일 매니저
	missileManager*	m_pMissileMgr;
	int				m_nFireCount;
	int				m_nRandFireCount;
	
	int m_currHP;
	int m_MaxHP;
	
	//static POINT position[5];
	//static int index;
public:
	HRESULT init();
	HRESULT init(const char* szFileName, POINT position, int destX, int destY, int speed, int charNum);
	void release();
	void update();
	void render(HDC hdc);
	void move();
	void fire();

	inline missileManager* getMissileMgr()
	{
		return m_pMissileMgr;
	}
	inline RECT getRect() { return m_rc; }
	//inline void setTarget(player* pTarget) { m_pTarget = pTarget; }
	inline bool getIsAlive() { return isAlive; }
	inline void setIsAlive(bool isalive) { isAlive = isalive; }

	void sniperAnimation();
	void sandBagAnimation();
	void sendBagHitAnimation();
	void cannonAnimation();
	void deathCount();

	enemy();
	~enemy();
};

