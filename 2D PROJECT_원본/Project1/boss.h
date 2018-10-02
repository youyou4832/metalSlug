#pragma once
class image;
class missileManager;
class boss
{
private:
	image * m_pImg;
	RECT	m_rc;

	int		m_nCurrFrameX;
	int		m_nCurrFrameY;
	int		m_nCount;

	float	m_fX;
	float	m_fY;

	bool isAlive;

	// 미사일 매니저
	missileManager*	m_pMissileMgr;
	int				m_nFireCount;
	int				m_nRandFireCount;

	// 타겟
	/*	플레이어클래스*	m_pTarget;*/
public:
	HRESULT init();
	HRESULT init(const char* szFileName, POINT position);
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
	/*inline void setTarget(플레이어클래스* pTarget) { m_pTarget = pTarget; }*/
	inline void setIsAlive(bool IsAilve) { isAlive = IsAilve; }
	inline bool getIsAlive() { return isAlive; }
	boss();
	~boss();
};

