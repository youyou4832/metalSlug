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

	// �̻��� �Ŵ���
	missileManager*	m_pMissileMgr;
	int				m_nFireCount;
	int				m_nRandFireCount;

	// Ÿ��
	/*	�÷��̾�Ŭ����*	m_pTarget;*/
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
	/*inline void setTarget(�÷��̾�Ŭ����* pTarget) { m_pTarget = pTarget; }*/
	inline void setIsAlive(bool IsAilve) { isAlive = IsAilve; }
	inline bool getIsAlive() { return isAlive; }
	boss();
	~boss();
};

