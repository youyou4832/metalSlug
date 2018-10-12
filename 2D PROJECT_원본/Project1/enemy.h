#pragma once
class missileManager;
class player;
struct E_tagState {
	int index = 0;
	int count = 0;
	bool isState = false;
};
class enemy
{
private:
	image * m_pImg;
	player * m_player;
	RECT	m_rc;

	E_tagState s_Attack;
	E_tagState s_Death;
	E_tagState s_Hit;//샌드백 히트 애니
	E_tagState s_Idle;
	E_tagState s_Move;
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

	bool firstMove = true;

	int MaxAttack;
	int AttackCount = 0;
	//노말 에너미
	bool checkMax = false;
	int AttackCN = 0;
	bool isDrawGun = false;
	bool isHaveGun = false;
	bool checkDistance = false;

	// 미사일 매니저
	missileManager*	m_pMissileMgr;
	int				m_nFireCount;
	int				m_nRandFireCount;
	
	int m_currHP;
	int m_MaxHP;
	
	//RECT playerRC;
	//static POINT position[5];
	//static int index;
public:
	HRESULT init();
	HRESULT init(const char* szFileName, POINT position, int destX, int destY, int speed, int charNum, player * player);
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
	void normalAnimation();
	void tankAnimation();
	void deathCount();
	
	inline void setCheckDistance() { checkDistance = true; }
	inline void setPlayerRect(player* player) { m_player = player; }

	enemy();
	~enemy();
};

