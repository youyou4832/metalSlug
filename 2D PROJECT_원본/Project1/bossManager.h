#pragma once
class bossManager
{
private:
	
	std::vector<bossManager*>	m_vecEnemy;
	std::vector<bossManager*>::iterator	m_iter;
	
	int				m_nCurrHP;
	int				m_nMaxHP;

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	
	void setEnemy(int countX, int countY);
	void damaged(int damage);
	void setTarget();
	//void setTarget(/*플레이어클래스*/* pTarget);


	inline std::vector<bossManager*>	getVecEnemy() { return m_vecEnemy; }
	inline std::vector<bossManager*>::iterator getIterEnemy() { return m_iter; }
	inline void setCurrHP(int hp) { m_nCurrHP = hp; }
	inline int getCurrHP() { return m_nCurrHP; }
	
	bossManager();
	~bossManager();
};

