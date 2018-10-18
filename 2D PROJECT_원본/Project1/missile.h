#pragma once

struct m_tagState {
	int index = 0;
	int count = 0;
	bool isState = false;
};

class missile
{
protected:
	image * m_pImg;
	RECT	m_rc;
	//int		m_radius;
	//float	m_fSpeed;
	//float	m_fX, m_fY;
	float	m_fFiredX, m_fFiredY;
	float	m_fAngle;
	float	m_fRange;
	bool	m_isFire;

	m_tagState special_bullet;
	m_tagState fire_bullet;
	m_tagState cannon_bullet;
	m_tagState angle_count;


	int m_charNum;
	SYNTHESIZE(float, m_fX, PositionX);
	SYNTHESIZE(float, m_fY, PositionY);
	SYNTHESIZE(float, m_fSpeed, fSpeed);

public:
	HRESULT init(int charNum);
	HRESULT init(const char* szImageName, float speed,
		float x, float y, float angle, float range, int charNum);
	void release();
	void update();
	void render(HDC hdc, int charNum);

	void fire(float x, float y);
	virtual void move();

	inline RECT getRect() { return m_rc; }
	inline void setIsFire(bool isFire) { m_isFire = isFire; }
	inline bool getIsFire() { return m_isFire; }
	//inline void setTarget(player* pTarget) { m_pTarget = pTarget; }
	inline void setAngle(float angle) { m_fAngle = angle; }

	void ani_specialBullet();
	void ani_nomalBullet();
	void ani_rageBullet();
	void angleCount();
	missile();
	virtual ~missile();
};

