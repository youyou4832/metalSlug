#pragma once
#include "enemy.h"
class player;
class enemyManager
{
private:
	std::vector<enemy*>	m_vecEnemy;
	std::vector<enemy*>::iterator	m_iter;
	bool m_isMove;
	SYNTHESIZE(int, m_totalEnemy, TotalEnemy);

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	
	void setSniper(const char * textName, float x, float y, int speed, player* player);
	void setCannon(const char * textName, float x, float y, int speed, player* player, int enemyNumber, bool isMove);
	void setNormal(const char * textName, float x, float y, int speed, player* player, int enemyNumber, bool isMove);
	void setTank(const char * textName, float x, float y, int speed, player* player, bool isMove);

	inline std::vector<enemy*>	getVecEnemy() { return m_vecEnemy; }
	inline std::vector<enemy*>::iterator getIterEnemy() { return m_iter; }

	enemyManager();
	~enemyManager();
};

